#!/usr/bin/env python3
"""jblq_daemon.py — background daemon for JBL Quantum headsets.

Watches for a supported headset appearing/disappearing (dongle hotplug), reads its
pushed status events, and serves the current state plus simple commands on a local
unix socket (/run/user/<uid>/jblq.sock, newline-delimited JSON — request/response).
No D-Bus dependency; a future GUI/waybar widget talks to this socket.

  jblq_daemon.py [--once]   # --once: drain events for 60s then exit (debugging)

Protocol: research/jbl-quantum/PROTOCOL.md (verified report ids only; the daemon
never writes unless a client asks, and every write passes the same safety gates
as the CLI).
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
        self.lock = threading.Lock()
        self.state: dict = {"present": False, "product": None}
        self.hs: QuantumHeadset | None = None
        self.stream: EventStream | None = None
        self.stop = threading.Event()

    def _apply_event(self, name: str, value: int):
        with self.lock:
            if name == "battery":
                self.state["battery"] = value
            elif name == "dial":
                self.state["dial"] = value
            elif name == "anc":
                self.state["anc"] = ANC_MODES.get(value, value)
            elif name == "mic":
                self.state["mic"] = "active" if value else "muted/up"
            elif name == "lights":
                self.state["lights"] = bool(value)
            elif name == "link-burst":
                self.state["link"] = "up"

    def _connect(self):
        try:
            hs = QuantumHeadset.find()
        except (DeviceNotFound, UnsupportedDevice):
            return False
        print(f"daemon: found {hs.product}", flush=True)
        with self.lock:
            snap = hs.snapshot()  # read-only state harvest at connect
            self.state = {
                "present": True,
                "product": hs.product,
                "battery": snap.battery,
                "dial": snap.dial,
                "anc": ANC_MODES.get(snap.anc, snap.anc),
                "sidetone": SIDETONE_LEVELS.get(snap.sidetone, snap.sidetone),
                "lights": snap.lights,
                "auto_off_min": snap.auto_off[1] * 5 if snap.auto_off else None,
                "serial": snap.serial,
                "firmware": snap.firmware,
            }
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
            except OSError:
                # device vanished (unplugged / powered off)
                self._drop()

    def _drop(self):
        with self.lock:
            if self.stream:
                self.stream.close()
            if self.hs:
                self.hs.close()
            self.stream = None
            self.hs = None
            self.state = {"present": False, "product": None}
        print("daemon: device lost, waiting…", flush=True)

    def request(self, req: dict) -> dict:
        cmd = req.get("cmd")
        if cmd == "state":
            with self.lock:
                return dict(self.state)
        if cmd == "refresh":
            if self.hs is None:
                return {"ok": False, "error": "no headset present"}
            with self.lock:
                snap = self.hs.snapshot()
                self.state.update({
                    "present": True,
                    "product": self.hs.product,
                    "battery": snap.battery,
                    "dial": snap.dial,
                    "anc": ANC_MODES.get(snap.anc, snap.anc),
                    "sidetone": SIDETONE_LEVELS.get(snap.sidetone, snap.sidetone),
                    "lights": snap.lights,
                    "auto_off_min": snap.auto_off[1] * 5 if snap.auto_off else None,
                    "serial": snap.serial,
                    "firmware": snap.firmware,
                })
                return {"ok": True}
        if cmd == "set":
            if self.hs is None:
                return {"ok": False, "error": "no headset present"}
            feature = req.get("feature")
            value = req.get("value")
            try:
                if feature == "sidetone":
                    rev = {v: k for k, v in SIDETONE_LEVELS.items()}
                    if value not in rev:
                        return {"ok": False, "error": "sidetone: off|low|mid|high"}
                    self.hs.set_sidetone(rev[value])
                    return {"ok": True}
                if feature == "anc":
                    rev = {v: k for k, v in ANC_MODES.items()}
                    if value not in rev:
                        return {"ok": False, "error": "anc: off|on|talkthru"}
                    self.hs.set_anc(rev[value])
                    return {"ok": True}
                if feature == "lights":
                    self.hs.set_lights(bool(value))
                    return {"ok": True}
                if feature == "auto_off":
                    try:
                        minutes = int(value)
                    except (TypeError, ValueError):
                        return {"ok": False, "error": "auto_off: minutes"}
                    self.hs.set_auto_off(minutes // 5)
                    return {"ok": True}
                if feature == "light_zone":
                    self.hs.set_light_zone(int(value["element"]), int(value["speed"]),
                                           int(value["segments"]))
                    return {"ok": True}
                if feature == "light_colour":
                    self.hs.set_light_colour(
                        int(value["element"]), int(value["slot"]),
                        tuple(int(c) for c in value["rgb"]),
                        int(value.get("mode", 1)), int(value.get("last", 0)))
                    return {"ok": True}
                return {"ok": False, "error": f"unknown feature '{feature}'"}
            except Exception as e:
                return {"ok": False, "error": str(e)}
        return {"ok": False, "error": f"unknown cmd '{cmd}'"}


class Handler(socketserver.StreamRequestHandler):
    monitor: HeadsetMonitor

    def handle(self):
        for line in self.rfile:
            line = line.strip()
            if not line:
                continue
            try:
                req = json.loads(line)
            except json.JSONDecodeError:
                self.wfile.write(b'{"ok":false,"error":"bad json"}\n')
                continue
            resp = self.monitor.request(req)
            self.wfile.write((json.dumps(resp) + "\n").encode())


class Server(socketserver.ThreadingUnixStreamServer):
    allow_reuse_address = True
    daemon_threads = True


def main():
    once = "--once" in sys.argv
    monitor = Handler.monitor = HeadsetMonitor()
    t = threading.Thread(target=monitor.run, daemon=True)
    t.start()

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
