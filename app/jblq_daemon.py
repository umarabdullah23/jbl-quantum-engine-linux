#!/usr/bin/env python3
"""jblq_daemon.py — background daemon for JBL Quantum headsets.

Watches for a supported headset (dongle hotplug), reads pushed status events, and
serves state + writes on a unix socket ($XDG_RUNTIME_DIR/jblq.sock, newline JSON).

Design notes (learned the hard way, live):
  * state reads are LOCK-FREE — `self.state` is swapped atomically (dict assignment
    under the GIL); a wedged monitor can never block client requests.
  * snapshot() is taken OUTSIDE any lock.
  * the EventStream does NOT re-open the control hidraw (one handle per interface).
  * every client request answers or errors — handlers never die silently.
  * charging is not reported by the dongle: inferred from a rising battery trend
    (sticky until a decrease or 100%) — clearly labelled "inferred" in the GUI.
"""
from __future__ import annotations

import json
import os
import signal
import socket
import socketserver
import sys
import threading
import time

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

from jbl_quantum import (  # noqa: E402
    ANC_MODES,
    SIDETONE_LEVELS,
    DeviceNotFound,
    EventStream,
    QuantumHeadset,
    UnsupportedDevice,
)

SOCKET_PATH = os.path.join(
    os.environ.get("XDG_RUNTIME_DIR", f"/run/user/{os.getuid()}"), "jblq.sock")


class HeadsetMonitor:
    def __init__(self):
        self.lock = threading.Lock()   # guards hs/stream handles, NOT state reads
        self._state: dict = {"present": False, "product": None}
        self.hs: QuantumHeadset | None = None
        self.stream: EventStream | None = None
        self.stop = threading.Event()
        self._prev_battery = None
        self._charging = False

    @property
    def state(self) -> dict:
        return self._state

    def _set_state(self, **kw):
        new = dict(self._state)
        new.update(kw)
        self._state = new  # atomic swap

    def _apply_event(self, name: str, value: int):
        if name == "battery":
            self._track_battery(value)
        elif name == "dial":
            self._set_state(dial=value)
        elif name == "anc":
            self._set_state(anc=ANC_MODES.get(value, value))
        elif name == "mic":
            self._set_state(mic="active" if value else "muted/up")
        elif name == "lights":
            self._set_state(lights=bool(value))
        elif name == "link-burst":
            self._set_state(link="up")

    def _track_battery(self, value: int):
        prev = self._state.get("battery")
        if prev is not None and value > prev:
            self._charging = True
        elif value < (prev or 0) or value >= 100 and prev == 100:
            self._charging = False
        self._prev_battery = value
        self._set_state(battery=value, charging=self._charging)

    def _connect(self) -> bool:
        try:
            hs = QuantumHeadset.find()
        except (DeviceNotFound, UnsupportedDevice):
            return False
        except Exception as e:
            print(f"daemon: connect failed: {e}", flush=True)
            return False
        print(f"daemon: found {hs.product}", flush=True)
        try:
            snap = hs.snapshot()  # outside the lock: device I/O
        except Exception as e:
            print(f"daemon: snapshot failed: {e}", flush=True)
            hs.close()
            return False
        self._prev_battery = snap.battery
        self._charging = False
        self._set_state(
            present=True, product=hs.product,
            battery=snap.battery, dial=snap.dial,
            anc=ANC_MODES.get(snap.anc, snap.anc),
            sidetone=SIDETONE_LEVELS.get(snap.sidetone, snap.sidetone),
            lights=snap.lights,
            auto_off_min=snap.auto_off[1] * 5 if snap.auto_off else None,
            serial=snap.serial, firmware=snap.firmware,
            mic=hs.get_mic_active(), charging=False)
        with self.lock:
            self.hs = hs
            self.stream = EventStream(hs)
        return True

    def run(self):
        while not self.stop.is_set():
            if self.hs is None:
                if not self._connect():
                    time.sleep(2.0)
                    continue
            try:
                ev = self.stream.read_event()
                if ev:
                    self._apply_event(*ev)
                    print("daemon: event", ev, flush=True)
                else:
                    time.sleep(0.05)
            except (OSError, ValueError):
                self._drop()
            except Exception as e:
                print(f"daemon: monitor error: {e}", flush=True)
                self._drop()

    def _drop(self):
        with self.lock:
            if self.stream:
                try:
                    self.stream.close()
                except Exception:
                    pass
            if self.hs:
                try:
                    self.hs.close()
                except Exception:
                    pass
            self.stream = None
            self.hs = None
        self._set_state(present=False, product=None)
        print("daemon: device lost, waiting…", flush=True)

    def request(self, req: dict) -> dict:
        cmd = req.get("cmd")
        if cmd == "state":
            return dict(self._state)
        if cmd == "refresh":
            with self.lock:
                hs = self.hs
            if hs is None:
                return {"ok": False, "error": "no headset present"}
            try:
                snap = hs.snapshot()
            except Exception as e:
                return {"ok": False, "error": str(e)}
            self._track_battery(snap.battery) if snap.battery is not None else None
            self._set_state(
                present=True, product=hs.product,
                battery=snap.battery, dial=snap.dial,
                anc=ANC_MODES.get(snap.anc, snap.anc),
                sidetone=SIDETONE_LEVELS.get(snap.sidetone, snap.sidetone),
                lights=snap.lights,
                auto_off_min=snap.auto_off[1] * 5 if snap.auto_off else None,
                serial=snap.serial, firmware=snap.firmware,
                mic=hs.get_mic_active())
            return {"ok": True}
        if cmd == "set":
            with self.lock:
                hs = self.hs
            if hs is None:
                return {"ok": False, "error": "no headset present"}
            feature = req.get("feature")
            value = req.get("value")
            try:
                if feature == "sidetone":
                    rev = {v: k for k, v in SIDETONE_LEVELS.items()}
                    if value not in rev:
                        return {"ok": False, "error": "sidetone: off|low|mid|high"}
                    hs.set_sidetone(rev[value])
                    return {"ok": True}
                if feature == "anc":
                    rev = {v: k for k, v in ANC_MODES.items()}
                    if value not in rev:
                        return {"ok": False, "error": "anc: off|on|talkthru"}
                    hs.set_anc(rev[value])
                    return {"ok": True}
                if feature == "lights":
                    hs.set_lights(bool(value))
                    return {"ok": True}
                if feature == "auto_off":
                    try:
                        minutes = int(value)
                    except (TypeError, ValueError):
                        return {"ok": False, "error": "auto_off: minutes"}
                    hs.set_auto_off(minutes // 5)
                    return {"ok": True}
                if feature == "light_zone":
                    hs.set_light_zone(int(value["element"]), int(value["brightness"]),
                                      int(value["segments"]))
                    return {"ok": True}
                if feature == "light_colour":
                    hs.set_light_colour(
                        int(value["element"]), int(value["slot"]),
                        tuple(int(c) for c in value["rgb"]),
                        int(value.get("mode", 1)), int(value.get("last", 0)))
                    return {"ok": True}
                return {"ok": False, "error": f"unknown feature '{feature}'"}
            except Exception as e:
                return {"ok": False, "error": str(e)}
        return {"ok": False, "error": f"unknown cmd '{cmd}'"}


class Handler(socketserver.StreamRequestHandler):
    timeout = 5  # never let a wedged client/handler hold a thread forever
    monitor: HeadsetMonitor

    def handle(self):
        try:
            for line in self.rfile:
                line = line.strip()
                if not line:
                    continue
                try:
                    req = json.loads(line)
                except json.JSONDecodeError:
                    self.wfile.write(b'{"ok":false,"error":"bad json"}\n')
                    continue
                try:
                    resp = self.monitor.request(req)
                except Exception as e:
                    resp = {"ok": False, "error": f"handler: {e}"}
                self.wfile.write((json.dumps(resp) + "\n").encode())
        except Exception:
            pass  # client vanished mid-request; the thread must not die noisily


class Server(socketserver.ThreadingUnixStreamServer):
    allow_reuse_address = True
    daemon_threads = True
    request_queue_size = 16


def main():
    once = "--once" in sys.argv
    monitor = Handler.monitor = HeadsetMonitor()
    threading.Thread(target=monitor.run, daemon=True).start()

    if os.path.exists(SOCKET_PATH):
        os.unlink(SOCKET_PATH)
    srv = Server(SOCKET_PATH, Handler)
    print(f"daemon: socket at {SOCKET_PATH}", flush=True)

    def bye(*_):
        monitor.stop.set()
        srv.shutdown()

    signal.signal(signal.SIGTERM, bye)
    signal.signal(signal.SIGINT, bye)

    if once:
        time.sleep(60)
        bye()
        return
    srv.serve_forever()


if __name__ == "__main__":
    main()
