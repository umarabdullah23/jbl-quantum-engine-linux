#!/usr/bin/env python3
"""jblq_gui.py — simple control panel for the jblq daemon.

Talks to the running daemon over its unix socket (same protocol as the CLI),
auto-refreshes every 2 s, and shows an explicit "plug in the dongle" state when
no headset is present. Buttons send {"cmd":"set", ...} — every write passes the
daemon's verified-protocol safety gates.
"""
import json
import socket
import os
import sys
import threading
import tkinter as tk
from tkinter import ttk

SOCKET_PATH = os.path.join(
    os.environ.get("XDG_RUNTIME_DIR", f"/run/user/{os.getuid()}"), "jblq.sock")


def daemon_request(req: dict, timeout: float = 2.0) -> dict:
    try:
        s = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)
        s.settimeout(timeout)
        s.connect(SOCKET_PATH)
        s.sendall((json.dumps(req) + "\n").encode())
        data = s.recv(4096).decode()
        s.close()
        return json.loads(data.strip())
    except Exception as e:
        return {"ok": False, "error": f"daemon unreachable: {e}"}


class App(tk.Tk):
    def __init__(self, demo: bool = False):
        super().__init__()
        self.title("JBL Quantum Engine — Linux")
        self.geometry("420x520")
        self.configure(bg="#111318")
        self.resizable(False, False)
        self.demo = demo
        self.demo_state = {
            "present": True,
            "product": "JBL Quantum 810 Wireless",
            "battery": 87,
            "dial": 11,
            "anc": "on",
            "sidetone": "low",
            "lights": True,
            "auto_off_min": 60,
            "serial": "DEMO0810WRLSS00",
            "firmware": "1.2.7 / 0.9.4 / 2.1.0 / 1.0.3",
        }

        style = ttk.Style(self)
        style.theme_use("clam")
        style.configure("TButton", padding=8)
        style.configure("TLabel", background="#111318", foreground="#e6e6e6")
        style.configure("Head.TLabel", font=("", 14, "bold"))
        style.configure("Dim.TLabel", foreground="#8a8f98")

        ttk.Label(self, text="JBL QUANTUM ENGINE", style="Head.TLabel").pack(pady=(14, 0))
        self.status = ttk.Label(self, text="connecting to daemon…", style="Dim.TLabel")
        self.status.pack(pady=(2, 8))

        self.state_lbl = tk.Label(self, text="", justify="left", anchor="w",
                                  bg="#181b21", fg="#e6e6e6",
                                  font=("TkFixedFont", 11), width=44, height=10, padx=12, pady=10)
        self.state_lbl.pack(padx=14, pady=6)

        box = ttk.Frame(self)
        box.pack(padx=14, pady=8, fill="x")

        # ANC
        ttk.Label(box, text="Noise cancelling").grid(row=0, column=0, sticky="w", pady=3)
        self.anc = tk.StringVar()
        for val in ("off", "on", "talkthru"):
            ttk.Radiobutton(box, text=val, variable=self.anc, value=val,
                            command=lambda: self.set("anc", self.anc.get()),
                            ).grid(row=0, column=1 + {"off": 0, "on": 1, "talkthru": 2}[val])

        # Sidetone
        ttk.Label(box, text="Sidetone").grid(row=1, column=0, sticky="w", pady=3)
        self.st = tk.StringVar()
        for val in ("off", "low", "mid", "high"):
            ttk.Radiobutton(box, text=val, variable=self.st, value=val,
                            command=lambda: self.set("sidetone", self.st.get())
                            ).grid(row=1, column=1 + ["off", "low", "mid", "high"].index(val))

        # Lights
        ttk.Label(box, text="Lights").grid(row=2, column=0, sticky="w", pady=3)
        self.lt = tk.StringVar()
        for val in ("off", "on"):
            ttk.Radiobutton(box, text=val, variable=self.lt, value=val,
                            command=lambda: self.set("lights", val if self.lt.get() != "on" else True)
                            ).grid(row=2, column=1 + ("off", "on").index(val))

        self.msg = ttk.Label(self, text="", style="Dim.TLabel", wraplength=380)
        self.msg.pack(pady=4)

        self.dongle_hint = ttk.Label(
            self, text="Plug in the Quantum 810 USB dongle — this panel connects automatically.",
            style="Dim.TLabel", wraplength=380)
        self.dongle_hint.pack(pady=(6, 10))

        self.demo_var = tk.BooleanVar(value=demo)
        self.demo_btn = ttk.Checkbutton(
            self, text="Demo UI (no headset needed)",
            variable=self.demo_var, command=self._toggle_demo)
        self.demo_btn.pack(pady=(0, 10))

        self._refresh()

    def _toggle_demo(self):
        self.demo = self.demo_var.get()
        self._refresh()

    def _refresh(self):
        st = daemon_request({"cmd": "state"})
        if self.demo and not st.get("present"):
            self._render(st, demo=True)
            self.after(2000, self._refresh)
            return
        if not st.get("present"):
            self.status.config(text="daemon: running  ·  headset: not detected")
            self.state_lbl.config(text="No headset detected.\n\nPlug in the Quantum 810 wireless dongle.\n"
                                       "This panel connects automatically.")
            self.dongle_hint.pack()
        else:
            self.status.config(text=f"daemon: running  ·  headset: connected")
            lines = [
                f"product    : {st.get('product', '?')}",
                f"battery    : {st.get('battery', '—')}%",
                f"dial       : {st.get('dial', '—')}/16",
                f"ANC        : {st.get('anc', '—')}",
                f"sidetone   : {st.get('sidetone', '—')}",
                f"lights     : {'on' if st.get('lights') else 'off'}",
                f"auto-off   : {st.get('auto_off_min', '—')} min",
                f"serial     : {st.get('serial', '—')}",
                f"firmware   : {st.get('firmware', '—')}",
            ]
            self._render(st, demo=False)
        self.after(2000, self._refresh)

    def _render(self, st, demo: bool):
        if demo:
            self.status.config(text="daemon: running  ·  headset: NOT DETECTED  ·  showing DEMO data")
            st = dict(self.demo_state)
        else:
            self.status.config(text="daemon: running  ·  headset: connected")
        lines = [
            f"product    : {st.get('product', '?')}",
            f"battery    : {st.get('battery', '—')}%",
            f"dial       : {st.get('dial', '—')}/16",
            f"ANC        : {st.get('anc', '—')}",
            f"sidetone   : {st.get('sidetone', '—')}",
            f"lights     : {'on' if st.get('lights') else 'off'}",
            f"auto-off   : {st.get('auto_off_min', '—')} min",
            f"serial     : {st.get('serial', '—')}",
            f"firmware   : {st.get('firmware', '—')}",
        ]
        self.state_lbl.config(text="\n".join(lines))
        self.dongle_hint.pack_forget()
        # reflect state into radio buttons without firing commands
        if st.get("anc") in ("off", "on", "talkthru"):
            self.anc.set(st["anc"])
        if st.get("sidetone") in ("off", "low", "mid", "high"):
            self.st.set(st["sidetone"])
        self.lt.set("on" if st.get("lights") else "off")

    def set(self, feature, value):
        if feature == "lights":
            value = (value is True or value == "on")
        if self.demo and not daemon_request({"cmd": "state"}).get("present"):
            # demo mode: update local demo state only, never touch the daemon
            self.demo_state[{"lights": "lights"}.get(feature, feature)] = \
                value if feature != "lights" else bool(value)
            self.msg.config(text=f"{feature} → {value}  (demo — nothing sent to hardware)",
                            foreground="#e6b450")
            self.after(100, self._refresh)
            return
        resp = daemon_request({"cmd": "set", "feature": feature, "value": value})
        if resp.get("ok"):
            self.msg.config(text=f"{feature} → {value}", foreground="#7bd88f")
        else:
            self.msg.config(text=resp.get("error", "write failed"), foreground="#f05e5e")
        self.after(400, self._refresh)


if __name__ == "__main__":
    App(demo="--demo" in sys.argv).mainloop()
