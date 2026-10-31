#!/usr/bin/env python3
"""JBL Quantum Engine — Windows edition (PyQt6).

Windows port of the Linux app (repo root app/jblq_gui.py + jblq_daemon.py), rebuilt to
match the REAL QuantumENGINE Windows UI (reference screenshots, E:\\quantum engine pics):
frameless dark window, left avatar rail, MY PRODUCTS home screen, device dashboard with
EQUALIZER / SPATIAL SOUND / MICROPHONE / AMBIENT SOUND CONTROL / LIGHTING / SUPPORT cards,
SPATIAL SOUND detail page with the head-sphere visualiser, and the 5-step onboarding tour.

Differences from the Linux app (deliberate, Windows-specific):
  * No unix-socket daemon — this process owns the control-HID handle directly. All HID
    I/O runs on a DeviceWorker QThread so a wedged feature-report can never freeze the UI.
  * Same shared engine: imports app/jbl_quantum.py (one protocol implementation, no drift).
  * System volume via pycaw when available (the Linux app used pactl).
  * Charging stays INFERENCE (battery trend) — the dongle has no charging flag (verified).

Honesty rules carried over unchanged:
  * Only verified reports (0x45–0x75) are sent to the device; unknown/DFU ids unreachable.
  * EQ / Quantum Spatial / DTS are HOST-SIDE in the real app (captures prove the dongle
    receives nothing) — here they are working UI state, clearly labelled, never faked.
  * Demo mode never sends anything; every write surface is disabled without a device.
"""
from __future__ import annotations

import json
import os
import queue
import sys
import time

from PyQt6.QtCore import (Qt, QTimer, QRectF, QPointF, QPoint, QThread, pyqtSignal,
                          QSettings)
from PyQt6.QtGui import (QColor, QFont, QIcon, QPainter, QPen, QBrush, QPixmap,
                         QLinearGradient, QRadialGradient, QPainterPath, QCursor,
                         QAction, QActionGroup)
from PyQt6.QtWidgets import (
    QApplication, QWidget, QLabel, QPushButton, QComboBox, QSlider, QVBoxLayout,
    QHBoxLayout, QGridLayout, QStackedWidget, QLineEdit, QFrame, QScrollArea,
    QMenu, QSizePolicy, QInputDialog,
)

# import the shared engine from app/ (single protocol implementation for both OSes)
_APP_DIR = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
if _APP_DIR not in sys.path:
    sys.path.insert(0, _APP_DIR)
from jbl_quantum import (  # noqa: E402
    QuantumHeadset, JblError, DeviceNotFound, UnsupportedDevice,
    ANC_MODES, SIDETONE_LEVELS, LIGHT_BRIGHTNESS,
)
import spatial_win  # noqa: E402  (real host-side spatial sound — see spatial_win.py)

APP_NAME = "JBL Quantum Engine"
APP_VERSION = "1.2.0"
DATA_DIR = os.path.join(os.environ.get("LOCALAPPDATA", os.path.expanduser("~")), "jblq")
PROFILE_FILE = os.path.join(DATA_DIR, "profiles.json")
SETTINGS = QSettings("jblq", "quantum-engine-win")

# ---------------- palette (sampled from the reference screenshots) ----------------
BG = "#0a0710"
BG_HOME = "#050307"
CARD = "#262130"
CARD_2 = "#2e2839"
CARD_BORDER = "#332b42"
WHITE = "#f2f2f4"
GREY = "#9b93a8"
DARKGREY = "#6b637c"
PURPLE = "#6f4ff2"
PURPLE_2 = "#8f6bff"
PURPLE_DEEP = "#5b3fd6"
PINK = "#e05ce8"
RED = "#e8262d"
AMBER = "#e6b450"
GREEN = "#4ade80"
CYAN = "#37d6e0"

EQ_BANDS = ["31", "62", "125", "250", "500", "1k", "2k", "4k", "8k", "16k"]
EQ_PRESETS = {
    "FLAT":       [0] * 10,
    "RPG":        [2, 1, 0, 0, 1, 2, 3, 4, 3, 2],
    "FPS":        [-1, -1, 0, 1, 2, 4, 5, 3, 1, 0],
    "WARZONE":    [5, 2, 2, 4, 5, 1, 2, 5, 9, 10],
    "MOODY":      [3, 2, 0, -1, -2, -1, 0, 1, 2, 2],
    "CHILL":      [2, 2, 1, 0, -1, -2, -2, -1, 0, 0],
    "BASS BOOST": [8, 7, 5, 2, 0, 0, 0, 0, 0, 0],
    "VOCAL":      [-2, -1, 0, 2, 4, 5, 3, 1, 0, 0],
}
LIGHT_PRESETS = ["SOLID", "BREATH", "WAVE", "GLITCH", "SPIN CW", "SPIN CCW", "RISE"]
# colour-frame mode byte per preset (jbl_quantum.set_light_colour mode 0..6)
LIGHT_MODE_BYTE = {0: 1, 1: 0, 2: 2, 3: 3, 4: 4, 5: 5, 6: 6}
LIGHT_BRIGHTNESS_STEPS = [40, 50, 60, 70, 75, 80, 100]
SIDETONE_STEPS = ["OFF", "LOW", "MID", "HIGH"]
ROOM_SIZES = ["Small", "Medium", "Large"]

HOST_SIDE_NOTE = ("host-side: the real app applies this on the PC — the dongle receives "
                  "nothing (capture-proven). Saved locally.")


def load_json(path, default):
    try:
        with open(path) as f:
            return json.load(f)
    except Exception:
        return default


def save_json(path, data):
    os.makedirs(os.path.dirname(path), exist_ok=True)
    with open(path, "w") as f:
        json.dump(data, f, indent=1)


# ---------------- device worker (all HID I/O off the UI thread) ----------------
class DeviceWorker(QThread):
    """Owns the QuantumHeadset handle; runs jobs queued by the UI thread.

    A feature-report GET with a misbehaving device can block indefinitely — that must
    never take the UI down (the Linux daemon needed a rewrite for exactly this class of
    bug, see SESSION-HANDOFF §14). One wedged job stalls only this thread; the UI shows
    'device busy' and keeps working. Re-enumeration happens on the next job after any
    DeviceNotFound (the dongle re-enumerates when the headset sleeps/wakes).
    """
    got = pyqtSignal(str, object)

    def __init__(self):
        super().__init__()
        self.q: queue.Queue = queue.Queue()
        self.hs: QuantumHeadset | None = None
        self._last_batt: int | None = None
        self.charging = False  # sticky inference (battery trend), ported from the daemon

    def submit(self, name: str, fn):
        self.q.put((name, fn))

    def quit_loop(self):
        self.q.put(("__quit__", None))

    # -- helpers run inside the worker thread ---------------------------------
    def _ensure(self) -> QuantumHeadset:
        if self.hs is None:
            self.hs = QuantumHeadset.find()
        return self.hs

    def _refresh_handle(self):
        if self.hs is not None:
            self.hs.close()
            self.hs = None

    def _state_job(self, w: "DeviceWorker"):
        try:
            hs = self._ensure()
        except (DeviceNotFound, UnsupportedDevice) as e:
            return {"present": False, "error": str(e)}
        except Exception as e:
            return {"present": False, "error": str(e)}
        try:
            snap = hs.snapshot()
            batt = snap.battery
            if batt is not None and self._last_batt is not None:
                if batt > self._last_batt:
                    self.charging = True
                elif batt < self._last_batt or batt >= 100:
                    self.charging = batt >= 100
            self._last_batt = batt
            out = {"present": True, "error": None,
                   "product": snap.product, "battery": snap.battery,
                   "charging": self.charging, "dial": snap.dial,
                   "anc": snap.anc, "sidetone": snap.sidetone, "lights": snap.lights,
                   "serial": snap.serial, "firmware": snap.firmware,
                   "mic": hs.get_mic_active()}
            if snap.auto_off is not None and len(snap.auto_off) > 1:
                out["auto_off_min"] = snap.auto_off[1] * 5
            return out
        except Exception as e:
            # device likely re-enumerated (sleep/wake) — drop the handle, retry next tick
            self._refresh_handle()
            return {"present": False, "error": str(e)}

    def _set_job(self, feature: str, value):
        def job(w: "DeviceWorker"):
            try:
                hs = self._ensure()
            except Exception as e:
                return {"ok": False, "error": str(e)}
            try:
                if feature == "anc":
                    hs.set_anc(int(value))
                elif feature == "sidetone":
                    hs.set_sidetone(int(value))
                elif feature == "lights":
                    hs.set_lights(bool(value))
                elif feature == "light_zone":
                    hs.set_light_zone(int(value["element"]), int(value["brightness"]),
                                      int(value["segments"]))
                elif feature == "light_colour":
                    hs.set_light_colour(int(value["element"]), int(value["slot"]),
                                        tuple(value["rgb"]), int(value["mode"]),
                                        int(value["last"]))
                elif feature == "auto_off":
                    hs.set_auto_off(int(value))
                else:
                    return {"ok": False, "error": f"unknown feature {feature}"}
                return {"ok": True}
            except Exception as e:
                return {"ok": False, "error": str(e)}
        return job

    def _restore_job(self, w: "DeviceWorker"):
        try:
            hs = self._ensure()
        except Exception as e:
            return {"error": str(e)}
        try:
            return {"restored": hs.restore_originals()}
        except Exception as e:
            return {"error": str(e)}

    def run(self):
        while True:
            name, payload = self.q.get()
            if name == "__quit__":
                break
            try:
                if name == "state":
                    r = self._state_job(self)
                elif name == "set":
                    feature, value = payload
                    r = self._set_job(feature, value)(self)
                elif name == "restore":
                    r = self._restore_job(self)
                elif name == "spatial":
                    fmt = payload
                    if fmt == spatial_win.DTS_NAME:
                        r = spatial_win.set_spatial(fmt)
                        if r.get("ok"):
                            r["mode"] = spatial_win.DTS_NAME
                        else:
                            # no DTS licence on this machine — Sonic is the real
                            # fallback, reported honestly
                            r2 = spatial_win.set_spatial(spatial_win.SONIC)
                            r = {**r2, "fallback": True, "dts_error": r.get("error"),
                                 "mode": spatial_win.SONIC}
                    else:
                        r = spatial_win.set_spatial(fmt)
                        r["mode"] = fmt if fmt else "off"
                elif name == "spatial_state":
                    r = spatial_win.get_spatial()
                else:
                    r = {"error": f"unknown job {name}"}
            except Exception as e:  # never let a job kill the thread
                r = {"error": f"worker: {e}"}
            self.got.emit(name, r)


# ---------------- custom widgets ----------------

class Toggle(QWidget):
    """Purple pill toggle (the real app's switch)."""
    def __init__(self, checked=True, on_change=None):
        super().__init__()
        self.checked = checked
        self.on_change = on_change
        self.setFixedSize(40, 22)
        self.setCursor(Qt.CursorShape.PointingHandCursor)

    def set_checked(self, v, notify=False):
        if v != self.checked:
            self.checked = v
            self.update()
            if notify and self.on_change:
                self.on_change(v)

    def mousePressEvent(self, _):
        self.checked = not self.checked
        self.update()
        if self.on_change:
            self.on_change(self.checked)

    def paintEvent(self, _):
        p = QPainter(self)
        p.setRenderHint(QPainter.RenderHint.Antialiasing)
        p.setPen(Qt.PenStyle.NoPen)
        p.setBrush(QBrush(QColor(PURPLE if self.checked else "#3a3348")))
        p.drawRoundedRect(QRectF(0, 0, self.width(), self.height()), 11, 11)
        p.setBrush(QBrush(QColor("white")))
        x = self.width() - 18 if self.checked else 4
        p.drawEllipse(QRectF(x, 3, 16, 16))


class Segmented(QWidget):
    """Two-option segmented selector (Quantum Spatial | dts, ANC | TalkThru)."""
    def __init__(self, options, index=0, on_change=None, glyphs=None):
        super().__init__()
        self.options = options
        self.glyphs = glyphs or [None] * len(options)
        self.index = index
        self.on_change = on_change
        self.setFixedHeight(56)
        self.setMinimumWidth(240)
        self.setCursor(Qt.CursorShape.PointingHandCursor)

    def set_index(self, i, notify=False):
        if i != self.index:
            self.index = i
            self.update()
            if notify and self.on_change:
                self.on_change(i)

    def _seg_at(self, x):
        n = len(self.options)
        return max(0, min(n - 1, int(x / max(1, self.width()) * n)))

    def mousePressEvent(self, e):
        i = self._seg_at(e.position().x())
        if i != self.index:
            self.index = i
            self.update()
            if self.on_change:
                self.on_change(i)

    def paintEvent(self, _):
        p = QPainter(self)
        p.setRenderHint(QPainter.RenderHint.Antialiasing)
        n = len(self.options)
        sw = self.width() / n
        p.setPen(Qt.PenStyle.NoPen)
        p.setBrush(QBrush(QColor("#171221")))
        p.drawRoundedRect(QRectF(0, 0, self.width(), self.height()), 8, 8)
        # selected segment
        p.setBrush(QBrush(QColor(PURPLE_DEEP)))
        p.drawRoundedRect(QRectF(self.index * sw + 3, 3, sw - 6, self.height() - 6), 6, 6)
        f = QFont("Segoe UI", 11)
        f.setBold(True)
        p.setFont(f)
        for i, opt in enumerate(self.options):
            cx = int(i * sw + sw / 2)
            cy = int(self.height() / 2)
            p.setPen(QPen(QColor("white" if i == self.index else GREY), 1))
            if self.glyphs[i]:
                p.drawText(QRectF(i * sw, 6, sw, self.height() - 24),
                           Qt.AlignmentFlag.AlignCenter, self.glyphs[i])
                p.setFont(QFont("Segoe UI", 7))
                p.drawText(QRectF(i * sw, self.height() - 22, sw, 18),
                           Qt.AlignmentFlag.AlignCenter, opt)
                p.setFont(f)
            else:
                p.drawText(QRectF(i * sw, 0, sw, self.height()),
                           Qt.AlignmentFlag.AlignCenter, opt)


class Pill(QPushButton):
    """Purple gradient dropdown pill (FLAT / SOUND IS SURVIVAL / …)."""
    def __init__(self, text, items=None, on_pick=None):
        super().__init__("  " + text)
        self.items = list(items) if items else None
        self.on_pick = on_pick
        self.setFixedHeight(40)
        self.setCursor(Qt.CursorShape.PointingHandCursor)
        self.setStyleSheet(
            "QPushButton { background: qlineargradient(x1:0,y1:0,x2:1,y2:0,"
            " stop:0 #6f4ff2, stop:1 #5531d6); color: white; border: none;"
            " border-radius: 9px; font-size: 12px; font-weight: bold; text-align: left;"
            " padding-left: 14px; padding-right: 30px; }"
            "QPushButton:hover { background: qlineargradient(x1:0,y1:0,x2:1,y2:0,"
            " stop:0 #8f6bff, stop:1 #6a3fe8); }"
            "QToolTip { color: white; background: #262130; border: 1px solid #3a3348; }")

    def text_value(self):
        return self.text().strip()

    def set_value(self, name):
        self.setText("  " + name)

    def mousePressEvent(self, e):
        if not self.items or not self.on_pick:
            return
        m = QMenu(self)
        m.setStyleSheet(
            "QMenu { background: #262130; color: #f2f2f4; border: 1px solid #3a3348;"
            " border-radius: 8px; padding: 4px; }"
            "QMenu::item { padding: 6px 24px 6px 12px; border-radius: 5px; }"
            "QMenu::item:selected { background: #6f4ff2; }")
        for name in self.items:
            act = m.addAction(name)
            act.triggered.connect(lambda _, n=name: (self.set_value(n), self.on_pick(n)))
        m.exec(e.globalPosition().toPoint())


class Card(QFrame):
    """Rounded dark card with title header, optional toggle and MORE › footer."""
    def __init__(self, title, toggle_cb=None):
        super().__init__()
        self.setObjectName("card")
        self.setStyleSheet(
            f"#card {{ background: {CARD}; border-radius: 14px; border: 1px solid {CARD_BORDER}; }}")
        self.v = QVBoxLayout(self)
        self.v.setContentsMargins(16, 14, 16, 10)
        self.v.setSpacing(10)
        head = QWidget()
        hh = QHBoxLayout(head)
        hh.setContentsMargins(0, 0, 0, 0)
        t = QLabel(title)
        t.setStyleSheet(f"color: {WHITE}; font-size: 12px; font-weight: bold; letter-spacing: 1.2px;")
        hh.addWidget(t)
        hh.addStretch(1)
        if toggle_cb:
            self.toggle = Toggle(True, toggle_cb)
            hh.addWidget(self.toggle)
        self.v.addWidget(head)

    def add_more(self, cb, label="MORE"):
        row = QWidget()
        rh = QHBoxLayout(row)
        rh.setContentsMargins(0, 0, 0, 0)
        rh.addStretch(1)
        more = QLabel(label + "  ›")
        more.setStyleSheet(f"color: {DARKGREY}; font-size: 10px; letter-spacing: 1px; font-weight: bold;")
        more.setCursor(Qt.CursorShape.PointingHandCursor)
        more.mousePressEvent = lambda _: cb()
        rh.addWidget(more)
        self.v.addWidget(row)
        return more

    def tour_name(self):
        return self.findChild(QLabel).text()


class EqCurve(QWidget):
    """Magenta smooth EQ curve with draggable 10-band control."""
    def __init__(self, values):
        super().__init__()
        self.values = values
        self.on_change = None
        self.setMinimumHeight(140)
        self.setMouseTracking(True)

    def _band_at(self, x):
        n = len(self.values)
        x0, x1 = 16, self.width() - 16
        return max(0, min(n - 1, round((x - x0) / (x1 - x0) * (n - 1))))

    def mousePressEvent(self, e):
        self._drag(e)

    def mouseMoveEvent(self, e):
        if e.buttons() & Qt.MouseButton.LeftButton:
            self._drag(e)

    def _drag(self, e):
        i = self._band_at(e.position().x())
        y0, y1 = 10, self.height() - 26
        v = 10 - (e.position().y() - y0) / max(1, (y1 - y0)) * 20
        self.values[i] = max(-10.0, min(10.0, round(v * 2) / 2))
        self.update()
        if self.on_change:
            self.on_change()

    def paintEvent(self, _):
        p = QPainter(self)
        p.setRenderHint(QPainter.RenderHint.Antialiasing)
        w, h = self.width(), self.height()
        n = len(self.values)
        x0, x1 = 16, w - 16
        ytop, ybot = 10, h - 26
        # faint vertical band guides
        p.setPen(QPen(QColor("#241e30"), 1))
        for i in range(n):
            x = x0 + i * (x1 - x0) / (n - 1)
            p.drawLine(int(x), ytop, int(x), ybot)
        p.setPen(QPen(QColor("#3a3348"), 1))
        p.drawLine(int(x0), int((ytop + ybot) / 2), int(x1), int((ytop + ybot) / 2))
        xs = [x0 + i * (x1 - x0) / (n - 1) for i in range(n)]
        ys = [ytop + (10 - v) / 20 * (ybot - ytop) for v in self.values]
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
        p.setPen(QPen(QColor(PINK), 3))
        p.drawPolyline(*[QPointF(a, b) for a, b in pts])
        p.setBrush(QBrush(QColor(PINK)))
        p.setPen(Qt.PenStyle.NoPen)
        for x, y in zip(xs, ys):
            p.drawEllipse(QPointF(x, y), 2.8, 2.8)
        p.setPen(QPen(QColor(GREY), 1))
        p.setFont(QFont("Segoe UI", 7))
        for x, b in zip(xs, EQ_BANDS):
            p.drawText(QRectF(x - 16, ybot + 4, 32, 14), Qt.AlignmentFlag.AlignHCenter, b)


class ColorSlider(QWidget):
    """Hue strip with a white position marker."""
    def __init__(self, on_change=None):
        super().__init__()
        self.hue = 0.95
        self.on_change = on_change
        self.setFixedHeight(18)
        self.setCursor(Qt.CursorShape.PointingHandCursor)

    def set_hue(self, h):
        self.hue = max(0.0, min(1.0, h))
        self.update()

    def mousePressEvent(self, e):
        self.hue = max(0.0, min(1.0, e.position().x() / max(1, self.width())))
        self.update()
        if self.on_change:
            self.on_change(self.hue)

    def mouseMoveEvent(self, e):
        if e.buttons() & Qt.MouseButton.LeftButton:
            self.mousePressEvent(e)

    def paintEvent(self, _):
        p = QPainter(self)
        p.setRenderHint(QPainter.RenderHint.Antialiasing)
        grad = QLinearGradient(0, 0, self.width(), 0)
        for i in range(7):
            grad.setColorAt(i / 6, QColor.fromHsvF(i / 6, 1, 1))
        p.setPen(Qt.PenStyle.NoPen)
        p.setBrush(QBrush(grad))
        p.drawRoundedRect(QRectF(0, 2, self.width(), self.height() - 4), 8, 8)
        p.setPen(QPen(QColor(WHITE), 2.4))
        x = self.hue * self.width()
        p.drawLine(int(x), 1, int(x), self.height() - 1)


class StopSlider(QWidget):
    """Discrete-stop slider drawn like the real app (labelled ends, purple fill).

    Used for side tone (4 steps), room size (3 stops) and head diameter (11 stops).
    """
    def __init__(self, stops, index=0, on_change=None, labels=None):
        super().__init__()
        self.stops = stops
        self.index = index
        self.on_change = on_change
        self.labels = labels or [None] * len(stops)
        self.setFixedHeight(44)
        self.setMinimumWidth(200)
        self.setCursor(Qt.CursorShape.PointingHandCursor)

    def set_index(self, i, notify=False):
        i = max(0, min(len(self.stops) - 1, i))
        if i != self.index:
            self.index = i
            self.update()
            if notify and self.on_change:
                self.on_change(self.stops[i], i)

    def _index_at(self, x):
        n = len(self.stops)
        return max(0, min(n - 1, round(x / max(1, self.width()) * (n - 1))))

    def mousePressEvent(self, e):
        self.set_index(self._index_at(e.position().x()), notify=True)

    def mouseMoveEvent(self, e):
        if e.buttons() & Qt.MouseButton.LeftButton:
            self.mousePressEvent(e)

    def paintEvent(self, _):
        p = QPainter(self)
        p.setRenderHint(QPainter.RenderHint.Antialiasing)
        w, h = self.width(), self.height()
        y = h / 2 - 4
        n = len(self.stops)
        p.setPen(QPen(QColor("#3a3348"), 3, Qt.PenStyle.SolidLine, Qt.PenCapStyle.RoundCap))
        p.drawLine(8, int(y), w - 8, int(y))
        if self.index > 0:
            p.setPen(QPen(QColor(PURPLE_2), 3, Qt.PenStyle.SolidLine, Qt.PenCapStyle.RoundCap))
            p.drawLine(8, int(y), int(8 + (w - 16) * self.index / (n - 1)), int(y))
        for i in range(n):
            x = 8 + (w - 16) * i / (n - 1)
            if i == self.index:
                p.setPen(Qt.PenStyle.NoPen)
                p.setBrush(QBrush(QColor("white")))
                p.drawEllipse(QPointF(x, y), 7, 7)
            elif i <= self.index:
                p.setBrush(QBrush(QColor(PURPLE_2)))
                p.drawEllipse(QPointF(x, y), 5, 5)
            else:
                p.setBrush(Qt.BrushStyle.NoBrush)
                p.setPen(QPen(QColor(DARKGREY), 1.6))
                p.drawEllipse(QPointF(x, y), 5, 5)
        p.setPen(QPen(QColor(GREY), 1))
        p.setFont(QFont("Segoe UI", 7))
        for i, lab in enumerate(self.labels):
            if lab:
                p.drawText(QRectF(8 + (w - 16) * i / (n - 1) - 60, h - 16, 120, 14),
                           Qt.AlignmentFlag.AlignHCenter, lab)


class DialDots(QWidget):
    """game/chat dial indicator (0..16 → 10 dots)."""
    def __init__(self):
        super().__init__()
        self.value = 11
        self.setFixedHeight(22)

    def set_value(self, v):
        self.value = v or 0
        self.update()

    def paintEvent(self, _):
        p = QPainter(self)
        p.setRenderHint(QPainter.RenderHint.Antialiasing)
        n, gap = 10, 13
        w, h = self.width(), self.height()
        x0 = (w - n * gap) / 2 + gap / 2
        filled = round(self.value / 16 * n)
        for i in range(n):
            x = x0 + i * gap
            p.setBrush(QBrush(QColor(PURPLE_2 if i < filled else "#3a3348")))
            p.setPen(Qt.PenStyle.NoPen)
            p.drawEllipse(QPointF(x, h / 2), 3.4, 3.4)


def draw_headset(p: QPainter, cx: float, cy: float, s: float, color=WHITE):
    """Stylised Quantum 810 side profile (drawn, no JBL image assets shipped)."""
    p.save()
    pen = QPen(QColor(color), 2.6 * s)
    p.setPen(pen)
    p.setBrush(Qt.BrushStyle.NoBrush)
    # headband
    path = QPainterPath()
    path.moveTo(cx - 44 * s, cy + 6 * s)
    path.cubicTo(cx - 54 * s, cy - 66 * s, cx + 54 * s, cy - 66 * s, cx + 44 * s, cy + 6 * s)
    p.drawPath(path)
    # cups
    for sx in (-1, 1):
        ex = cx + sx * 56 * s
        p.setBrush(QBrush(QColor("#141019")))
        p.setPen(QPen(QColor(color), 2.2 * s))
        p.drawEllipse(QPointF(ex, cy + 22 * s), 22 * s, 30 * s)
        p.setPen(QPen(QColor("#3a3348"), 1.6 * s))
        p.drawEllipse(QPointF(ex, cy + 22 * s), 13 * s, 20 * s)
        # yoke arm
        p.setPen(QPen(QColor(color), 2.2 * s))
        p.drawLine(int(ex), int(cy - 6 * s), int(ex + sx * 8 * s), int(cy - 30 * s))
    # mic boom
    p.drawLine(int(cx - 56 * s), int(cy + 44 * s), int(cx - 80 * s), int(cy + 74 * s))
    p.setBrush(QBrush(QColor(color)))
    p.drawEllipse(QPointF(cx - 84 * s, cy + 78 * s), 6 * s, 6 * s)
    p.restore()


class HeadsetHero(QWidget):
    """Dashboard hero: headset render over animated ambient rings."""
    def __init__(self):
        super().__init__()
        self.setMinimumHeight(210)
        self.setMinimumWidth(420)
        self.setSizePolicy(QSizePolicy.Policy.Expanding, QSizePolicy.Policy.Preferred)
        self._phase = 0.0
        self._big = True
        self.setCursor(Qt.CursorShape.PointingHandCursor)
        t = QTimer(self, interval=50, timeout=self._anim)
        t.start()

    def toggle_size(self):
        self._big = not self._big
        self.setMinimumHeight(300 if self._big else 150)
        self.updateGeometry()

    def _anim(self):
        self._phase = (self._phase + 0.02) % 1.0
        self.update()

    def mousePressEvent(self, _):
        self.toggle_size()  # the real app's expand button behaviour

    def paintEvent(self, _):
        p = QPainter(self)
        p.setRenderHint(QPainter.RenderHint.Antialiasing)
        w, h = self.width(), self.height()
        cx, cy = w / 2, h / 2 + 6
        scale = min(1.0, h / 230.0)
        # ambient rings
        for i, (rr, alpha) in enumerate(((h * 0.52, 34), (h * 0.40, 52), (h * 0.28, 74))):
            ang = self._phase + i * 0.33
            pen = QPen(QColor(111, 79, 242, alpha), 2)
            p.setPen(pen)
            p.setBrush(Qt.BrushStyle.NoBrush)
            rect = QRectF(cx - rr * 1.35, cy - rr, rr * 2.7, rr * 2)
            start = int(60 + ang * 57)
            p.drawArc(rect, start * 16, 200 * 16)
            p.drawArc(rect, (start + 180) * 16, 200 * 16)
        # radial glow
        glow = QRadialGradient(cx, cy, h * 0.55)
        glow.setColorAt(0.0, QColor(111, 79, 242, 36))
        glow.setColorAt(1.0, QColor(0, 0, 0, 0))
        p.setBrush(QBrush(glow))
        p.setPen(Qt.PenStyle.NoPen)
        p.drawEllipse(QPointF(cx, cy), h * 0.55, h * 0.5)
        draw_headset(p, cx, cy, scale)


class SphereHead(QWidget):
    """Spatial-sound visualiser: wireframe sphere + head, 'output channel: 7.1'."""
    def __init__(self):
        super().__init__()
        self.active_color = QColor(PURPLE_2)
        self.setMinimumHeight(300)

    def paintEvent(self, _):
        p = QPainter(self)
        p.setRenderHint(QPainter.RenderHint.Antialiasing)
        w, h = self.width(), self.height()
        cx, cy = w / 2, h / 2 - 12
        r = min(w, h) * 0.34
        col = QColor(self.active_color) if self.active_color.value() else QColor(GREY)
        pen = QPen(col, 1.4)
        p.setPen(pen)
        p.setBrush(Qt.BrushStyle.NoBrush)
        # meridian circle + horizontal ellipse
        p.drawEllipse(QPointF(cx, cy), r, r)
        p.drawLine(int(cx), int(cy - r), int(cx), int(cy + r))
        p.drawEllipse(QPointF(cx, cy), r, r * 0.32)
        # head
        p.setBrush(QBrush(QColor("#8d93a8")))
        p.setPen(Qt.PenStyle.NoPen)
        p.drawEllipse(QPointF(cx, cy), r * 0.42, r * 0.55)
        # smile + side ears
        p.setPen(QPen(QColor(WHITE), 4, Qt.PenStyle.SolidLine, Qt.PenCapStyle.RoundCap))
        p.drawArc(QRectF(cx - r * 0.26, cy + r * 0.02, r * 0.52, r * 0.3), 200 * 16, 140 * 16)
        p.setBrush(QBrush(QColor("#6b7180")))
        for sx in (-1, 1):
            p.drawPolygon([QPointF(cx + sx * r * 0.42, cy - r * 0.1),
                           QPointF(cx + sx * r * 0.52, cy + r * 0.12),
                           QPointF(cx + sx * r * 0.42, cy + r * 0.3)])
        p.setPen(QPen(QColor(DARKGREY), 1))
        p.setFont(QFont("Segoe UI", 9))
        p.drawText(QRectF(0, h - 30, w - 14, 20),
                   Qt.AlignmentFlag.AlignRight | Qt.AlignmentFlag.AlignVCenter,
                   "output channel: 7.1")


class BatteryChip(QWidget):
    def __init__(self):
        super().__init__()
        self.percent = None
        self.charging = False
        self.setFixedSize(110, 24)

    def paintEvent(self, _):
        p = QPainter(self)
        p.setRenderHint(QPainter.RenderHint.Antialiasing)
        p.setFont(QFont("Segoe UI", 9))
        p.setPen(QPen(QColor(WHITE), 1))
        if self.charging:
            p.drawText(QRectF(0, 0, 78, 24), Qt.AlignmentFlag.AlignVCenter, "⚡ charging*")
        else:
            p.drawText(QRectF(0, 0, 40, 24), Qt.AlignmentFlag.AlignVCenter,
                       "—" if self.percent is None else f"{self.percent}%")
        bx, by, bw, bh = (80, 6, 20, 12) if self.charging else (44, 6, 20, 12)
        p.setPen(QPen(QColor(WHITE), 1.2))
        p.setBrush(Qt.BrushStyle.NoBrush)
        p.drawRoundedRect(QRectF(bx, by, bw, bh), 3, 3)
        p.drawRect(QRectF(bx + bw, by + 3.5, 2.5, 5))
        if self.percent is not None:
            p.setBrush(QBrush(QColor(GREEN if self.percent > 20 else RED)))
            p.setPen(Qt.PenStyle.NoPen)
            p.drawRoundedRect(QRectF(bx + 2, by + 2, (bw - 4) * max(0, min(1, self.percent / 100)),
                                     bh - 4), 2, 2)


class RailAvatar(QWidget):
    """Circular rail button; active = lit ring + left indicator bar."""
    def __init__(self, kind, tip, on_click):
        super().__init__()
        self.kind = kind          # "logo" | "headset" | glyph text
        self.tip = tip
        self.on_click = on_click
        self.active = False
        self.setToolTip(tip)
        self.setCursor(Qt.CursorShape.PointingHandCursor)
        self.setFixedSize(64, 52)

    def set_active(self, a):
        self.active = a
        self.update()

    def mousePressEvent(self, _):
        self.on_click()

    def paintEvent(self, _):
        p = QPainter(self)
        p.setRenderHint(QPainter.RenderHint.Antialiasing)
        cx, cy, r = self.width() / 2, self.height() / 2, 17
        if self.active:
            p.setPen(QPen(QColor(PURPLE), 3))
            p.drawLine(0, int(cy - 16), 0, int(cy + 16))
        p.setBrush(QBrush(QColor("#2b2337" if self.active else "#1c1626")))
        p.setPen(QPen(QColor(PURPLE_2 if self.active else "#3a3348"), 1.4))
        p.drawEllipse(QPointF(cx, cy), r, r)
        if self.kind == "logo":
            # stylised open-Q mark (drawn, no trademarked artwork)
            p.setBrush(QBrush(QColor(WHITE)))
            p.setPen(Qt.PenStyle.NoPen)
            p.drawEllipse(QPointF(cx, cy - 1), 9.5, 8.5)
            p.setBrush(QBrush(QColor("#1c1626")))
            p.drawEllipse(QPointF(cx, cy - 1), 4.5, 4)
            p.setBrush(QBrush(QColor(WHITE)))
            p.drawEllipse(QPointF(cx + 6, cy + 7), 2.6, 2.6)
        elif self.kind == "headset":
            draw_headset(p, cx, cy + 2, 0.30)
        else:
            p.setPen(QPen(QColor(WHITE if self.active else GREY), 1))
            f = QFont("Segoe UI Emoji", 11)
            p.setFont(f)
            p.drawText(self.rect(), Qt.AlignmentFlag.AlignCenter, self.kind)


# ---------------- detail-page chrome ----------------

class DetailHeader(QWidget):
    """Back arrow + centred title + optional right toggle (matches spatial page)."""
    def __init__(self, title, on_back, toggle_cb=None, on_reset=None):
        super().__init__()
        self.setFixedHeight(56)
        h = QHBoxLayout(self)
        h.setContentsMargins(24, 8, 24, 8)
        back = QPushButton("‹")
        back.setFixedSize(36, 36)
        back.setCursor(Qt.CursorShape.PointingHandCursor)
        back.setStyleSheet(
            f"QPushButton {{ background: {CARD_2}; border: 1px solid {CARD_BORDER};"
            f" border-radius: 18px; color: {WHITE}; font-size: 18px; }}")
        back.clicked.connect(on_back)
        h.addWidget(back)
        t = QLabel(title)
        t.setStyleSheet(f"color: {WHITE}; font-size: 15px; font-weight: bold; letter-spacing: 1.5px;")
        t.setAlignment(Qt.AlignmentFlag.AlignCenter)
        h.addWidget(t, 1)
        right = QWidget()
        rh = QHBoxLayout(right)
        rh.setContentsMargins(0, 0, 0, 0)
        rh.setSpacing(10)
        if on_reset:
            rs = QPushButton("⟲  reset")
            rs.setFixedHeight(32)
            rs.setCursor(Qt.CursorShape.PointingHandCursor)
            rs.setStyleSheet(
                f"QPushButton {{ background: {CARD_2}; border: 1px solid {CARD_BORDER};"
                f" border-radius: 16px; color: {WHITE}; padding: 0 14px; }}")
            rs.clicked.connect(on_reset)
            rh.addWidget(rs)
        if toggle_cb:
            self.toggle = Toggle(True, toggle_cb)
            rh.addWidget(self.toggle)
        h.addWidget(right)


def cap_label(txt, size=11, color=GREY, bold=False, tracking=True):
    l = QLabel(txt)
    ls = f"color: {color}; font-size: {size}px;"
    if bold:
        ls += " font-weight: bold;"
    if tracking:
        ls += " letter-spacing: 1px;"
    l.setStyleSheet(ls)
    return l


# ---------------- pages ----------------
PAGE_HOME, PAGE_DEVICE, PAGE_SPATIAL, PAGE_EQ, PAGE_MIC, PAGE_LIGHTING, \
    PAGE_AMBIENT, PAGE_SUPPORT, PAGE_SETTINGS = range(9)


class TourOverlay(QWidget):
    """5-step onboarding tour (purple tooltip cards + Skip), matches the real app."""

    STEPS = [
        ("Choose from gaming sound presets or customize the equalizer bands.", PAGE_DEVICE, "eq"),
        ("Spatial sound enhances the immersive experience. Give it a try!", PAGE_DEVICE, "spatial"),
        ("Adjust the microphone specific settings here.", PAGE_DEVICE, "mic"),
        ("Customize the RGB effects on the product.", PAGE_DEVICE, "lighting"),
        ("Find more settings or product related info here.", PAGE_DEVICE, "support"),
    ]

    def __init__(self, window):
        super().__init__(window)
        self.win = window
        self.step = 0
        self.setAttribute(Qt.WidgetAttribute.WA_TransparentForMouseEvents, False)
        self.setGeometry(window.rect())

    def start(self):
        self.step = 0
        self.show()
        self.raise_()
        self._go()

    def _go(self):
        self.win.stack.setCurrentIndex(self.STEPS[self.step][1])
        self.setGeometry(self.win.rect())
        self.update()

    def _target(self):
        _, page, key = self.STEPS[self.step]
        w = self.win.card_refs.get(key)
        if w is None:
            return None
        tl = w.mapTo(self.win, QPoint(0, 0))
        return QRectF(tl.x(), tl.y(), w.width(), w.height())

    def paintEvent(self, _):
        p = QPainter(self)
        p.setRenderHint(QPainter.RenderHint.Antialiasing)
        p.fillRect(self.rect(), QColor(0, 0, 0, 190))
        tgt = self._target()
        text = self.STEPS[self.step][0]
        n = len(self.STEPS)
        cw, ch = 340, 96
        if tgt is not None:
            # dim-dodge: leave the target slightly brighter
            ring = QColor(PURPLE_2)
            ring.setAlpha(160)
            p.setPen(QPen(ring, 2))
            p.drawRoundedRect(tgt.adjusted(-4, -4, 4, 4), 16, 16)
            x = max(12, min(self.width() - cw - 12, tgt.x()))
            y = tgt.y() + tgt.height() + 14
            if y + ch > self.height() - 12:
                y = tgt.y() - ch - 14
        else:
            x = (self.width() - cw) / 2
            y = (self.height() - ch) / 2
        # tooltip card
        card = QRectF(x, y, cw, ch)
        grad = QLinearGradient(card.topLeft(), card.bottomRight())
        grad.setColorAt(0, QColor("#6f4ff2"))
        grad.setColorAt(1, QColor("#5334c9"))
        p.setBrush(QBrush(grad))
        p.setPen(Qt.PenStyle.NoPen)
        p.drawRoundedRect(card, 10, 10)
        p.setPen(QPen(QColor(WHITE), 1))
        p.setFont(QFont("Segoe UI", 10))
        p.drawText(card.adjusted(16, 10, -16, -34),
                   Qt.AlignmentFlag.AlignLeft | Qt.AlignmentFlag.AlignTop |
                   Qt.TextFlag.TextWordWrap, text)
        p.setFont(QFont("Segoe UI", 9))
        p.drawText(QRectF(card.x() + 16, card.bottom() - 30, 60, 22),
                   Qt.AlignmentFlag.AlignVCenter, f"{self.step + 1} / {n}")
        # buttons
        self._btn_prev = QRectF(card.right() - 190, card.bottom() - 36, 82, 28) \
            if self.step > 0 else None
        self._btn_next = QRectF(card.right() - 100, card.bottom() - 36, 84, 28)
        p.setFont(QFont("Segoe UI", 9))
        for rect, label in ((self._btn_prev, "Previous"), (self._btn_next,
                                                            "Done" if self.step == n - 1 else "Next")):
            if rect is None:
                continue
            p.setBrush(QColor(255, 255, 255, 30))
            p.setPen(QPen(QColor("white"), 1))
            p.drawRoundedRect(rect, 6, 6)
            p.drawText(rect, Qt.AlignmentFlag.AlignCenter, label)
        # skip pill top-right
        self._btn_skip = QRectF(self.width() - 90, 30, 64, 34)
        p.setBrush(QColor(255, 255, 255, 26))
        p.setPen(QPen(QColor("white"), 1))
        p.drawRoundedRect(self._btn_skip, 17, 17)
        p.drawText(self._btn_skip, Qt.AlignmentFlag.AlignCenter, "Skip")

    def _hit(self, pos, rect):
        return rect is not None and rect.contains(QPointF(pos))

    def mousePressEvent(self, e):
        pos = e.position()
        n = len(self.STEPS)
        if self._hit(pos, self._btn_skip):
            return self.finish()
        if self._hit(pos, self._btn_next):
            if self.step == n - 1:
                return self.finish()
            self.step += 1
            return self._go()
        if self._hit(pos, self._btn_prev):
            self.step = max(0, self.step - 1)
            return self._go()

    def finish(self):
        SETTINGS.setValue("tour_done", True)
        self.hide()
        self.win._nav(self.win.last_page)


# ---------------- main window ----------------

class MainWindow(QWidget):
    def __init__(self, demo=False):
        super().__init__()
        self.setWindowTitle(APP_NAME)
        self.resize(1280, 800)
        self.setMinimumSize(1000, 640)
        self.setWindowFlags(Qt.WindowType.FramelessWindowHint)
        self.setStyleSheet(f"QWidget {{ color: {WHITE}; font-size: 12px; }}")

        self.demo = demo
        self.eq_preset = "FLAT"
        self.eq_values = list(EQ_PRESETS["FLAT"])
        self.spatial_mode = 1        # 0 quantum spatial, 1 dts, (toggle off = disabled)
        self.spatial_on = True
        self.room_size = 1
        self.head_diameter = 5       # 15..25 cm index
        self.sidetone = 0
        self.light_preset = "SOLID"
        self.zone_hue = {"LOGO": 0.95, "RING": 0.45}
        self.zone_brightness = {"LOGO": 6, "RING": 6}
        self.zone_param = 4
        self.sync_all = True
        self.last_page = PAGE_DEVICE
        self.profiles = load_json(PROFILE_FILE, {})
        self.custom_presets = load_json(os.path.join(DATA_DIR, "eq_custom.json"), {})
        self.eq_all_presets = {**EQ_PRESETS, **self.custom_presets}
        self.card_refs: dict[str, QWidget] = {}
        self._volume_iface = None
        self._last_feature: str | None = None
        self._lights_on_state = True  # device-truth for the lighting master (from _apply_state)

        self.worker = DeviceWorker()
        self.worker.got.connect(self._worker_got)
        self.worker.start()

        self._build()
        self._load_profile_auto()
        self._tick()
        self.poll = QTimer(self, interval=2000, timeout=self._tick)
        self.poll.start()
        if self.demo:
            # prime the dashboard with the demo state (live mode gets it from _tick)
            self.hero_battery.percent = 80
            self.hero_battery.update()
            self.pc_batt.setText("🔋 80%")
            self.dial_dots.set_value(11)
        else:
            # sync the spatial toggle with the REAL Windows spatial state (read-only)
            QTimer.singleShot(1500, lambda: self.worker.submit("spatial_state", None))
        if not self.demo and not SETTINGS.value("tour_done", False, type=bool):
            QTimer.singleShot(900, self._start_tour)

    # ---------- shell ----------
    def _build(self):
        root = QHBoxLayout(self)
        root.setContentsMargins(0, 0, 0, 0)
        root.setSpacing(0)

        # left rail
        rail = QWidget()
        rail.setFixedWidth(78)
        rail.setStyleSheet("background: #100b18;")
        rv = QVBoxLayout(rail)
        rv.setContentsMargins(7, 14, 7, 14)
        rv.setSpacing(8)
        self.rail_logo = RailAvatar("logo", APP_NAME, lambda: self._nav(PAGE_HOME))
        rv.addWidget(self.rail_logo, 0, Qt.AlignmentFlag.AlignHCenter)
        self.rail_headset = RailAvatar("headset", "My product", lambda: self._nav(PAGE_DEVICE))
        rv.addWidget(self.rail_headset, 0, Qt.AlignmentFlag.AlignHCenter)
        rv.addStretch(1)
        self.rail_help = RailAvatar("💬", "Support & help", lambda: self._nav(PAGE_SUPPORT))
        rv.addWidget(self.rail_help, 0, Qt.AlignmentFlag.AlignHCenter)
        self.rail_settings = RailAvatar("⚙", "Settings", lambda: self._nav(PAGE_SETTINGS))
        rv.addWidget(self.rail_settings, 0, Qt.AlignmentFlag.AlignHCenter)
        root.addWidget(rail)

        # main column (custom titlebar + stack + status)
        main = QWidget()
        main.setStyleSheet(
            "background: qlineargradient(x1:0,y1:0,x2:0,y2:1,"
            f" stop:0 {BG}, stop:1 #120b1e);")
        mv = QVBoxLayout(main)
        mv.setContentsMargins(0, 0, 0, 0)
        mv.setSpacing(0)
        mv.addWidget(self._titlebar())
        self.demo_banner = QLabel("  DEMO MODE — nothing is sent to hardware  ")
        self.demo_banner.setStyleSheet(
            f"background: {AMBER}; color: #141416; font-size: 10px; font-weight: bold;"
            " letter-spacing: 1px;")
        self.demo_banner.setFixedHeight(20)
        self.demo_banner.setVisible(self.demo)
        mv.addWidget(self.demo_banner)

        self.stack = QStackedWidget()
        for build in (self._page_home, self._page_device, self._page_spatial,
                      self._page_eq, self._page_mic, self._page_lighting,
                      self._page_ambient, self._page_support, self._page_settings):
            self.stack.addWidget(self._scroll(build))
        mv.addWidget(self.stack, 1)

        self.status = QLabel(" ")
        self.status.setStyleSheet(f"color: {GREY}; font-size: 10px; padding: 3px 20px 6px;")
        mv.addWidget(self.status)
        root.addWidget(main, 1)
        self._nav(PAGE_HOME)

    def _titlebar(self):
        bar = QWidget()
        bar.setFixedHeight(34)
        bar.setStyleSheet("background: #0d0916;")
        h = QHBoxLayout(bar)
        h.setContentsMargins(14, 0, 6, 0)
        logo = QLabel("◉")
        logo.setStyleSheet(f"color: {PURPLE_2}; font-size: 13px;")
        h.addWidget(logo)
        t = QLabel(APP_NAME)
        t.setStyleSheet(f"color: {GREY}; font-size: 10px; letter-spacing: 1px;")
        h.addWidget(t)
        h.addStretch(1)
        for glyph, cb in (("—", self.showMinimized), ("▢", self._toggle_max),
                          ("✕", self.close)):
            b = QPushButton(glyph)
            b.setFixedSize(40, 26)
            b.setCursor(Qt.CursorShape.PointingHandCursor)
            b.setStyleSheet(
                f"QPushButton {{ background: transparent; color: {GREY}; border: none;"
                f" font-size: 11px; }} QPushButton:hover {{ background: #2a2138; color: {WHITE}; }}")
            b.clicked.connect(cb)
            h.addWidget(b)

        def drag(e):
            if e.buttons() & Qt.MouseButton.LeftButton:
                self.windowHandle().startSystemMove()
        bar.mousePressEvent = drag
        return bar

    def _toggle_max(self):
        self.showNormal() if self.isMaximized() else self.showMaximized()

    def _scroll(self, builder):
        sa = QScrollArea()
        sa.setWidgetResizable(True)
        sa.setFrameShape(QFrame.Shape.NoFrame)
        sa.setStyleSheet("QScrollArea { background: transparent; border: none; }"
                         "QWidget { background: transparent; }"
                         f"QScrollBar:vertical {{ background: #141019; width: 10px; margin: 0; }}"
                         f"QScrollBar::handle:vertical {{ background: #3a3348; border-radius: 5px;"
                         f" min-height: 30px; }}"
                         "QScrollBar::handle:vertical:hover { background: #4a4260; }"
                         "QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical"
                         " { height: 0; }"
                         "QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical"
                         " { background: none; }")
        inner = builder()
        sa.setWidget(inner)
        return sa

    def _nav(self, idx):
        self.last_page = idx
        self.stack.setCurrentIndex(idx)
        self.rail_logo.set_active(idx == PAGE_HOME)
        self.rail_headset.set_active(idx in (PAGE_DEVICE, PAGE_SPATIAL, PAGE_EQ,
                                             PAGE_MIC, PAGE_LIGHTING, PAGE_AMBIENT))
        self.rail_help.set_active(idx == PAGE_SUPPORT)
        self.rail_settings.set_active(idx == PAGE_SETTINGS)

    # ---------- HOME ----------
    def _page_home(self):
        pg = QWidget()
        v = QVBoxLayout(pg)
        v.setContentsMargins(60, 30, 60, 30)
        v.setSpacing(18)

        # banner carousel (static frame of the real one)
        banner = QWidget()
        banner.setFixedHeight(200)
        banner.setCursor(Qt.CursorShape.PointingHandCursor)

        def paint_banner(ev, w=banner):
            p = QPainter(w)
            p.setRenderHint(QPainter.RenderHint.Antialiasing)
            rect = w.rect()
            grad = QLinearGradient(QPointF(rect.topLeft()), QPointF(rect.bottomRight()))
            grad.setColorAt(0, QColor("#7d2fa8"))
            grad.setColorAt(0.5, QColor("#a34fd6"))
            grad.setColorAt(1, QColor("#6a2fb0"))
            p.setBrush(QBrush(grad))
            p.setPen(Qt.PenStyle.NoPen)
            p.drawRoundedRect(rect, 14, 14)
            # head silhouette + crystal
            p.setBrush(QColor(60, 20, 90, 120))
            p.drawEllipse(QPointF(rect.width() / 2, rect.height() / 2 + 30), 150, 170)
            crys = QRadialGradient(rect.width() / 2, rect.height() / 2 - 10, 70)
            crys.setColorAt(0, QColor("#f0a6ff"))
            crys.setColorAt(1, QColor("#c04fd6"))
            p.setBrush(QBrush(crys))
            path = QPainterPath()
            cx, cy = rect.width() / 2, rect.height() / 2 - 10
            path.moveTo(cx, cy - 55)
            path.lineTo(cx + 45, cy + 10)
            path.lineTo(cx, cy + 55)
            path.lineTo(cx - 45, cy + 10)
            p.drawPath(path)
            p.setPen(QPen(QColor(WHITE), 1))
            p.setFont(QFont("Segoe UI", 16, QFont.Weight.Bold))
            p.drawText(rect.adjusted(0, 0, 0, -20), Qt.AlignmentFlag.AlignCenter,
                       "SOUND IS SURVIVAL")
        banner.paintEvent = paint_banner
        v.addWidget(banner)

        head = QWidget()
        hh = QHBoxLayout(head)
        hh.setContentsMargins(0, 0, 0, 0)
        t = QLabel("MY PRODUCTS")
        t.setStyleSheet(f"color: {WHITE}; font-size: 15px; font-weight: bold; letter-spacing: 1.5px;")
        hh.addWidget(t)
        hh.addStretch(1)
        plus = QLabel("＋")
        plus.setStyleSheet(f"color: {WHITE}; font-size: 18px;")
        hh.addWidget(plus)
        v.addWidget(head)

        # product card
        self.product_card = QFrame()
        self.product_card.setObjectName("pcard")
        self.product_card.setFixedSize(300, 260)
        self.product_card.setStyleSheet(
            f"#pcard {{ background: {CARD}; border-radius: 14px; border: 1px solid {CARD_BORDER}; }}")
        self.product_card.setCursor(Qt.CursorShape.PointingHandCursor)
        pv = QVBoxLayout(self.product_card)
        pv.setContentsMargins(0, 0, 0, 0)
        pv.setSpacing(0)
        img = QWidget()
        img.setFixedHeight(190)
        img.setCursor(Qt.CursorShape.PointingHandCursor)

        def paint_img(ev, w=img):
            p = QPainter(w)
            p.setRenderHint(QPainter.RenderHint.Antialiasing)
            draw_headset(p, w.width() / 2, w.height() / 2 - 6, 1.15, color="#c9c4d4")
        img.paintEvent = paint_img
        pv.addWidget(img)
        info = QWidget()
        iv = QVBoxLayout(info)
        iv.setContentsMargins(14, 2, 14, 12)
        iv.setSpacing(3)
        self.pc_name = QLabel("JBL Quantum 810")
        self.pc_name.setStyleSheet(f"color: {WHITE}; font-size: 13px; font-weight: bold;")
        self.pc_batt = QLabel("🔋 —")
        self.pc_batt.setStyleSheet(f"color: {GREY}; font-size: 11px;")
        iv.addWidget(self.pc_name)
        iv.addWidget(self.pc_batt)
        pv.addWidget(info)
        self.product_card.mousePressEvent = lambda _: self._nav(PAGE_DEVICE)
        self.product_card.setToolTip("Open the Quantum 810 dashboard")

        row = QWidget()
        rh = QHBoxLayout(row)
        rh.setContentsMargins(0, 0, 0, 0)
        rh.addWidget(self.product_card)
        rh.addStretch(1)
        v.addWidget(row)
        v.addStretch(1)
        self.hint_home = cap_label("", 10)
        v.addWidget(self.hint_home)
        return pg

    # ---------- DEVICE DASHBOARD ----------
    def _page_device(self):
        pg = QWidget()
        v = QVBoxLayout(pg)
        v.setContentsMargins(40, 18, 40, 14)
        v.setSpacing(8)

        title = QLabel("JBL Quantum 810")
        title.setStyleSheet(f"color: {WHITE}; font-size: 15px; font-weight: bold; letter-spacing: 1px;")
        v.addWidget(title, 0, Qt.AlignmentFlag.AlignHCenter)

        self.hero = HeadsetHero()
        v.addWidget(self.hero, 0, Qt.AlignmentFlag.AlignHCenter)

        # volume / battery row
        stat = QWidget()
        sh = QHBoxLayout(stat)
        sh.setContentsMargins(0, 0, 0, 0)
        sh.setSpacing(26)
        sh.addStretch(1)
        self.vol_label = cap_label("🔊 100%", 12, WHITE, tracking=False)
        self.vol_label.setCursor(Qt.CursorShape.PointingHandCursor)
        self.vol_label.mousePressEvent = lambda _: self._volume_popup()
        sh.addWidget(self.vol_label)
        self.hero_battery = BatteryChip()
        sh.addWidget(self.hero_battery)
        sh.addStretch(1)
        v.addWidget(stat)
        self.dial_dots = DialDots()
        v.addWidget(self.dial_dots, 0, Qt.AlignmentFlag.AlignHCenter)

        grid_holder = QWidget()
        grid = QGridLayout(grid_holder)
        grid.setContentsMargins(0, 6, 0, 0)
        grid.setHorizontalSpacing(14)
        grid.setVerticalSpacing(14)

        def stretch_all(*cols):
            for c in cols:
                grid.setColumnStretch(c, 1)

        # EQUALIZER card
        eq_card = Card("EQUALIZER")
        self.eq_curve = EqCurve(self.eq_values)
        self.eq_curve.setMinimumHeight(110)
        eq_card.v.addWidget(self.eq_curve)
        self.eq_pill = Pill(self.eq_preset, items=list(self.eq_all_presets.keys()),
                            on_pick=self._eq_preset)
        eq_card.v.addWidget(self.eq_pill)
        eq_card.add_more(lambda: self._nav(PAGE_EQ))
        grid.addWidget(eq_card, 0, 0)
        self.card_refs["eq"] = eq_card

        mid = QWidget()
        mv = QVBoxLayout(mid)
        mv.setContentsMargins(0, 0, 0, 0)
        mv.setSpacing(14)
        # SPATIAL SOUND card
        sp_card = Card("SPATIAL SOUND", toggle_cb=self._spatial_toggle)
        self.sp_card = sp_card
        self.sp_seg = Segmented(["Quantum Spatial", "DTS"], self.spatial_mode,
                                self._spatial_mode_changed, glyphs=["⚛", "dts"])
        sp_card.v.addWidget(self.sp_seg)
        sp_card.add_more(lambda: self._nav(PAGE_SPATIAL))
        mv.addWidget(sp_card)
        self.card_refs["spatial"] = sp_card
        # AMBIENT SOUND CONTROL card
        am_card = Card("AMBIENT SOUND CONTROL", toggle_cb=self._anc_toggle)
        self.anc_card = am_card
        self.anc_seg = Segmented(["ANC", "TalkThru"], 0, self._anc_seg_changed)
        am_card.v.addWidget(self.anc_seg)
        am_card.add_more(lambda: self._nav(PAGE_AMBIENT))
        mv.addWidget(am_card)
        self.card_refs["ambient"] = am_card
        grid.addWidget(mid, 0, 1)
        stretch_all(0, 1, 2)

        # MICROPHONE card
        mc = Card("MICROPHONE")
        gain_row = QWidget()
        gh = QHBoxLayout(gain_row)
        gh.setContentsMargins(0, 0, 0, 0)
        gh.addWidget(cap_label("Gain:", 11, GREY, tracking=False))
        gh.addStretch(1)
        self.mic_gain_lbl = cap_label("100%", 11, GREY, tracking=False)
        gh.addWidget(self.mic_gain_lbl)
        mc.v.addWidget(gain_row)
        self.mic_gain = QSlider(Qt.Orientation.Horizontal)
        self.mic_gain.setRange(0, 100)
        self.mic_gain.setValue(100)
        self.mic_gain.setEnabled(False)  # mic gain = RACE-level, fail-closed until captured
        mc.v.addWidget(self.mic_gain)
        st_row = QWidget()
        sh2 = QHBoxLayout(st_row)
        sh2.setContentsMargins(0, 0, 0, 0)
        sh2.addWidget(cap_label("Side Tone:", 11, GREY, tracking=False))
        sh2.addStretch(1)
        self.mic_sidetone_lbl = cap_label("Off", 11, GREY, tracking=False)
        sh2.addWidget(self.mic_sidetone_lbl)
        mc.v.addWidget(st_row)
        self.mic_stops = StopSlider(SIDETONE_STEPS, 0, self._sidetone_changed,
                                    labels=SIDETONE_STEPS)
        mc.v.addWidget(self.mic_stops)
        self.mic_preset = Pill("  NATURAL", items=["NATURAL", "BRIGHT", "WARM", "SOFT"],
                               on_pick=lambda n: self.flash(
                                   f"mic voice preset '{n}' — {HOST_SIDE_NOTE}"))
        self.mic_preset.setEnabled(True)
        mc.v.addWidget(self.mic_preset)
        mc.add_more(lambda: self._nav(PAGE_MIC))
        grid.addWidget(mc, 0, 2)
        self.card_refs["mic"] = mc

        # LIGHTING card
        lt_card = Card("LIGHTING", toggle_cb=self._lights_toggle)
        self.lt_card = lt_card
        self.light_pill = Pill("  SOUND IS SURVIVAL",
                               items=["SOUND IS SURVIVAL", "OFF"] + LIGHT_PRESETS,
                               on_pick=self._light_preset)
        lt_card.v.addWidget(self.light_pill)
        lt_card.add_more(lambda: self._nav(PAGE_LIGHTING))
        grid.addWidget(lt_card, 1, 0)
        self.card_refs["lighting"] = lt_card

        # SUPPORT card
        sup = Card("SUPPORT")
        q = QLabel("?")
        q.setFixedSize(56, 44)
        q.setAlignment(Qt.AlignmentFlag.AlignCenter)
        q.setStyleSheet(
            f"color: {PURPLE_2}; font-size: 20px; font-weight: bold;"
            f" border: 2px solid {PURPLE_2}; border-radius: 10px;")
        sup.v.addWidget(q, 0, Qt.AlignmentFlag.AlignHCenter)
        sup.add_more(lambda: self._nav(PAGE_SUPPORT))
        grid.addWidget(sup, 1, 1)
        self.card_refs["support"] = sup

        self.no_device = cap_label("no headset detected — plug in the Quantum 810 wireless "
                                   "dongle (it connects automatically)", 10, AMBER)
        self.no_device.setAlignment(Qt.AlignmentFlag.AlignCenter)
        self.no_device.setVisible(False)
        grid.addWidget(self.no_device, 2, 0, 1, 3)

        v.addWidget(grid_holder, 1)
        return pg

    # ---------- SPATIAL DETAIL ----------
    def _page_spatial(self):
        pg = QWidget()
        v = QVBoxLayout(pg)
        v.setContentsMargins(40, 8, 40, 14)
        v.setSpacing(10)
        head = DetailHeader("SPATIAL SOUND  ⓘ", lambda: self._nav(PAGE_DEVICE),
                            toggle_cb=self._spatial_toggle)
        self.sp_detail_toggle = head.toggle
        v.addWidget(head)
        rs = QPushButton("⟲  reset")
        rs.setFixedHeight(34)
        rs.setCursor(Qt.CursorShape.PointingHandCursor)
        rs.setStyleSheet(
            f"QPushButton {{ background: {CARD_2}; border: 1px solid {CARD_BORDER};"
            f" border-radius: 17px; color: {WHITE}; padding: 0 16px; }}"
            f"QPushButton:hover {{ border-color: {PURPLE_2}; }}")
        rs.clicked.connect(self._spatial_reset)
        v.addWidget(rs, 0, Qt.AlignmentFlag.AlignRight)

        body = QWidget()
        bh = QHBoxLayout(body)
        bh.setContentsMargins(0, 6, 0, 0)
        bh.setSpacing(30)

        left = QWidget()
        lv = QVBoxLayout(left)
        lv.setContentsMargins(0, 0, 0, 0)
        lv.setSpacing(12)
        lv.addWidget(cap_label("SPATIAL SOUND MODE", 12, WHITE, bold=True))
        self.sp_seg2 = Segmented(["Quantum Spatial", "DTS"], self.spatial_mode,
                                 self._spatial_mode_changed, glyphs=["⚛", "dts"])
        lv.addWidget(self.sp_seg2)

        self.sp_dts_box = QWidget()
        dv = QVBoxLayout(self.sp_dts_box)
        dv.setContentsMargins(0, 20, 0, 0)
        dts_card = QFrame()
        dts_card.setFixedSize(200, 100)
        dts_card.setStyleSheet("background: #1a1524; border-radius: 6px;")

        def paint_dts(ev, w=dts_card):
            p = QPainter(w)
            p.setRenderHint(QPainter.RenderHint.Antialiasing)
            p.fillRect(w.rect(), QColor("#141019"))
            p.setPen(QPen(QColor(WHITE), 1))
            p.setFont(QFont("Segoe UI", 20, QFont.Weight.Black))
            p.drawText(QRectF(0, 8, w.width() - 46, 40), Qt.AlignmentFlag.AlignCenter, "dts")
            # X mark
            p.setPen(QPen(QColor(WHITE), 5))
            p.drawLine(w.width() - 40, 14, w.width() - 16, 40)
            p.drawLine(w.width() - 16, 14, w.width() - 40, 40)
            p.setFont(QFont("Segoe UI", 8, QFont.Weight.Bold))
            p.drawText(QRectF(10, 46, w.width() - 20, 16),
                       Qt.AlignmentFlag.AlignLeft, "HEADPHONE")
            p.drawText(QRectF(0, w.height() - 26, w.width() - 10, 20),
                       Qt.AlignmentFlag.AlignRight, "v2.0")
        dts_card.paintEvent = paint_dts
        dv.addWidget(dts_card, 0, Qt.AlignmentFlag.AlignHCenter)
        dv.addWidget(cap_label("DTS Headphone:X needs the DTS licence (installed by JBL "
                               "QuantumENGINE). If this PC doesn't have it, the app "
                               "applies Windows Sonic instead and says so.", 9, DARKGREY))
        lv.addWidget(self.sp_dts_box)

        self.sp_qs_box = QWidget()
        qv = QVBoxLayout(self.sp_qs_box)
        qv.setContentsMargins(0, 8, 0, 0)
        qv.setSpacing(10)
        qv.addWidget(cap_label("ROOM SIZE  ⓘ", 12, WHITE, bold=True))
        self.room_stops = StopSlider([0, 1, 2], self.room_size,
                                     self._room_changed, labels=ROOM_SIZES)
        qv.addWidget(self.room_stops)
        qv.addWidget(cap_label("HEAD DIAMETER  ⓘ", 12, WHITE, bold=True))
        self.head_stops = StopSlider(list(range(11)), self.head_diameter,
                                     self._head_changed,
                                     labels=["15cm", None, None, None, None, "20cm",
                                             None, None, None, None, "25cm"])
        qv.addWidget(self.head_stops)
        lv.addWidget(self.sp_qs_box)
        lv.addStretch(1)

        self.sp_note = cap_label(
            "spatial sound is HOST-SIDE processing on this PC (the dongle receives "
            "nothing — capture-proven). This switch applies Windows' real spatial "
            "sound to the headset's Game endpoint: DTS mode uses DTS Headphone:X when "
            "its licence is present, Quantum Spatial uses Windows Sonic. HONEST NOTE: "
            "the real app's spatial DSP runs inside JBL's own kernel driver "
            "(HarmanAudioService), so its exact sound can't be reproduced here — ours "
            "is a different (clearly audible) spatializer. Toggles are endpoint-format "
            "stable so running games keep the headset.", 9, DARKGREY)
        self.sp_note.setWordWrap(True)
        lv.addWidget(self.sp_note)

        right = QWidget()
        rv = QVBoxLayout(right)
        rv.setContentsMargins(0, 0, 0, 0)
        sph_card = QFrame()
        sph_card.setObjectName("card")
        sph_card.setStyleSheet(
            f"#card {{ background: {CARD}; border-radius: 14px; border: 1px solid {CARD_BORDER}; }}")
        sv = QVBoxLayout(sph_card)
        sv.setContentsMargins(10, 10, 10, 10)
        self.sphere = SphereHead()
        sv.addWidget(self.sphere)
        sph_card.setFixedWidth(440)
        rv.addWidget(sph_card)
        rv.addStretch(1)

        bh.addWidget(left, 1)
        bh.addWidget(right, 0)
        v.addWidget(body, 1)
        return pg

    # ---------- EQ DETAIL ----------
    def _page_eq(self):
        pg = QWidget()
        v = QVBoxLayout(pg)
        v.setContentsMargins(40, 8, 40, 14)
        v.setSpacing(10)
        v.addWidget(DetailHeader("EQUALIZER", lambda: self._nav(PAGE_DEVICE)))
        card = Card("EQUALIZER")
        self.eq_curve_big = EqCurve(self.eq_values)
        self.eq_curve_big.on_change = self._eq_custom_changed
        self.eq_curve_big.setMinimumHeight(240)
        card.v.addWidget(self.eq_curve_big)
        presets_row = QWidget()
        pr = QHBoxLayout(presets_row)
        pr.setContentsMargins(0, 0, 0, 0)
        pr.setSpacing(8)
        for name in list(self.eq_all_presets.keys()):
            b = QPushButton(name)
            b.setFixedHeight(30)
            b.setCursor(Qt.CursorShape.PointingHandCursor)
            b.setStyleSheet(
                f"QPushButton {{ background: {CARD_2}; border: 1px solid {CARD_BORDER};"
                f" border-radius: 15px; color: {WHITE}; padding: 0 14px; }}"
                f"QPushButton:hover {{ border-color: {PURPLE_2}; }}")
            b.clicked.connect(lambda _, n=name: self._eq_preset(n))
            pr.addWidget(b)
        pr.addStretch(1)
        card.v.addWidget(presets_row)
        save_row = QWidget()
        sr = QHBoxLayout(save_row)
        sr.setContentsMargins(0, 0, 0, 0)
        self.eq_save = QLineEdit()
        self.eq_save.setPlaceholderText("save current curve as custom preset…")
        self.eq_save.returnPressed.connect(self._eq_save_custom)
        sr.addWidget(self.eq_save, 1)
        card.v.addWidget(save_row)
        note = cap_label(HOST_SIDE_NOTE + "  (community WARZONE curve is exact; others "
                         "are approximations — see SESSION-HANDOFF §7)", 9, DARKGREY)
        note.setWordWrap(True)
        card.v.addWidget(note)
        v.addWidget(card, 1)
        return pg

    # ---------- MIC DETAIL ----------
    def _page_mic(self):
        pg = QWidget()
        v = QVBoxLayout(pg)
        v.setContentsMargins(40, 8, 40, 14)
        v.setSpacing(10)
        v.addWidget(DetailHeader("MICROPHONE", lambda: self._nav(PAGE_DEVICE)))
        card = Card("MICROPHONE")
        state_row = QWidget()
        srh = QHBoxLayout(state_row)
        srh.setContentsMargins(0, 0, 0, 0)
        srh.addWidget(cap_label("Mic state (boom down + unmuted):", 11, GREY, tracking=False))
        srh.addStretch(1)
        self.mic_state_lbl = QLabel("—")
        self.mic_state_lbl.setStyleSheet(f"color: {WHITE}; font-weight: bold;")
        srh.addWidget(self.mic_state_lbl)
        card.v.addWidget(state_row)
        card.v.addWidget(cap_label("Side Tone / Audio Monitor — verified report 0x5D (4 steps)",
                                   10, GREY))
        self.mic_stops_big = StopSlider(SIDETONE_STEPS, self.sidetone,
                                        self._sidetone_changed, labels=SIDETONE_STEPS)
        card.v.addWidget(self.mic_stops_big)
        gain_row = QWidget()
        grh = QHBoxLayout(gain_row)
        grh.setContentsMargins(0, 4, 0, 0)
        grh.addWidget(cap_label("Gain", 11, GREY, tracking=False))
        grh.addStretch(1)
        grh.addWidget(cap_label("pending — RACE-level control, unlocked only after a live "
                                "capture (fail-closed by design)", 9, DARKGREY))
        card.v.addWidget(gain_row)
        self.mic_gain2 = QSlider(Qt.Orientation.Horizontal)
        self.mic_gain2.setRange(0, 100)
        self.mic_gain2.setValue(100)
        self.mic_gain2.setEnabled(False)
        card.v.addWidget(self.mic_gain2)
        note = cap_label("mute/mic-active is read from verified report 0x67; the headset's "
                         "own mute button stays authoritative.", 9, DARKGREY)
        note.setWordWrap(True)
        card.v.addWidget(note)
        v.addWidget(card, 1)
        return pg

    # ---------- LIGHTING DETAIL ----------
    def _page_lighting(self):
        pg = QWidget()
        v = QVBoxLayout(pg)
        v.setContentsMargins(40, 8, 40, 14)
        v.setSpacing(10)
        head = DetailHeader("LIGHTING", lambda: self._nav(PAGE_DEVICE),
                            toggle_cb=self._lights_toggle)
        self.lt_detail_toggle = head.toggle
        v.addWidget(head)
        card = Card("EFFECTS")
        self.light_pill2 = Pill("  SOUND IS SURVIVAL",
                                items=["OFF"] + LIGHT_PRESETS, on_pick=self._light_preset)
        card.v.addWidget(self.light_pill2)
        card.v.addWidget(cap_label("BRIGHTNESS (device-allowed steps 40–100%)", 10, GREY))
        self.bright_stops = StopSlider(LIGHT_BRIGHTNESS_STEPS, 6, self._brightness_changed,
                                       labels=["40", "100"])
        card.v.addWidget(self.bright_stops)
        card.v.addWidget(cap_label("SEG PARAM (effect tail byte 0–8, capture-verified range)",
                                   10, GREY))
        self.param_stops = StopSlider(list(range(9)), self.zone_param,
                                      self._param_changed)
        card.v.addWidget(self.param_stops)
        card.v.addWidget(cap_label("SEGMENTS hard-limited to 1–5 — more wedges the lighting "
                                   "MCU (hardware safety rule)", 9, AMBER))
        v.addWidget(card)

        zones = QWidget()
        zh = QHBoxLayout(zones)
        zh.setSpacing(14)
        self.zone_sliders = {}
        for zone in ("LOGO", "RING"):
            zc = Card(zone)
            cs = ColorSlider(on_change=lambda h, z=zone: self._zone_colour(z, h))
            cs.set_hue(self.zone_hue[zone])
            self.zone_sliders[zone] = cs
            zc.v.addWidget(cs)
            zh.addWidget(zc, 1)
        v.addWidget(zones)

        sync_row = QWidget()
        srh = QHBoxLayout(sync_row)
        srh.addWidget(cap_label("SYNC ALL LIGHTS", 11, WHITE, bold=True))
        srh.addStretch(1)
        self.sync_toggle = Toggle(self.sync_all, self._sync_toggle)
        srh.addWidget(self.sync_toggle)
        v.addWidget(sync_row)
        v.addStretch(1)
        return pg

    # ---------- AMBIENT DETAIL ----------
    def _page_ambient(self):
        pg = QWidget()
        v = QVBoxLayout(pg)
        v.setContentsMargins(40, 8, 40, 14)
        v.setSpacing(10)
        head = DetailHeader("AMBIENT SOUND CONTROL", lambda: self._nav(PAGE_DEVICE),
                            toggle_cb=self._anc_toggle)
        self.anc_detail_toggle = head.toggle
        v.addWidget(head)
        card = Card("MODE")
        self.anc_seg2 = Segmented(["ANC", "TalkThru"], 0, self._anc_seg_changed)
        card.v.addWidget(self.anc_seg2)
        note = cap_label("verified report 0x46: 0=off 1=on 2=talkthru — the headset's physical "
                         "button cycles the same modes (~1.5 s to settle before the mirror "
                         "read-back).", 9, DARKGREY)
        note.setWordWrap(True)
        card.v.addWidget(note)
        v.addWidget(card, 1)
        return pg

    # ---------- SUPPORT / SYSTEM ----------
    def _page_support(self):
        pg = QWidget()
        v = QVBoxLayout(pg)
        v.setContentsMargins(40, 8, 40, 14)
        v.setSpacing(10)
        v.addWidget(DetailHeader("SUPPORT", lambda: self._nav(PAGE_DEVICE)))
        card = Card("SYSTEM SOFTWARE")
        self.sys_info = QLabel("—")
        self.sys_info.setStyleSheet(f"color: {WHITE}; font-size: 12px; line-height: 150%;")
        card.v.addWidget(self.sys_info)
        card.v.addWidget(cap_label("AUTO POWER OFF — verified report 0x75 (5-min units, "
                                   "verified by read-back)", 10, GREY))
        self.autoff_pill = Pill("  60 MIN", items=["NEVER", "30 MIN", "60 MIN", "120 MIN"],
                                on_pick=self._autooff_pick)
        card.v.addWidget(self.autoff_pill)
        rs = QPushButton("RESTORE ORIGINALS (undo everything this app changed)")
        rs.setFixedHeight(34)
        rs.setCursor(Qt.CursorShape.PointingHandCursor)
        rs.setStyleSheet(
            f"QPushButton {{ background: {CARD_2}; border: 1px solid {CARD_BORDER};"
            f" border-radius: 8px; color: {WHITE}; }}"
            f"QPushButton:hover {{ border-color: {RED}; }}")
        rs.clicked.connect(self._restore)
        card.v.addWidget(rs)
        note = cap_label("firmware / DFU reports (0xF0/0xF1/0xF4/0xF5/0xF6/0x9A) are "
                         "deliberately unreachable in this app — no firmware flows, ever.",
                         9, DARKGREY)
        note.setWordWrap(True)
        card.v.addWidget(note)
        v.addWidget(card)

        help_card = Card("HELP")
        help_txt = cap_label(
            "Interoperability app for the JBL Quantum 810 Wireless dongle (0ECB:2069), "
            "protocol facts from docs/PROTOCOL.md + our own USB-capture verification. "
            "MIT licensed; no JBL software included. Close JBL QuantumENGINE while using "
            "this app so both tools don't fight over the device.", 10, GREY)
        help_txt.setWordWrap(True)
        help_card.v.addWidget(help_txt)
        v.addWidget(help_card)
        v.addStretch(1)
        return pg

    # ---------- SETTINGS ----------
    def _page_settings(self):
        pg = QWidget()
        v = QVBoxLayout(pg)
        v.setContentsMargins(40, 8, 40, 14)
        v.setSpacing(10)
        v.addWidget(DetailHeader("SETTINGS", lambda: self._nav(PAGE_DEVICE)))
        card = Card("APPLICATION")
        info = cap_label(f"{APP_NAME} for Windows  ·  v{APP_VERSION}\n"
                         f"profiles: {PROFILE_FILE}", 10, GREY)
        info.setWordWrap(True)
        card.v.addWidget(info)
        demo_row = QWidget()
        drh = QHBoxLayout(demo_row)
        drh.addWidget(cap_label("DEMO MODE (never sends anything to hardware)", 11, WHITE))
        drh.addStretch(1)
        self.demo_toggle = Toggle(self.demo, self._toggle_demo)
        drh.addWidget(self.demo_toggle)
        card.v.addWidget(demo_row)
        tour_btn = QPushButton("Replay the intro tour")
        tour_btn.setFixedHeight(32)
        tour_btn.setCursor(Qt.CursorShape.PointingHandCursor)
        tour_btn.setStyleSheet(
            f"QPushButton {{ background: {CARD_2}; border: 1px solid {CARD_BORDER};"
            f" border-radius: 8px; color: {WHITE}; }}")
        tour_btn.clicked.connect(self._start_tour)
        card.v.addWidget(tour_btn)
        v.addWidget(card)
        v.addStretch(1)
        return pg

    # ---------------- device actions ----------------
    def _send(self, feature, value, refresh_delay=0.4):
        self._last_feature = feature
        if self.demo:
            self.flash(f"{feature} → {value}   (demo — nothing sent)", AMBER)
            return
        self.worker.submit("set", (feature, value))
        QTimer.singleShot(int(refresh_delay * 1000), self._tick)

    def _tick(self):
        if self.demo:
            return
        self.worker.submit("state", None)

    def _worker_got(self, name, result):
        if name == "state":
            self._apply_state(result)
        elif name == "set":
            if not result.get("ok"):
                self.flash(f"write failed: {result.get('error')}", RED)
            else:
                # every successful device write gets visible feedback — silence on a
                # working switch reads as "this doesn't work" (owner report 2026-11-01)
                self.flash(f"{self._last_feature} applied ✓" if self._last_feature
                           else "applied ✓", GREEN)
        elif name == "spatial":
            if result.get("ok"):
                mode = result.get("mode", "")
                if result.get("fallback"):
                    self.flash(f"DTS not licensed on this PC ({result.get('dts_error')}) — "
                               f"applied Windows Sonic instead ✓", AMBER)
                else:
                    self.flash(f"spatial sound → {mode or 'OFF'} applied ✓ "
                               f"(endpoint format kept stable for running games)", GREEN)
            else:
                # honest failure — e.g. DTS requested but the OS kept Sonic
                self.flash(f"spatial sound: {result.get('error')}", RED)
        elif name == "spatial_state":
            # boot sync: the toggle reflects the REAL OS spatial state
            self.spatial_on = bool(result.get("guid"))
            self._spatial_apply_ui()
            cur = result.get("mode") or "off"
            self.flash(f"spatial sound is currently {cur} (Windows-side)")

    def _apply_state(self, st):
        present = bool(st.get("present"))
        self.no_device.setVisible(not present and not self.demo)
        if not present:
            self.hero_battery.percent = None
            self.hero_battery.update()
            self.pc_batt.setText("not connected")
            self.hint_home.setText("plug in the Quantum 810 wireless dongle — it connects "
                                   "automatically; or enable demo mode in Settings.")
            return
        name = st.get("product", "JBL Quantum 810")
        batt = st.get("battery")
        self.hero_battery.percent = batt
        self.hero_battery.charging = bool(st.get("charging"))
        self.hero_battery.update()
        self.pc_name.setText(name.replace(" Wireless", ""))
        self.pc_batt.setText(("⚡ charging*" if st.get("charging") else "🔋 ") +
                             (f"{batt}%" if batt is not None else ""))
        self.dial_dots.set_value(st.get("dial"))
        self.mic_state_lbl.setText({True: "ON", False: "OFF", None: "—"}.get(st.get("mic")))
        sid = st.get("sidetone")
        if sid in (0, 1, 2, 3):
            self.sidetone = sid
            self.mic_stops.set_index(sid)
            self.mic_stops_big.set_index(sid)
            self.mic_sidetone_lbl.setText(SIDETONE_STEPS[sid].title())
        anc = st.get("anc")
        if anc in (0, 1, 2):
            self._reflect_anc(anc)
        lights = st.get("lights")
        if lights is not None:
            # sync BOTH lighting toggles with device truth — the dashboard card used
            # to start ON while the device was OFF, so the owner's first click sent
            # "off" into an already-off device (= the "first time doesn't work" bug)
            self._lights_on_state = bool(lights)
            for t in (self.lt_card.toggle, self.lt_detail_toggle):
                if t.checked != bool(lights):
                    t.set_checked(bool(lights))
        aom = st.get("auto_off_min")
        if aom is not None:
            self.autoff_pill.set_value("NEVER" if aom == 0 else f"{aom} MIN")
        self.sys_info.setText(
            f"product   : {name}\nbattery   : {batt if batt is not None else '—'}%\n"
            f"serial    : {st.get('serial') or '—'}\nfirmware  : {st.get('firmware') or '—'}\n"
            f"dial      : {st.get('dial') if st.get('dial') is not None else '—'}/16")

    def _reflect_anc(self, mode):
        idx = {1: 0, 2: 1}.get(mode, 0)
        on = mode != 0
        for seg in (self.anc_seg, self.anc_seg2):
            seg.set_index(idx)
        for t in (self.anc_card.toggle, self.anc_detail_toggle):
            t.set_checked(on)
        # dim the card body when ANC is off (mirrors the real app)
        self.anc_seg.setEnabled(True)

    # ---- dashboard callbacks ----
    def _spatial_toggle(self, on):
        self.spatial_on = on
        self._spatial_apply_ui()
        if self.demo:
            self.flash(f"spatial sound {'on' if on else 'off'} (demo — nothing changed)",
                       AMBER)
            return
        fmt = (spatial_win.DTS_NAME if self.spatial_mode == 1
               else spatial_win.SONIC) if on else ""
        self._last_feature = "spatial sound"
        # the OS round-trip takes seconds — acknowledge the click IMMEDIATELY or the
        # switch reads as dead (owner: "spatial sound switch not work")
        self.flash("applying spatial sound… (this takes a few seconds)", AMBER)
        self.worker.submit("spatial", fmt)

    def _spatial_mode_changed(self, i):
        self.spatial_mode = i
        self._spatial_apply_ui()
        if not self.spatial_on or self.demo:
            name = "Quantum Spatial (Windows Sonic)" if i == 0 else "DTS"
            self.flash(f"spatial mode → {name}" +
                       ("" if self.spatial_on else " — spatial sound is OFF"), AMBER)
            return
        fmt = spatial_win.DTS_NAME if i == 1 else spatial_win.SONIC
        self._last_feature = "spatial mode"
        self.flash("applying spatial mode… (this takes a few seconds)", AMBER)
        self.worker.submit("spatial", fmt)

    def _spatial_apply_ui(self):
        for seg in (self.sp_seg, self.sp_seg2):
            seg.set_index(self.spatial_mode)
        for t in (self.sp_card.toggle, self.sp_detail_toggle):
            t.set_checked(self.spatial_on)
        dts = self.spatial_mode == 1 and self.spatial_on
        qs = self.spatial_mode == 0 and self.spatial_on
        self.sp_dts_box.setVisible(dts)
        self.sp_qs_box.setVisible(qs)
        self.sphere.active_color = QColor(PURPLE_2) if self.spatial_on else QColor(GREY)
        self.sphere.update()

    def _spatial_reset(self):
        self.spatial_mode, self.spatial_on, self.room_size, self.head_diameter = 1, True, 1, 5
        self.room_stops.set_index(1)
        self.head_stops.set_index(5)
        self._spatial_apply_ui()
        if not self.demo and self.spatial_on:
            self._last_feature = "spatial sound"
            self.worker.submit("spatial",
                               spatial_win.DTS_NAME if self.spatial_mode == 1
                               else spatial_win.SONIC)
        self.flash("spatial settings reset (defaults)")

    def _room_changed(self, val, _i):
        self.room_size = val
        self.flash(f"room size → {ROOM_SIZES[val]} (host-side)", AMBER)
        self._save_profile_auto()

    def _head_changed(self, val, _i):
        self.head_diameter = val
        self.flash(f"head diameter → {15 + val}cm (host-side)", AMBER)
        self._save_profile_auto()

    def _anc_toggle(self, on):
        self._send("anc", 1 if on else 0, refresh_delay=1.8)

    def _anc_seg_changed(self, i):
        self._send("anc", 1 if i == 0 else 2, refresh_delay=1.8)

    def _sidetone_changed(self, val, _i):
        # StopSlider.stops is the LABEL list — the device wants the level int (0..3)
        self._send("sidetone", _i)
        self.mic_sidetone_lbl.setText(SIDETONE_STEPS[_i].title())

    def _lights_toggle(self, on):
        self._send("lights", on)

    def _light_preset(self, name):
        if name == "SOUND IS SURVIVAL":  # the real app's default preset label = SOLID
            name = "SOLID"
        self.light_preset = name
        self.light_pill.set_value(name)
        self.light_pill2.set_value(name)
        if name == "OFF":
            self._send("lights", False)
            return
        was_on = self._lights_on_state
        self._send("lights", True)
        mode = LIGHT_MODE_BYTE[LIGHT_PRESETS.index(name)] if name in LIGHT_PRESETS else 1

        def apply_colour():
            for zone in ("LOGO", "RING"):
                self._send("light_colour", {
                    "element": 0 if zone == "LOGO" else 1, "slot": 0,
                    "rgb": self._hue_rgb(self.zone_hue[zone]), "mode": mode,
                    "last": self.zone_param})
        if was_on:
            apply_colour()
        else:
            # the lighting MCU boots with the master switch — an immediate colour
            # frame after master-on can be dropped (owner's "first time only" report);
            # give it a beat, then apply
            QTimer.singleShot(400, apply_colour)
        self._save_profile_auto()

    @staticmethod
    def _hue_rgb(h):
        c = QColor.fromHsvF(max(0.0, min(1.0, h)), 1, 1)
        return [c.red(), c.green(), c.blue()]

    def _zone_colour(self, zone, hue):
        self.zone_hue[zone] = hue
        if not self._lights_on_state:
            # choosing a colour while the master is off = clear intent to light up;
            # a colour frame with the master off can be dropped by the lighting MCU
            self._send("lights", True)
        mode = LIGHT_MODE_BYTE[LIGHT_PRESETS.index(self.light_preset)] \
            if self.light_preset in LIGHT_PRESETS else 1
        payload = {"element": 0 if zone == "LOGO" else 1, "slot": 0,
                   "rgb": self._hue_rgb(hue), "mode": mode, "last": self.zone_param}
        self._send("light_colour", payload)
        if self.sync_all:
            other = "RING" if zone == "LOGO" else "LOGO"
            self.zone_hue[other] = hue
            self.zone_sliders[other].set_hue(hue)
            self._send("light_colour", {**payload, "element": 0 if other == "LOGO" else 1})
        self._save_profile_auto()

    def _brightness_changed(self, val, _i):
        for zone in ("LOGO", "RING"):
            self.zone_brightness[zone] = LIGHT_BRIGHTNESS_STEPS.index(val)
            self._send("light_zone", {"element": 0 if zone == "LOGO" else 1,
                                      "brightness": val, "segments": 5})

    def _param_changed(self, val, _i):
        self.zone_param = val
        self.flash(f"seg param → {val}")

    def _sync_toggle(self, on):
        self.sync_all = on
        self.flash(f"sync all lights {'on' if on else 'off'}")

    def _autooff_pick(self, name):
        units = 0 if name == "NEVER" else int(name.split()[0]) // 5
        self._send("auto_off", units)

    def _restore(self):
        if self.demo:
            self.flash("demo — nothing sent to hardware", AMBER)
            return
        self.worker.submit("restore", None)

    # ---- EQ ----
    def _eq_preset(self, name):
        self.eq_preset = name
        self.eq_values[:] = list(self.eq_all_presets.get(name, [0] * 10))
        self.eq_curve.values = self.eq_values
        self.eq_curve.update()
        self.eq_curve_big.values = self.eq_values
        self.eq_curve_big.update()
        self.eq_pill.set_value(name)
        self.flash(f"EQ preset {name} — {HOST_SIDE_NOTE}", AMBER)
        self._save_profile_auto()

    def _eq_custom_changed(self):
        self.eq_preset = "CUSTOM"
        self.eq_pill.set_value("CUSTOM")
        # big page curve shares the same list object; dashboard curve follows
        self.eq_curve.values = self.eq_values
        self.eq_curve.update()
        self._save_profile_auto()

    def _eq_save_custom(self):
        name = self.eq_save.text().strip().upper()
        if not name:
            return
        self.custom_presets[name] = list(self.eq_values)
        save_json(os.path.join(DATA_DIR, "eq_custom.json"), self.custom_presets)
        self.eq_all_presets = {**EQ_PRESETS, **self.custom_presets}
        self.eq_pill.items = list(self.eq_all_presets.keys())
        self.eq_pill.set_value(name)
        self.flash(f"custom preset '{name}' saved (local)")

    # ---- profiles ----
    def _current_profile(self):
        return {"eq": list(self.eq_values), "eq_preset": self.eq_preset,
                "spatial_mode": self.spatial_mode, "spatial_on": self.spatial_on,
                "room_size": self.room_size, "head_diameter": self.head_diameter,
                "light_preset": self.light_preset,
                "hue": dict(self.zone_hue), "param": self.zone_param}

    def _save_profile_auto(self):
        save_json(PROFILE_FILE, {"last": self._current_profile()})

    def _load_profile_auto(self):
        d = load_json(PROFILE_FILE, {}).get("last", {})
        if not d:
            return
        self.eq_values[:] = d.get("eq", self.eq_values)
        self.eq_preset = d.get("eq_preset", "FLAT")
        self.eq_curve.values = self.eq_values
        self.eq_curve_big.values = self.eq_values
        self.eq_curve.update()
        self.eq_curve_big.update()
        self.eq_pill.set_value(self.eq_preset)
        self.spatial_mode = d.get("spatial_mode", 1)
        self.spatial_on = d.get("spatial_on", True)
        self.room_size = d.get("room_size", 1)
        self.head_diameter = d.get("head_diameter", 5)
        self.room_stops.set_index(self.room_size)
        self.head_stops.set_index(self.head_diameter)
        self._spatial_apply_ui()
        self.light_preset = d.get("light_preset", "SOLID")
        self.light_pill.set_value(self.light_preset)
        self.light_pill2.set_value(self.light_preset)
        self.zone_param = d.get("param", 4)
        self.param_stops.set_index(self.zone_param)
        for z, h in d.get("hue", {}).items():
            if z in self.zone_hue:
                self.zone_hue[z] = h
                self.zone_sliders[z].set_hue(h)

    # ---- volume (pycaw, optional) ----
    def _volume_popup(self):
        try:
            from pycaw.pycaw import AudioUtilities, IAudioEndpointVolume
            from comtypes import CLSCTX_ALL
            if self._volume_iface is None:
                dev = AudioUtilities.GetSpeakers()
                iface = dev.Activate(IAudioEndpointVolume._iid_, CLSCTX_ALL, None)
                self._volume_iface = iface
            vol = self._volume_iface.GetMasterVolumeLevelScalar()
            m = QMenu(self)
            m.setStyleSheet("QMenu { background: #262130; border: 1px solid #3a3348;"
                            " border-radius: 8px; padding: 10px; }")
            sa = QSlider(Qt.Orientation.Horizontal)
            sa.setRange(0, 100)
            sa.setValue(int(vol * 100))
            sa.setFixedWidth(180)

            def apply(v):
                try:
                    self._volume_iface.SetMasterVolumeLevelScalar(v / 100.0, None)
                    self.vol_label.setText(f"🔊 {v}%")
                except Exception:
                    pass
            sa.sliderMoved.connect(apply)
            sa.sliderReleased.connect(lambda: apply(sa.value()))
            wa = QWidgetAction_preview(sa)
            m.addAction(wa)
            m.exec(QCursor.pos())
        except Exception:
            self.flash("system volume control needs the optional 'pycaw' dependency")

    # ---- demo ----
    def _toggle_demo(self, on):
        self.demo = on
        self.demo_toggle.set_checked(on)
        self.demo_banner.setVisible(on)
        self.flash("demo mode " + ("ON — nothing will be sent" if on else "OFF"))
        if on:
            self.no_device.setVisible(False)
            self.hero_battery.percent = 80
            self.hero_battery.update()
            self.pc_batt.setText("🔋 80%")
            self.dial_dots.set_value(11)

    # ---- tour ----
    def _start_tour(self):
        self.tour = TourOverlay(self)
        self.tour.start()

    # ---- misc ----
    def flash(self, text, color=None):
        self.status.setText(text)
        self.status.setStyleSheet(
            f"color: {color or GREY}; font-size: 10px; padding: 3px 20px 6px;")

    def closeEvent(self, e):
        self.worker.quit_loop()
        self.worker.wait(1500)
        super().closeEvent(e)


def QWidgetAction_preview(widget):
    """QAction holding a widget for menus (avoids importing QWidgets twice)."""
    from PyQt6.QtWidgets import QWidgetAction
    wa = QWidgetAction(widget)
    wa.setDefaultWidget(widget)
    return wa


def main():
    if "--selftest" in sys.argv:
        # frozen-artifact check (exe is windowed — write a report, no console output).
        # Verifies the OPTIONAL deps actually got bundled, before an owner hit the
        # "needs the optional pycaw dependency" fallback in the wild again.
        report = {"version": APP_VERSION, "frozen": getattr(sys, "frozen", False)}
        try:
            import hid  # noqa: F401
            report["hid_ok"] = True
        except Exception as e:
            report["hid_ok"] = False
            report["hid_error"] = str(e)
        try:
            from pycaw.pycaw import AudioUtilities, IAudioEndpointVolume  # noqa: F401
            from comtypes import CLSCTX_ALL  # noqa: F401
            report["pycaw_ok"] = True
        except Exception as e:
            report["pycaw_ok"] = False
            report["pycaw_error"] = str(e)
        try:
            hs = QuantumHeadset.find()
            report["device_present"] = True
            report["device_product"] = hs.product
            hs.close()
        except Exception as e:
            report["device_present"] = False
        try:
            import spatial_win
            st = spatial_win.get_spatial()
            report["spatial_tool_ok"] = bool(st.get("available"))
            report["spatial_endpoint"] = st.get("endpoint")
            report["spatial_current"] = st.get("mode")
        except Exception as e:
            report["spatial_tool_ok"] = False
            report["spatial_error"] = str(e)
        out = os.path.join(DATA_DIR, "selftest.json")
        save_json(out, report)
        return

    demo = "--demo" in sys.argv
    app = QApplication(sys.argv)
    app.setStyle("Fusion")
    app.setApplicationName(APP_NAME)
    icon_path = os.path.join(os.path.dirname(os.path.abspath(__file__)), "jblq_icon.ico")
    if os.path.exists(icon_path):
        app.setWindowIcon(QIcon(icon_path))
    w = MainWindow(demo=demo)
    w.show()
    sys.exit(app.exec())


if __name__ == "__main__":
    main()
