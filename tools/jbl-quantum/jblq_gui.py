#!/usr/bin/env python3
"""jblq_gui.py — QuantumENGINE-style control panel for JBL Quantum headsets (Linux).

Layout mirrors the Windows app's own feature structure (vocabulary extracted from the
app's binary/strings): SOUND (spatial, game & chat balance, equalizer), MICROPHONE
(mic, gain, sidetone/audio-voice monitor), AMBIENT SOUND CONTROL (ANC/AA/Off),
LIGHTING (zones, effects, colours), DEVICE (battery, auto power off, info).

Honesty rules shown in the UI:
  * device-verified controls (ANC/AA, sidetone, lights, auto-off) are live through the daemon
  * host-side features (spatial/EQ on Windows are host DSP) are marked "host-side";
    live wiring = PipeWire (pending), demo = visual only
  * controls with no verified dongle report yet are marked "(pending)"
"""
import json
import os
import socket
import sys
import tkinter as tk
from tkinter import ttk

SOCKET_PATH = os.path.join(
    os.environ.get("XDG_RUNTIME_DIR", f"/run/user/{os.getuid()}"), "jblq.sock")

BG, PANEL, TXT, DIM, ACC, ORANGE = "#14161b", "#1d2027", "#e8e8e8", "#8a8f98", "#3d6eff", "#ff3300"

SPATIAL_MODES = ["Off", "JBL QuantumSURROUND", "DTS Headphone:X"]
EQ_PRESETS = ["Default", "Moody", "Chill", "BASS BOOST", "Treble Boost", "Vocal Boost",
              "Casual Game", "FPS Game", "E-Sports Live", "Sports Game", "Racing Game",
              "Movie", "Music"]
EQ_BANDS = ["63", "125", "250", "500", "1k", "2k", "4k", "8k", "16k"]
# approximate demo curves (dB per band) — exact QuantumENGINE values pending extraction;
# community extraction: alessandromrc/jbl-quantum-4-linux
EQ_CURVES = {
    "Default":      [0, 0, 0, 0, 0, 0, 0, 0, 0],
    "Moody":        [3, 2, 0, -1, -2, -1, 0, 1, 2],
    "Chill":        [2, 2, 1, 0, -1, -2, -2, -1, 0],
    "BASS BOOST":   [8, 7, 5, 2, 0, 0, 0, 0, 0],
    "Treble Boost": [0, 0, 0, 0, 1, 2, 4, 6, 7],
    "Vocal Boost":  [-2, -1, 0, 2, 4, 5, 3, 1, 0],
    "Casual Game":  [2, 1, 0, 0, 1, 2, 1, 0, 1],
    "FPS Game":     [-1, -1, 0, 1, 2, 4, 5, 3, 1],
    "E-Sports Live":[0, 0, 1, 2, 3, 4, 3, 2, 2],
    "Sports Game":  [3, 2, 1, 0, 1, 2, 2, 1, 1],
    "Racing Game":  [6, 5, 3, 1, 0, 1, 2, 2, 2],
    "Movie":        [4, 3, 2, 1, 1, 2, 2, 2, 3],
    "Music":        [2, 1, 0, -1, 0, 1, 2, 3, 3],
}
LIGHT_EFFECTS = ["Breathing", "Solid", "Wave", "Glitch", "Spin CW", "Spin CCW", "Rise"]
LIGHT_SPEEDS = [("Slow", 0x28), ("Med-Low", 0x32), ("Medium", 0x3C), ("Med-High", 0x46),
                ("Fast", 0x4B), ("Faster", 0x50), ("Fastest", 0x64)]


def daemon_request(req, timeout=2.0):
    try:
        s = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)
        s.settimeout(timeout)
        s.connect(SOCKET_PATH)
        s.sendall((json.dumps(req) + "\n").encode())
        data = s.recv(65536).decode()
        s.close()
        return json.loads(data.strip())
    except Exception as e:
        return {"ok": False, "error": f"daemon unreachable: {e}"}


class QuantumUI(tk.Tk):
    def __init__(self, demo=False):
        super().__init__()
        self.title("QuantumENGINE — Linux")
        self.geometry("880x620")
        self.configure(bg=BG)
        self.demo = demo
        self.demo_state = {
            "present": True, "product": "JBL Quantum 810 Wireless", "battery": 87,
            "dial": 11, "anc": "on", "sidetone": "low", "lights": True,
            "auto_off_min": 60, "serial": "DEMO0810WRLSS00",
            "firmware": "1.2.7 / 0.9.4 / 2.1.0 / 1.0.3",
        }
        self.eq = {b: tk.DoubleVar(value=0.0) for b in EQ_BANDS}
        self.rgb = [tk.IntVar(value=0xFF), tk.IntVar(value=0x33), tk.IntVar(value=0x00)]
        self._build()
        self.after(1500, self._tick)

    # ---------- shell ----------
    def _build(self):
        style = ttk.Style(self)
        style.theme_use("clam")
        for name, bg, fg in [("TFrame", BG, TXT), ("Panel.TFrame", PANEL, TXT)]:
            style.configure(name, background=bg)
        style.configure(".", background=BG, foreground=TXT, fieldbackground=PANEL)
        style.configure("TLabel", background=BG, foreground=TXT)
        style.configure("Panel.TLabel", background=PANEL, foreground=TXT)
        style.configure("Dim.TLabel", background=BG, foreground=DIM)
        style.configure("Head.TLabel", font=("", 15, "bold"))
        style.configure("Sec.TLabel", font=("", 11, "bold"), foreground=ORANGE)
        style.configure("TRadiobutton", background=BG, foreground=TXT, focuscolor=BG)
        style.map("TRadiobutton", background=[("active", BG)])
        style.configure("TCheckbutton", background=BG, foreground=TXT, focuscolor=BG)
        style.map("TCheckbutton", background=[("active", BG)])
        style.configure("TNotebook", background=BG, borderwidth=0)
        style.configure("TNotebook.Tab", background=BG, foreground=DIM, padding=(14, 8))
        style.map("TNotebook.Tab", foreground=[("selected", TXT)],
                  background=[("selected", PANEL)])
        style.configure("Horizontal.TScale", background=BG, troughcolor=PANEL)
        style.configure("Accent.TButton", background=ORANGE, foreground="white")
        style.map("Accent.TButton", background=[("active", "#cc2a00")])

        # header
        head = ttk.Frame(self, style="Panel.TFrame")
        head.pack(fill="x")
        self.h_title = tk.Label(head, text="JBL QUANTUM 810 WIRELESS", bg=PANEL, fg=TXT,
                                font=("", 13, "bold"))
        self.h_title.pack(side="left", padx=16, pady=10)
        self.h_battery = tk.Label(head, text="", bg=PANEL, fg=ORANGE, font=("", 12, "bold"))
        self.h_battery.pack(side="right", padx=16)
        self.h_demo = ttk.Checkbutton(head, text="Demo UI (no headset needed)",
                                      command=self._toggle_demo)
        self.h_demo.pack(side="right", padx=8)
        self.demo_var = tk.BooleanVar(value=self.demo)
        self.h_demo.configure(variable=self.demo_var)
        self.h_state = tk.Label(head, text="", bg=PANEL, fg=DIM, font=("", 9))
        self.h_state.pack(side="right", padx=8)

        nb = ttk.Notebook(self)
        nb.pack(fill="both", expand=True, padx=10, pady=8)
        self.tab_sound = self._tab_sound(nb)
        self.tab_mic = self._tab_mic(nb)
        self.tab_ambient = self._tab_ambient(nb)
        self.tab_light = self._tab_light(nb)
        self.tab_dev = self._tab_device(nb)

        self.msg = ttk.Label(self, text="", style="Dim.TLabel", wraplength=820)
        self.msg.pack(fill="x", padx=14, pady=(0, 8))

    def _card(self, parent, title, note=None):
        c = tk.Frame(parent, bg=PANEL, padx=14, pady=10)
        c.pack(fill="x", pady=6, padx=2)
        tk.Label(c, text=title, bg=PANEL, fg=ORANGE, font=("", 10, "bold")).pack(anchor="w")
        if note:
            tk.Label(c, text=note, bg=PANEL, fg=DIM, font=("", 8)).pack(anchor="w")
        return c

    # ---------- tabs ----------
    def _tab_sound(self, nb):
        f = ttk.Frame(nb, style="TFrame")
        nb.add(f, text=" SOUND ")
        c1 = self._card(f, "Spatial sound",
                        "On Windows QuantumENGINE applies this as host-side DSP; on Linux this is "
                        "PipeWire (wiring pending). No dongle report exists for it — proven by capture.")
        self.spatial = tk.StringVar(value=SPATIAL_MODES[0])
        row = ttk.Frame(c1, style="Panel.TFrame"); row.pack(anchor="w")
        for m in SPATIAL_MODES:
            ttk.Radiobutton(row, text=m, variable=self.spatial, value=m,
                            command=lambda: self.set_local("spatial", self.spatial.get())
                            ).pack(side="left", padx=6)

        c2 = self._card(f, "Game & chat balance",
                        "Dial position 0 (all chat) … 16 (all game). Live mode is read-only: the "
                        "headset pushes its dial position; Windows sets it via unverified reports.")
        self.dial = tk.IntVar(value=11)
        s = ttk.Scale(c2, from_=0, to=16, variable=self.dial, command=lambda *_: None)
        s.pack(fill="x", padx=4)
        lr = ttk.Frame(c2, style="Panel.TFrame"); lr.pack(fill="x")
        tk.Label(lr, text="CHAT", bg=PANEL, fg=DIM).pack(side="left")
        self.dial_lbl = tk.Label(lr, text="11 / 16", bg=PANEL, fg=TXT)
        self.dial_lbl.place(relx=0.5, rely=0.5)
        tk.Label(lr, text="GAME", bg=PANEL, fg=DIM).pack(side="right")

        c3 = self._card(f, "Equalizer",
                        "Host-side EQ — on the 810 dongle the device applies no EQ (proven). "
                        "Linux wiring: PipeWire filter-chain (pending). Curve style mirrors the "
                        "QuantumENGINE EQ card; demo curves approximate the real presets.")
        # purple curve canvas, like the QE EQ card
        self.eq_canvas = tk.Canvas(c3, bg="#241f33", height=150, highlightthickness=0)
        self.eq_canvas.pack(fill="x", pady=4)
        pr = ttk.Frame(c3, style="Panel.TFrame"); pr.pack(fill="x")
        self.eq_preset = tk.StringVar(value="Default")
        cb = ttk.Combobox(pr, textvariable=self.eq_preset, values=EQ_PRESETS,
                          state="readonly", width=14)
        cb.pack(side="left", padx=4, pady=4)
        cb.bind("<<ComboboxSelected>>", lambda e: self._apply_preset())
        ttk.Button(pr, text="MORE >", command=lambda: self._toggle_bands()).pack(side="left", padx=4)
        ttk.Button(pr, text="Flatten", command=self._flatten).pack(side="left", padx=4)
        self.bands_frame = ttk.Frame(c3, style="Panel.TFrame")
        for b in EQ_BANDS:
            col = ttk.Frame(self.bands_frame, style="Panel.TFrame"); col.pack(side="left", padx=6)
            sc = ttk.Scale(col, from_=12, to=-12, variable=self.eq[b], length=110,
                           command=lambda *_: self._draw_eq())
            sc.pack()
            tk.Label(col, text=b, bg=PANEL, fg=DIM).pack()
        # hidden until MORE
        for v in self.eq.values():
            v.trace_add("write", lambda *_: self._draw_eq())
        self._draw_eq()
        return f

    def _toggle_bands(self):
        if self.bands_frame.winfo_ismapped():
            self.bands_frame.pack_forget()
        else:
            self.bands_frame.pack(fill="x", pady=6)

    def _draw_eq(self):
        c = self.eq_canvas
        c.delete("all")
        w = c.winfo_width() or 640
        h = 150
        n = len(EQ_BANDS)
        xs = [30 + i * (w - 60) / (n - 1) for i in range(n)]
        ys = [h / 2 - self.eq[b].get() * 5 for b in EQ_BANDS]
        # grid lines
        for gy in (h / 2,):
            c.create_line(20, gy, w - 20, gy, fill="#3a334f")
        for x in xs:
            c.create_line(x, 20, x, h - 25, fill="#2c2740")
        # smooth curve through points (catmull-rom)
        pts = []
        for i in range(n - 1):
            p0 = ys[i - 1] if i > 0 else ys[i]
            p1, p2 = ys[i], ys[i + 1]
            p3 = ys[i + 2] if i + 2 < n else ys[i + 1]
            for t in range(12):
                t /= 12
                t2, t3 = t * t, t * t * t
                y = 0.5 * ((2 * p1) + (-p0 + p2) * t + (2 * p0 - 5 * p1 + 4 * p2 - p3) * t2
                           + (-p0 + 3 * p1 - 3 * p2 + p3) * t3)
                pts.append((xs[i] + (xs[i + 1] - xs[i]) * t, y))
        flat = [c for p in pts for c in p]
        c.create_line(*flat, fill="#b57bff", width=3, smooth=True)
        for x, y in zip(xs, ys):
            c.create_oval(x - 3, y - 3, x + 3, y + 3, fill="#b57bff", outline="")
        for x, b in zip(xs, EQ_BANDS):
            c.create_text(x, h - 10, text=b, fill="#8a8f98", font=("", 8))

    def _tab_mic(self, nb):
        f = ttk.Frame(nb, style="TFrame")
        nb.add(f, text=" MICROPHONE ")
        c1 = self._card(f, "MIC ON/OFF",
                        "Device reports mic state (boom down AND unmuted) read-only; the physical "
                        "mute is on the headset. Live toggle disabled.")
        self.mic_on = tk.BooleanVar(value=False)
        ttk.Checkbutton(c1, text="Microphone active", variable=self.mic_on,
                        command=lambda: self.set_note("mic toggle is hardware-side on this model")
                        ).pack(anchor="w")

        c2 = self._card(f, "MIC GAIN", "No verified dongle report yet (pending).")
        self.mic_gain = tk.IntVar(value=70)
        ttk.Scale(c2, from_=0, to=100, variable=self.mic_gain,
                  command=lambda *_: None).pack(fill="x")

        c3 = self._card(f, "SIDETONE  (AUDIO/VOICE MONITOR)",
                        "4-step mic monitoring — device-verified feature report 0x5D.")
        self.sidetone = tk.StringVar(value="low")
        row = ttk.Frame(c3, style="Panel.TFrame"); row.pack(anchor="w")
        for v in ("off", "low", "mid", "high"):
            ttk.Radiobutton(row, text=v.upper(), variable=self.sidetone, value=v,
                            command=lambda: self.set_dev("sidetone", self.sidetone.get())
                            ).pack(side="left", padx=8)

        c4 = self._card(f, "MIC EQ", "Host-side mic EQ (pending).")
        self.mic_eq = tk.StringVar(value="Default")
        ttk.Combobox(c4, textvariable=self.mic_eq, values=["Default", "Bright", "Warm"],
                     state="readonly", width=12).pack(anchor="w")
        return f

    def _tab_ambient(self, nb):
        f = ttk.Frame(nb, style="TFrame")
        nb.add(f, text=" AMBIENT SOUND CONTROL ")
        c1 = self._card(f, "ANC / AA / Off", "Device-verified feature report 0x46 (0=off 1=ANC 2=TalkThru/AA).")
        self.anc = tk.StringVar(value="on")
        row = ttk.Frame(c1, style="Panel.TFrame"); row.pack(anchor="w", pady=4)
        for v, label in (("off", "OFF"), ("on", "ANC"), ("talkthru", "AMBIENT AWARE")):
            ttk.Radiobutton(row, text=label, variable=self.anc, value=v,
                            command=lambda: self.set_dev("anc", self.anc.get())
                            ).pack(side="left", padx=14)
        c2 = self._card(f, "AMBIENT AWARE level", "Passthrough gain — RACE-level command exists in "
                        "QuantumENGINE (SetAncPassThruGain), no verified dongle report yet (pending).")
        self.aa_gain = tk.IntVar(value=50)
        ttk.Scale(c2, from_=0, to=100, variable=self.aa_gain,
                  command=lambda *_: None).pack(fill="x")
        return f

    def _tab_light(self, nb):
        f = ttk.Frame(nb, style="TFrame")
        nb.add(f, text=" LIGHTING ")
        c1 = self._card(f, "Lighting master", "Device-verified report 0x4B.")
        self.lights = tk.BooleanVar(value=True)
        ttk.Checkbutton(c1, text="Lighting on", variable=self.lights,
                        command=lambda: self.set_dev("lights", self.lights.get())
                        ).pack(anchor="w")

        c2 = self._card(f, "Zone / effect / colour", "Device-verified reports 0x4C/0x4D. "
                        "Zones: logo + ring (L/R mirrored in hardware). Safety: segments 1–5 "
                        "hard-clamped — more wedges the lighting MCU.")
        row1 = ttk.Frame(c2, style="Panel.TFrame"); row1.pack(anchor="w", pady=2)
        tk.Label(row1, text="Zone", bg=PANEL, fg=TXT).pack(side="left")
        self.zone = tk.StringVar(value="Logo")
        ttk.Combobox(row1, textvariable=self.zone, values=["Logo", "Ring"],
                     state="readonly", width=8).pack(side="left", padx=6)
        tk.Label(row1, text="Effect", bg=PANEL, fg=TXT).pack(side="left", padx=(16, 0))
        self.effect = tk.StringVar(value="Solid")
        ttk.Combobox(row1, textvariable=self.effect, values=LIGHT_EFFECTS,
                     state="readonly", width=10).pack(side="left", padx=6)
        tk.Label(row1, text="Speed", bg=PANEL, fg=TXT).pack(side="left", padx=(16, 0))
        self.speed = tk.StringVar(value="Medium")
        ttk.Combobox(row1, textvariable=self.speed,
                     values=[n for n, _ in LIGHT_SPEEDS], state="readonly", width=9
                     ).pack(side="left", padx=6)

        row2 = ttk.Frame(c2, style="Panel.TFrame"); row2.pack(anchor="w", pady=2)
        for i, ch in enumerate(("R", "G", "B")):
            tk.Label(row2, text=ch, bg=PANEL, fg=TXT).pack(side="left")
            ttk.Scale(row2, from_=0, to=255, variable=self.rgb[i], length=120,
                      command=lambda *_: None).pack(side="left", padx=4)
        self.preview = tk.Label(row2, text="   ", bg="#ff3300")
        self.preview.pack(side="left", padx=10)
        for v in self.rgb:
            v.trace_add("write", lambda *_: self._preview())
        ttk.Button(row2, text="Apply colour", style="Accent.TButton",
                   command=self._apply_colour).pack(side="left", padx=8)

        row3 = ttk.Frame(c2, style="Panel.TFrame"); row3.pack(anchor="w", pady=2)
        tk.Label(row3, text="Segments (1–5)", bg=PANEL, fg=TXT).pack(side="left")
        self.segments = tk.IntVar(value=5)
        ttk.Spinbox(row3, from_=1, to=5, textvariable=self.segments, width=4).pack(side="left", padx=6)
        ttk.Button(row3, text="Apply zone config", style="Accent.TButton",
                   command=self._apply_zone).pack(side="left", padx=8)
        return f

    def _tab_device(self, nb):
        f = ttk.Frame(nb, style="TFrame")
        nb.add(f, text=" DEVICE ")
        c1 = self._card(f, "Auto power off", "Device-verified report 0x75 — 5-minute units, "
                        "verify-by-readback, no ACK event.")
        self.autoff = tk.StringVar(value="60")
        row = ttk.Frame(c1, style="Panel.TFrame"); row.pack(anchor="w")
        for v in ("0", "30", "60", "120"):
            ttk.Radiobutton(row, text=("Never" if v == "0" else f"{v} min"),
                            variable=self.autoff, value=v,
                            command=lambda: self.set_dev("auto_off", int(self.autoff.get()))
                            ).pack(side="left", padx=10)

        c2 = self._card(f, "Info")
        self.info_lbl = tk.Label(c2, text="", bg=PANEL, fg=TXT, justify="left",
                                 font=("TkFixedFont", 10))
        self.info_lbl.pack(anchor="w")

        c3 = self._card(f, "Maintenance")
        ttk.Button(c3, text="Restore factory settings (undo our writes)",
                   command=self._restore).pack(anchor="w", pady=2)
        tk.Label(c3, text="Restores the values captured before this session's writes. "
                          "Never touches firmware (DFU reports are unreachable by design).",
                 bg=PANEL, fg=DIM, font=("", 8), wraplength=700, justify="left").pack(anchor="w")
        return f

    # ---------- behaviour ----------
    def _preview(self):
        self.preview.config(bg="#%02x%02x%02x" % tuple(min(255, max(0, v.get())) for v in self.rgb))

    def _apply_preset(self):
        curve = EQ_CURVES.get(self.eq_preset.get())
        if curve:
            for b, db in zip(EQ_BANDS, curve):
                self.eq[b].set(float(db))
        self._draw_eq()
        self.flash(f"EQ preset '{self.eq_preset.get()}' — host-side (PipeWire pending)")

    def _flatten(self):
        for v in self.eq.values():
            v.set(0.0)
        self._draw_eq()
        self.flash("EQ flattened (host-side)")

    def _apply_colour(self):
        rgb = [min(255, max(0, v.get())) for v in self.rgb]
        self.set_dev("light_colour", {"element": 0 if self.zone.get() == "Logo" else 1,
                                      "slot": 0, "rgb": rgb,
                                      "mode": LIGHT_EFFECTS.index(self.effect.get()),
                                      "last": 0})

    def _apply_zone(self):
        speed = dict(LIGHT_SPEEDS)[self.speed.get()]
        self.set_dev("light_zone", {"element": 0 if self.zone.get() == "Logo" else 1,
                                    "speed": speed,
                                    "segments": min(5, max(1, self.segments.get()))})

    def _restore(self):
        if self.demo:
            self.flash("demo — nothing sent to hardware")
            return
        import subprocess, sys
        out = subprocess.run([sys.executable, os.path.join(os.path.dirname(__file__), "jblq"),
                              "restore"], capture_output=True, text=True, timeout=15)
        self.flash(out.stdout.strip() or out.stderr.strip() or "restore done")

    def _toggle_demo(self):
        self.demo = self.demo_var.get()

    def set_local(self, feature, value):
        if self.demo:
            self.demo_state[feature if feature != "lights" else "lights"] = value
            self.flash(f"{feature} → {value}  (demo — nothing sent to hardware)", "#e6b450")
        else:
            self.flash(f"{feature} is host-side — PipeWire wiring pending", "#e6b450")

    def set_note(self, text):
        self.flash(text, "#e6b450")

    def set_dev(self, feature, value):
        if self.demo:
            key = {"sidetone": "sidetone", "anc": "anc", "lights": "lights",
                   "auto_off": "auto_off_min"}.get(feature)
            if key:
                self.demo_state[key] = value * 5 if feature == "auto_off" else value
            self.flash(f"{feature} → {value}  (demo — nothing sent to hardware)", "#e6b450")
            return
        payload = value
        if feature == "auto_off":
            payload = int(value)  # minutes; daemon converts to 5-min units
        resp = daemon_request({"cmd": "set", "feature": feature, "value": payload})
        if resp.get("ok"):
            self.flash(f"{feature} → {value}", "#7bd88f")
            daemon_request({"cmd": "refresh"})
        else:
            self.flash(resp.get("error", "write failed"), "#f05e5e")

    def flash(self, text, color=None):
        self.msg.config(text=text, foreground=color or DIM)

    def _tick(self):
        st = daemon_request({"cmd": "state"})
        live = bool(st.get("present"))
        if self.demo and not live:
            st = dict(self.demo_state)
        elif not live:
            st = {"present": False}
        demo = self.demo and not live

        if not st.get("present"):
            self.h_title.config(text="JBL QUANTUM — NO HEADSET DETECTED")
            self.h_battery.config(text="")
            self.h_state.config(text="plug in the dongle — auto-connects")
            self.info_lbl.config(text="No headset detected.\nPlug in the Quantum 810 wireless dongle.")
            self.after(2000, self._tick)
            return

        self.h_title.config(text=st.get("product", "JBL Quantum").upper() + ("   ·   DEMO" if demo else ""))
        self.h_battery.config(text=f"{st.get('battery', '—')}%")
        self.h_state.config(text="demo data" if demo else "live device")

        anc = st.get("anc"); sid = st.get("sidetone")
        if anc in ("off", "on", "talkthru"):
            self.anc.set(anc)
        if sid in ("off", "low", "mid", "high"):
            self.sidetone.set(sid)
        self.lights.set(bool(st.get("lights")))
        self.dial.set(st.get("dial") or 0)
        self.dial_lbl.config(text=f"{st.get('dial', '—')} / 16")
        aom = st.get("auto_off_min")
        if aom is not None:
            self.autoff.set(str(aom))
        self.info_lbl.config(text=(
            f"product   : {st.get('product', '—')}\n"
            f"battery   : {st.get('battery', '—')}%\n"
            f"serial    : {st.get('serial', '—')}\n"
            f"firmware  : {st.get('firmware', '—')}\n"
            f"auto-off  : {st.get('auto_off_min', '—')} min\n"
            f"dial      : {st.get('dial', '—')}/16"))
        self.after(2000, self._tick)


if __name__ == "__main__":
    QuantumUI(demo="--demo" in sys.argv).mainloop()
