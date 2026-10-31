#!/usr/bin/env python3
"""spatial_win.py — REAL host-side spatial sound for the Windows app, GameLoop-safe.

The dongle receives nothing for spatial (capture-proven) — processing lives on the PC.
Windows' own spatial formats (Windows Sonic / DTS Headphone:X where licensed) are the
host-side implementation we can drive.

WHY THE FORMAT PIN EXISTS (owner report, 2026-11-01): the Quantum Game endpoint ships
as 8-channel/48kHz; enabling Windows Sonic rewrites the endpoint format to 2-channel
(registry-verified: {f19f064d} blob feff0800 → feff0200 in ~100 ms). GameLoop/PUBGM
treats that format change as the headset being unplugged and never recovers — the
"disconnect then connect" the owner saw. The real QuantumENGINE never hits this because
JBL's own audio filter is always installed and processes in-place.

THE FIX (registry-poll-verified): pin the endpoint default format to 2ch/16-bit/48kHz
ONCE, before the first enable. Every later spatial toggle then changes ZERO format and
the device never leaves Active state — the endpoint identity is stable, so the emulator
keeps the headset. Disabling spatial deliberately does NOT restore 8ch (that would
reintroduce the same break). Trade-off: Windows mixes 7.1 down to stereo before the
endpoint — inaudible on a stereo headset.

Mechanism: NirSoft SoundVolumeView (vendored unmodified, freeware) — /SetSpatial,
/SetDefaultFormat, /stext read-back ('Spatial Guid' + 'Default Format' lines).
Gotchas learned live: SVV writes asynchronously (poll the dump file), output may be
UTF-16 (BOM-detect), and after a dongle re-enumeration STALE endpoints with identical
friendly names exist — only trust records with "Device State : Active" and target the
Item ID, never the name.
"""
from __future__ import annotations

import os
import re
import subprocess
import sys
import tempfile
import time

SONIC = "Windows Sonic For Headphones"
SONIC_GUID = "{B53D940C-B846-4831-9F76-D102B9B725A0}"
DTS_NAME = "DTS Headphone:X"
PINNED_FORMAT = "2 Channel, 16 bit, 48000 Hz"


def _svv_path() -> str:
    if getattr(sys, "frozen", False):
        base = getattr(sys, "_MEIPASS", os.path.dirname(sys.executable))
        for cand in (os.path.join(base, "vendor", "SoundVolumeView.exe"),
                     os.path.join(os.path.dirname(sys.executable), "vendor",
                                  "SoundVolumeView.exe")):
            if os.path.exists(cand):
                return cand
        return cand
    return os.path.join(os.path.dirname(os.path.abspath(__file__)), "vendor",
                        "SoundVolumeView.exe")


def _dump(timeout=40, retries=2) -> str | None:
    svv = _svv_path()
    if not os.path.exists(svv):
        return None
    for _ in range(retries):
        fd, out = tempfile.mkstemp(suffix=".txt")
        os.close(fd)
        try:
            subprocess.run([svv, "/stext", out], capture_output=True, timeout=timeout)
        except subprocess.TimeoutExpired:
            subprocess.run(["taskkill", "/IM", "SoundVolumeView.exe", "/F"],
                           capture_output=True)
        for _wait in range(15):  # SVV writes asynchronously — poll, don't assume
            time.sleep(0.3)
            if os.path.exists(out) and os.path.getsize(out) > 5000:
                break
        try:
            if os.path.exists(out):
                raw = open(out, "rb").read()
                txt = (raw.decode("utf-16") if raw[:2] in (b"\xff\xfe", b"\xfe\xff")
                       else raw.decode("utf-8", errors="replace"))
                if len(txt.strip()) > 1000:
                    return txt
        except OSError:
            pass
        finally:
            try:
                os.remove(out)
            except OSError:
                pass
    return None


def _endpoint_record() -> dict | None:
    """The ACTIVE Quantum Game render endpoint record (never stale duplicates)."""
    txt = _dump()
    if not txt:
        return None
    fallback = None
    for block in txt.split("=" * 50):
        if "Speakers\\Render" not in block or "Direction         : Render" not in block:
            continue
        if "Device State      : Active" not in block:
            continue
        if "quantum" not in block.lower() and "jbl" not in block.lower():
            continue
        m_id = re.search(r"Item ID\s+: (\S+)", block)
        if not m_id:
            continue
        rec = {"item_id": m_id.group(1),
               "format": (re.search(r"Default Format\s+: (.*)", block) or [None, ""])
                         .group(1).strip() if re.search(r"Default Format\s+: (.*)", block) else "",
               "spatial_guid": (re.search(r"Spatial Guid\s*: (\S*)", block).group(1).strip()
                                if re.search(r"Spatial Guid\s*: (\S*)", block) else "")}
        if "game" in block.lower():
            return rec          # spatial applies to game audio — the primary endpoint
        fallback = fallback or rec
    return fallback


def get_spatial() -> dict:
    rec = _endpoint_record()
    if rec is None:
        return {"available": False, "guid": "", "mode": "off",
                "endpoint": None,
                "error": "headset audio not active — power the headset on"}
    mode = "off"
    if rec["spatial_guid"]:
        mode = SONIC if rec["spatial_guid"].upper() == SONIC_GUID else rec["spatial_guid"]
    return {"available": True, "guid": rec["spatial_guid"], "mode": mode,
            "endpoint": rec["item_id"], "format": rec["format"]}


def set_spatial(format_name: str) -> dict:
    """Set (or clear with '') the spatial format on the ACTIVE Quantum endpoint.

    Enabling first pins the endpoint format to 2ch/48k (see module docstring — this is
    the GameLoop/PUBGM disconnect fix). Verified by read-back: {ok, applied, mode}.
    """
    svv = _svv_path()
    if not os.path.exists(svv):
        return {"ok": False, "error": "SoundVolumeView.exe missing from the app bundle"}
    rec = _endpoint_record()
    if rec is None:
        return {"ok": False,
                "error": "headset audio not active — power the headset on and try again"}

    svv_exe = svv

    def run_svv(*a):
        return subprocess.run([svv_exe, *a], capture_output=True, timeout=40)

    if format_name:  # enabling — pin the format first (no-op if already pinned)
        if rec.get("format") and rec["format"] != PINNED_FORMAT:
            run_svv("/SetDefaultFormat", rec["item_id"], "16", "48000", "2")
            pinned = _endpoint_record()
            if pinned and pinned.get("format") != PINNED_FORMAT:
                return {"ok": False,
                        "error": f"could not pin endpoint format (still {pinned.get('format')!r})"}
        want_guid_state = True
    else:
        want_guid_state = False

    r = run_svv("/SetSpatial", rec["item_id"], format_name)
    if r.returncode != 0:
        return {"ok": False, "error": f"SetSpatial rc={r.returncode}"}

    # read-back — never claim a set we didn't verify
    for _ in range(3):
        after = get_spatial()
        if not after.get("available"):
            return {"ok": False, "error": after.get("error", "endpoint lost")}
        if bool(after.get("guid")) == want_guid_state:
            return {"ok": True, "applied": True, "guid": after["guid"],
                    "mode": after["mode"], "format_pinned":
                        after.get("format") == PINNED_FORMAT}
        time.sleep(0.6)
    return {"ok": False, "error": "read-back mismatch — the OS didn't apply the change"}
