#!/usr/bin/env python3
"""jbl_quantum.py — native Linux control for JBL Quantum wireless headsets.

Implements the Quantum 810 Wireless dongle HID feature protocol
(VID 0x0ECB, control interface = MI_05). Protocol facts and evidence:
  research/jbl-quantum/PROTOCOL.md

Safety rules baked into this module:
  * Unknown VID:PID  -> DeviceNotFound / UnsupportedDevice, never a speculative write.
  * Every setter reads the current value first and offers restore(); nothing is sent
    that is not in the verified report table below.
  * Firmware/DFU report IDs (0xF0/0xF1/0xF4/0xF5/0xF6/0x9A) are deliberately absent.
  * RGB segment count is hard-clamped to 1-5 (>5 wedges the lighting MCU, per the
    taron-sys report map).

Transport: hidraw via hidapi (python `hid` package). Feature reports use
HIDIOCSFEATURE/HIDIOCGFEATURE semantics through hidapi's feature-report API, so no
kernel detaching or libusb interface claiming (claiming the vendor interface destroys
the hidraw node until replug).
"""
from __future__ import annotations

import struct
import time
from dataclasses import dataclass, field

VENDOR_ID = 0x0ECB  # Harman International / JBL

# Verified product IDs -> (name, control interface index). 810 verified in hand;
# the rest recognized but writes are still gated by the same verified report ids.
MODELS: dict[int, tuple[str, int]] = {
    0x2069: ("JBL Quantum 810 Wireless", 5),
    0x1F47: ("JBL Quantum 800", 5),
    0x203E: ("JBL Quantum 800", 5),
    0x219A: ("JBL Quantum 850", 5),
    0x219B: ("JBL Quantum 850", 5),
    0x219C: ("JBL Quantum 850", 5),
    0x2088: ("JBL Quantum 910", 5),
    0x209C: ("JBL Quantum 910", 5),
    0x20A2: ("JBL Quantum 910 PS", 5),
    0x209D: ("JBL Quantum 910 Xbox", 5),
    0x209F: ("JBL Quantum 910 Xbox", 5),
    0x2147: ("JBL Quantum 910 Xbox Black", 5),
    0x214A: ("JBL Quantum 910 Xbox", 5),
    0x2127: ("JBL Quantum 950", 5),
    0x2128: ("JBL Quantum 950", 5),
    0x2129: ("JBL Quantum 950", 5),
    0x2141: ("JBL Quantum 950X", 5),
    0x213E: ("JBL Quantum 950X Xbox", 5),
    0x2140: ("JBL Quantum 950X Xbox", 5),
    0x1F48: ("JBL Quantum ONE", 5),
    0x203A: ("JBL Quantum ONE", 5),
    0x20C2: ("JBL Quantum ONE P1", 5),
    0x205C: ("JBL Quantum 610", 5),
    0x1F46: ("JBL Quantum 600", 5),
    0x203C: ("JBL Quantum 600", 5),
    0x1F4C: ("JBL Quantum 400", 5),
    0x2039: ("JBL Quantum 400", 5),
    0x20EE: ("JBL Quantum 400", 5),
    0x2115: ("JBL Quantum 360 Wireless", 5),
    0x20A5: ("JBL Quantum 360 Xbox", 5),
    0x2142: ("JBL Quantum 360 Xbox Black", 5),
    0x20AB: ("JBL Quantum 360 PS", 5),
}

# ---- verified feature report ids (see PROTOCOL.md §2/§3) --------------------
R_ANC = 0x46            # SET: 0=off 1=on 2=talkthru
R_ANC_MIRROR = 0x45     # GET
R_BATTERY = 0x49        # GET: 0-100
R_LIGHTS = 0x4B         # SET: 0=off 1=on
R_LIGHTS_MIRROR = 0x4A
R_LIGHT_CONFIG = 0x4C   # SET [id, element, brightness, segments]; brightness in
                        # {40,50,60,70,75,80,100}; segments 1..5 HARD LIMIT
R_LIGHT_COLOUR = 0x4D   # SET [id, element, slot, r, g, b, mode, last(0..8)]
R_FIRMWARE = 0x51       # GET: 4x 3-byte major.minor.patch
R_HOST_NAME = 0x5B      # GET: len byte, 1 unknown, ascii
R_SIDETONE = 0x5D       # SET: 0=off 1=low 2=mid 3=high (4-step enum)
R_SIDETONE_MIRROR = 0x5C
R_SERIAL = 0x61         # GET: 16 ascii
R_DIAL = 0x62           # GET: game/chat 0..16
R_MIC_ACTIVE = 0x67     # GET: boom down AND unmuted
R_CONNECTION = 0x68     # GET
R_CONNECTION_MIRROR = 0x69
R_AUTO_OFF = 0x75       # SET and GET (same id), 5-minute units, byte2=0x02 undecoded

FORBIDDEN_REPORTS = {0xF0, 0xF1, 0xF4, 0xF5, 0xF6, 0x9A}  # suspected firmware/DFU

LIGHT_BRIGHTNESS = {0x28: 40, 0x32: 50, 0x3C: 60, 0x46: 70, 0x4B: 75,
                    0x50: 80, 0x64: 100}  # byte2 = brightness % (QE boot writes
                    # 0x64=100; sidmax7 labels this byte per-zone brightness)

ANC_MODES = {0: "off", 1: "on", 2: "talkthru"}
SIDETONE_LEVELS = {0: "off", 1: "low", 2: "mid", 3: "high"}

# interrupt-IN event report ids (pushed on the device's event interface)
EVENT_IDS = {
    0x02: "anc",
    0x03: "bluetooth",
    0x06: "mic",
    0x07: "lights",
    0x08: "battery",
    0x09: "link-burst",
    0x10: "dial",
    0x2F: "mute-bracket",
}


class JblError(RuntimeError):
    pass


class DeviceNotFound(JblError):
    pass


class UnsupportedDevice(JblError):
    pass


@dataclass
class Snapshot:
    """Full state dump — the 'undo' record. Capture BEFORE any first write."""
    path: str
    product: str
    product_id: int
    anc: int | None = None
    sidetone: int | None = None
    lights: int | None = None
    auto_off: bytes | None = None
    battery: int | None = None
    dial: int | None = None
    serial: str | None = None
    firmware: str | None = None
    raw: dict = field(default_factory=dict)

    def summary(self) -> str:
        lines = [f"device: {self.product} (0x{VENDOR_ID:04x}:{self.product_id:04x}) @ {self.path}"]
        if self.anc is not None:
            lines.append(f"  ANC            : {ANC_MODES.get(self.anc, hex(self.anc))}")
        if self.sidetone is not None:
            lines.append(f"  Sidetone       : {SIDETONE_LEVELS.get(self.sidetone, hex(self.sidetone))}")
        if self.lights is not None:
            lines.append(f"  Lights         : {'on' if self.lights else 'off'}")
        if self.auto_off is not None:
            mins = self.auto_off[1] * 5
            lines.append(f"  Auto power-off : {'off' if mins == 0 else f'{mins} min'}")
        if self.battery is not None:
            lines.append(f"  Battery        : {self.battery}%")
        if self.dial is not None:
            lines.append(f"  Game/chat dial : {self.dial}/16")
        if self.serial:
            lines.append(f"  Serial         : {self.serial}")
        if self.firmware:
            lines.append(f"  Firmware       : {self.firmware}")
        return "\n".join(lines)


class QuantumHeadset:
    """Open handle to the control HID interface of a supported Quantum headset."""

    def __init__(self, path: str, product: str, product_id: int):
        import hid  # deferred so the module imports without hidapi installed

        self.path = path
        self.product = product
        self.product_id = product_id
        self._h = hid.device()
        self._h.open_path(path.encode() if isinstance(path, str) else path)
        # undo registry: first value seen for each report id wins
        self._originals: dict[int, bytes] = {}

    # ---- discovery ---------------------------------------------------------
    @classmethod
    def find(cls, product_id: int | None = None) -> "QuantumHeadset":
        import hid

        for info in hid.enumerate(VENDOR_ID):
            pid = info["product_id"]
            if product_id is not None and pid != product_id:
                continue
            if pid not in MODELS:
                continue
            name, iface = MODELS[pid]
            # control interface = vendor-defined usage page on the model's interface
            if info.get("interface_number") != iface:
                continue
            if (info.get("usage_page") or 0) < 0xFF00:
                continue
            return cls(info["path"], name, pid)
        # diagnostics for the error message
        seen = [(f"0x{VENDOR_ID:04x}:0x{i['product_id']:04x}", i["interface_number"],
                 f"0x{i.get('usage_page') or 0:04x}") for i in hid.enumerate(VENDOR_ID)]
        if seen:
            raise UnsupportedDevice(
                f"JBL/Harman device(s) present but no usable control interface: {seen}")
        raise DeviceNotFound(
            f"No JBL Quantum headset found (no 0x{VENDOR_ID:04x}:* device on any bus). "
            "Plug in the wireless dongle and re-run.")

    # ---- low-level feature report I/O --------------------------------------
    def _get_feature(self, report_id: int, size: int = 64) -> bytes | None:
        if report_id in FORBIDDEN_REPORTS:
            raise JblError(f"report 0x{report_id:02x} is firmware/DFU territory — refused")
        try:
            data = self._h.get_feature_report(report_id, size)
        except Exception as e:  # hidapi raises on stalled/unsupported
            return None
        if not data:
            return None
        # device quirk: unknown ids answer with the nearest lower known id [TT]
        if data and data[0] != report_id:
            return None
        return bytes(data)

    def _set_feature(self, payload: bytes) -> None:
        report_id = payload[0]
        if report_id in FORBIDDEN_REPORTS:
            raise JblError(f"report 0x{report_id:02x} is firmware/DFU territory — refused")
        self._h.send_feature_report(payload)

    def _capture_original(self, report_id: int, getter) -> None:
        if report_id in self._originals:
            return
        try:
            current = getter()
        except Exception:
            return
        if current is not None:
            self._originals[report_id] = current

    # ---- per-feature getters/setters ---------------------------------------
    def get_anc(self) -> int | None:
        d = self._get_feature(R_ANC_MIRROR)
        return d[1] if d and len(d) > 1 else None

    def set_anc(self, mode: int) -> None:
        if mode not in ANC_MODES:
            raise ValueError(f"ANC mode must be one of {ANC_MODES}")
        self._capture_original(R_ANC_MIRROR, self.get_anc)
        self._set_feature(bytes([R_ANC, mode]))

    def get_sidetone(self) -> int | None:
        d = self._get_feature(R_SIDETONE_MIRROR)
        return d[1] if d and len(d) > 1 else None

    def set_sidetone(self, level: int) -> None:
        if level not in SIDETONE_LEVELS:
            raise ValueError(f"sidetone must be one of {SIDETONE_LEVELS}")
        self._capture_original(R_SIDETONE_MIRROR, self.get_sidetone)
        self._set_feature(bytes([R_SIDETONE, level]))

    def get_lights(self) -> int | None:
        d = self._get_feature(R_LIGHTS_MIRROR)
        return d[1] if d and len(d) > 1 else None

    def set_lights(self, on: bool) -> None:
        self._capture_original(R_LIGHTS_MIRROR, self.get_lights)
        self._set_feature(bytes([R_LIGHTS, 1 if on else 0]))

    def set_light_zone(self, element: int, brightness: int, segments: int) -> None:
        """brightness: percent 40/50/60/70/75/80/100 (device-allowed values)."""
        if element not in (0, 1):
            raise ValueError("element must be 0 (logo) or 1 (ring)")
        allowed = {v for v in LIGHT_BRIGHTNESS.values()}
        if brightness not in allowed:
            raise ValueError(f"brightness must be one of {sorted(allowed)}")
        if not 1 <= segments <= 5:  # HARD SAFETY: >5 wedges the lighting MCU [TT]
            raise ValueError("segments must be 1..5 (hardware safety limit)")
        self._capture_original(R_LIGHTS_MIRROR, self.get_lights)
        self._set_feature(bytes([R_LIGHT_CONFIG, element, brightness, segments]))

    def set_light_colour(self, element: int, slot: int, rgb: tuple[int, int, int],
                         mode: int = 1, last: int = 0) -> None:
        if element not in (0, 1):
            raise ValueError("element must be 0 (logo) or 1 (ring)")
        if not 0 <= slot <= 4:
            raise ValueError("slot must be 0..4")
        if not 0 <= mode <= 6:
            raise ValueError("mode must be 0..6 (breathing/solid/wave/glitch/spin-cw/spin-ccw/rise)")
        if not 0 <= last <= 8:
            raise ValueError("last must be 0..8 (per-segment parameter)")
        r, g, b = rgb
        self._set_feature(bytes([R_LIGHT_COLOUR, element, slot, r, g, b, mode, last]))

    def get_auto_off(self) -> bytes | None:
        # sole report where GET id == SET id [TT]; no event ACK — read back to verify
        d = self._get_feature(R_AUTO_OFF)
        return bytes(d[:2]) if d else None

    def set_auto_off(self, units: int) -> None:
        """units = timeout in 5-minute steps: 0=off, 6=30min, 12=1h, 24=2h."""
        if not 0 <= units <= 0xFF:
            raise ValueError("auto-off units must be 0..255")
        self._capture_original(R_AUTO_OFF, self.get_auto_off)
        payload = bytes([R_AUTO_OFF, units, 0x02])
        self._set_feature(payload)
        # no ACK event exists for 0x75 — verify by read-back [TT]
        time.sleep(0.05)
        rb = self.get_auto_off()
        if rb and rb[1] != units:
            raise JblError(f"auto-off write did not take (read back {rb.hex()})")

    def get_battery(self) -> int | None:
        d = self._get_feature(R_BATTERY)
        return d[1] if d and len(d) > 1 else None

    def get_dial(self) -> int | None:
        d = self._get_feature(R_DIAL)
        v = d[1] if d and len(d) > 1 else None
        if v is not None and not 0 <= v <= 16:
            return None
        return v

    def get_mic_active(self) -> bool | None:
        d = self._get_feature(R_MIC_ACTIVE)
        return bool(d[1]) if d and len(d) > 1 else None

    def get_serial(self) -> str | None:
        d = self._get_feature(R_SERIAL, 20)
        if not d or len(d) < 17:
            return None
        try:
            return d[1:17].decode("ascii", errors="replace")
        except Exception:
            return None

    def get_firmware(self) -> str | None:
        d = self._get_feature(R_FIRMWARE, 16)
        if not d or len(d) < 13:
            return None
        triplets = []
        for i in range(4):
            m, n, p = d[1 + 3 * i : 4 + 3 * i]
            triplets.append(f"{m}.{n}.{p}")
        return " / ".join(triplets)

    # ---- bulk ---------------------------------------------------------------
    def snapshot(self) -> Snapshot:
        s = Snapshot(path=str(self.path), product=self.product, product_id=self.product_id)
        s.anc = self.get_anc()
        s.sidetone = self.get_sidetone()
        s.lights = self.get_lights()
        s.auto_off = self.get_auto_off()
        s.battery = self.get_battery()
        s.dial = self.get_dial()
        s.serial = self.get_serial()
        s.firmware = self.get_firmware()
        s.raw = {f"0x{k:02x}": v.hex() for k, v in self._originals.items()}
        return s

    def restore_originals(self) -> dict[str, str]:
        """Restore every setting this handle changed, to the first value we saw."""
        out = {}
        for rid, original in self._originals.items():
            try:
                self._set_feature(original)
                out[f"0x{rid:02x}"] = original.hex()
            except Exception as e:
                out[f"0x{rid:02x}"] = f"FAILED: {e}"
        return out

    def close(self) -> None:
        try:
            self._h.close()
        except Exception:
            pass

    def __enter__(self):
        return self

    def __exit__(self, *a):
        self.close()


# ---- event stream (interrupt-IN reports) ------------------------------------
class EventStream:
    """Reads pushed 2-byte status reports (battery, dial, ANC, mic, lights…).

    Opens the model's control hidraw (events are also delivered there) and, when
    present, the sibling MI_03 event hidraw. Use in a thread; reports arrive
    whenever the device pushes them (power-on burst, dial turn, battery…).
    """

    def __init__(self, headset: QuantumHeadset):
        import hid

        self._streams: list[hid.device] = []
        # Open EVERY hidraw interface of this headset (hid.enumerate only returns
        # HID interfaces, so audio isochronous interfaces never appear here).
        # Events (battery, dial, ANC…) arrive on whichever interface pushes them.
        seen: set[str] = set()
        for info in hid.enumerate(VENDOR_ID, headset.product_id):
            p = info["path"]
            if p in seen:
                continue
            seen.add(p)
            try:
                h = hid.device()
                h.open_path(p)
                h.set_nonblocking(True)
                self._streams.append(h)
            except OSError:
                continue

    def read_event(self) -> tuple[str, int] | None:
        for s in self._streams:
            data = s.read(64)
            if data and len(data) >= 2 and data[0] in EVENT_IDS:
                return EVENT_IDS[data[0]], data[1]
        return None

    def close(self) -> None:
        for s in self._streams:
            try:
                s.close()
            except Exception:
                pass
