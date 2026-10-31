#!/usr/bin/env python3
"""JBL Quantum Engine (Linux) — v2 UI matching the CURRENT QuantumENGINE design.

Reference: official JBL showcase videos (jbl.com/quantum-engine media, downloaded
2026-10-31) — left icon rail with circular device avatars, "User Profile" pill,
rounded feature cards with purple preset pills, MORE > links, magenta EQ curve.
"""
import json
import os
import socket
import sys

from PyQt6.QtCore import Qt, QTimer, QRectF, QPointF
from PyQt6.QtGui import (QColor, QFont, QIcon, QPainter, QPen, QBrush, QPixmap,
                         QLinearGradient, QRadialGradient, QPainterPath)
from PyQt6.QtWidgets import (
    QApplication, QWidget, QLabel, QPushButton, QComboBox, QSlider, QVBoxLayout,
    QHBoxLayout, QGridLayout, QStackedWidget, QLineEdit, QRadioButton, QButtonGroup,
    QSpinBox, QInputDialog, QFrame, QScrollArea,
)

APP_NAME = "JBL Quantum Engine (Linux)"
APP_VERSION = "1.1.0"
SOCKET_PATH = os.path.join(
    os.environ.get("XDG_RUNTIME_DIR", f"/run/user/{os.getuid()}"), "jblq.sock")
PROFILE_FILE = os.path.expanduser("~/.config/jblq/profiles.json")

# palette from the current app
BG_TOP, BG_BOT = "#0d0a14", "#1c1230"
CARD = "#262130"
CARD_2 = "#2e2839"
WHITE = "#f2f2f4"
GREY = "#9b93a8"
DARKGREY = "#5f5870"
PURPLE = "#6f4ff2"
PURPLE_2 = "#8f6bff"
PINK = "#e05ce8"
RED = "#e8262d"
AMBER = "#e6b450"
GREEN = "#4ade80"

EQ_BANDS = ["31", "62", "125", "250", "500", "1k", "2k", "4k", "8k", "16k"]
EQ_PRESETS = {
    "RPG":        [2, 1, 0, 0, 1, 2, 3, 4, 3, 2],
    "FPS":        [-1, -1, 0, 1, 2, 4, 5, 3, 1, 0],
    "WARZONE":    [5, 2, 2, 4, 5, 1, 2, 5, 9, 10],
    "MOODY":      [3, 2, 0, -1, -2, -1, 0, 1, 2, 2],
    "CHILL":      [2, 2, 1, 0, -1, -2, -2, -1, 0, 0],
    "BASS BOOST": [8, 7, 5, 2, 0, 0, 0, 0, 0, 0],
    "VOCAL":      [-2, -1, 0, 2, 4, 5, 3, 1, 0, 0],
    "FLAT":       [0] * 10,
}
LIGHT_PRESETS = ["DEFAULT", "BREATH", "SOLID", "WAVE", "GLITCH", "SPIN CW", "SPIN CCW", "RISE", "OFF"]
LIGHT_BRIGHTNESS = [40, 50, 60, 70, 75, 80, 100]
SPATIAL_MODES = ["JBL QuantumSURROUND", "DTS", "OFF"]
SIDETONE_STEPS = ["OFF", "LOW", "MID", "HIGH"]


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


# ---------------- custom widgets ----------------

class Pill(QPushButton):
    """Purple gradient preset pill with chevron, like the current app."""
    def __init__(self, text, items=None, on_pick=None):
        super().__init__(" " + text + "  ⌄" if not items else " " + text + "  ⌄")
        self.setFixedHeight(34)
        self.setCursor(Qt.CursorShape.PointingHandCursor)
        self.setStyleSheet(
            "QPushButton { background: qlineargradient(x1:0,y1:0,x2:1,y2:0,"
            " stop:0 #6f4ff2, stop:1 #5531d6); color: white; border: none;"
            " border-radius: 8px; font-size: 12px; font-weight: bold; text-align: left;"
            " padding-left: 12px; }"
            "QPushButton:hover { background: qlineargradient(x1:0,y1:0,x2:1,y2:0,"
            " stop:0 #8f6bff, stop:1 #6a3fe8); }")
        self.items = items
        self.on_pick = on_pick

    def mousePressEvent(self, e):
        if self.items and self.on_pick:
            names = list(self.items)
            name, ok = QInputDialog.getItem(self, "Preset", "", names,
                                            names.index(self.text().strip().rstrip('⌄ ')) if self.text().strip().rstrip('⌄ ') in names else 0, False)
            if ok:
                self.setText(" " + name + "  ⌄")
                self.on_pick(name)
        else:
            self.on_pick(self.text()) if self.on_pick else None


class Card(QFrame):
    """Rounded dark card with title, optional toggle, MORE > footer."""
    def __init__(self, title, toggle_cb=None):
        super().__init__()
        self.setObjectName("card")
        self.setStyleSheet(
            "#card { background: #262130; border-radius: 12px; border: 1px solid #332b42; }")
        self.v = QVBoxLayout(self)
        self.v.setContentsMargins(14, 12, 14, 8)
        self.v.setSpacing(8)
        head = QWidget(); hh = QHBoxLayout(head); hh.setContentsMargins(0, 0, 0, 0)
        t = QLabel(title)
        t.setStyleSheet("color: #f2f2f4; font-size: 12px; font-weight: bold; letter-spacing: 1px;")
        hh.addWidget(t)
        hh.addStretch(1)
        if toggle_cb:
            self.toggle = Toggle(True, toggle_cb)
            hh.addWidget(self.toggle)
        self.v.addWidget(head)
        self._footer = None

    def add_more(self, cb):
        row = QWidget(); rh = QHBoxLayout(row); rh.setContentsMargins(0, 0, 0, 0)
        rh.addStretch(1)
        more = QLabel("MORE  ›")
        more.setStyleSheet(f"color: {DARKGREY}; font-size: 10px; letter-spacing: 1px;")
        more.setCursor(Qt.CursorShape.PointingHandCursor)
        more.mousePressEvent = lambda _: cb()
        rh.addWidget(more)
        self.v.addWidget(row)


class Toggle(QWidget):
    def __init__(self, checked=True, on_change=None):
        super().__init__()
        self.checked = checked
        self.on_change = on_change
        self.setFixedSize(38, 20)
        self.setCursor(Qt.CursorShape.PointingHandCursor)

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
        p.drawRoundedRect(QRectF(0, 0, self.width(), self.height()), 10, 10)
        p.setBrush(QBrush(QColor("white")))
        x = self.width() - 17 if self.checked else 3
        p.drawEllipse(QRectF(x, 3, 14, 14))


class RailButton(QWidget):
    """Circular avatar button on the left rail; active = lit ring."""
    def __init__(self, glyph, tip, on_click):
        super().__init__()
        self.glyph, self.tip, self.on_click = glyph, tip, on_click
        self.active = False
        self.setFixedSize(52, 44)
        self.setToolTip(tip)
        self.setCursor(Qt.CursorShape.PointingHandCursor)

    def mousePressEvent(self, _):
        self.on_click()

    def paintEvent(self, _):
        p = QPainter(self)
        p.setRenderHint(QPainter.RenderHint.Antialiasing)
        cx, cy, r = self.width() / 2, self.height() / 2, 16
        if self.active:
            p.setBrush(QBrush(QColor("#3a2f55")))
        else:
            p.setBrush(QBrush(QColor("#221c2e")))
        p.setPen(QPen(QColor(PURPLE_2 if self.active else "#3a3348"), 1.6))
        p.drawEllipse(QPointF(cx, cy), r, r)
        p.setPen(QPen(QColor("white" if self.active else GREY), 1.6))
        f = QFont("DejaVu Sans", 11)
        f.setBold(True)
        p.setFont(f)
        p.drawText(self.rect(), Qt.AlignmentFlag.AlignCenter, self.glyph)


class HeadsetHero(QWidget):
    """Big headset render + ambient rings, echoing the current home screen."""
    def paintEvent(self, _):
        p = QPainter(self)
        p.setRenderHint(QPainter.RenderHint.Antialiasing)
        w, h = self.width(), self.height()
        cx, cy = w / 2, h / 2
        for i, (rr, col) in enumerate(((h * 0.46, QColor(111, 79, 242, 40)),
                                       (h * 0.36, QColor(111, 79, 242, 60)),
                                       (h * 0.27, QColor(143, 107, 255, 80)))):
            p.setPen(QPen(col, 2))
            p.drawEllipse(QPointF(cx, cy), rr * 1.3, rr)
        pen = QPen(QColor(WHITE), 2.4)
        p.setPen(pen)
        # headband
        path = QPainterPath()
        path.moveTo(cx - 44, cy + 4)
        path.cubicTo(cx - 52, cy - 62, cx + 52, cy - 62, cx + 44, cy + 4)
        p.drawPath(path)
        # cups
        for sx in (-1, 1):
            ex = cx + sx * 56
            p.setBrush(QBrush(QColor("#171221")))
            p.drawEllipse(QPointF(ex, cy + 20), 22, 30)
            p.drawEllipse(QPointF(ex, cy + 20), 14, 21)
            p.drawLine(int(ex), int(cy - 8), int(ex + sx * 7), int(cy - 34))
        # mic boom
        p.drawLine(int(cx - 56), int(cy + 42), int(cx - 78), int(cy + 72))
        p.drawEllipse(QPointF(cx - 82, cy + 76), 6, 6)


class EqCurve(QWidget):
    """Magenta smooth EQ curve card body, draggable bands."""
    def __init__(self, values):
        super().__init__()
        self.values = values
        self.setMinimumHeight(120)
        self.setMouseTracking(True)

    def _band_at(self, x):
        n = len(self.values)
        x0, x1 = 14, self.width() - 14
        return max(0, min(n - 1, round((x - x0) / (x1 - x0) * (n - 1))))

    def mousePressEvent(self, e):
        self._drag(e)

    def mouseMoveEvent(self, e):
        if e.buttons() & Qt.MouseButton.LeftButton:
            self._drag(e)

    def _drag(self, e):
        i = self._band_at(e.position().x())
        y0, y1 = 6, self.height() - 22
        v = 10 - (e.position().y() - y0) / (y1 - y0) * 20
        self.values[i] = max(-10.0, min(10.0, round(v * 2) / 2))
        self.update()

    def paintEvent(self, _):
        p = QPainter(self)
        p.setRenderHint(QPainter.RenderHint.Antialiasing)
        w, h = self.width(), self.height()
        n = len(self.values)
        x0, x1 = 14, w - 14
        ytop, ybot = 6, h - 22
        p.setPen(QPen(QColor("#3a3348"), 1))
        p.drawLine(int(x0), int((ytop + ybot) / 2), int(x1), int((ytop + ybot) / 2))
        xs = [x0 + i * (x1 - x0) / (n - 1) for i in range(n)]
        ys = [ytop + (10 - v) / 20 * (ybot - ytop) for v in self.values]
        pts = []
        for i in range(n - 1):
            p0 = ys[i - 1] if i > 0 else ys[i]
            p1, p2 = ys[i], ys[i + 1]
            p3 = ys[i + 2] if i + 2 < n else ys[i + 1]
            for t in range(10):
                t /= 10
                t2, t3 = t * t, t * t * t
                y = 0.5 * ((2 * p1) + (-p0 + p2) * t + (2 * p0 - 5 * p1 + 4 * p2 - p3) * t2
                           + (-p0 + 3 * p1 - 3 * p2 + p3) * t3)
                pts.append((xs[i] + (xs[i + 1] - xs[i]) * t, y))
        flat = [c for pt in pts for c in pt]
        p.setPen(QPen(QColor(PINK), 3))
        p.drawPolyline(*[QPointF(a, b) for a, b in pts])
        p.setBrush(QBrush(QColor(PINK)))
        p.setPen(Qt.PenStyle.NoPen)
        for x, y in zip(xs, ys):
            p.drawEllipse(QPointF(x, y), 2.6, 2.6)
        p.setPen(QPen(QColor(GREY), 1))
        p.setFont(QFont("DejaVu Sans", 7))
        for x, b in zip(xs, EQ_BANDS):
            p.drawText(int(x - 16), int(ybot + 4), 32, 14, Qt.AlignmentFlag.AlignHCenter, b)


class ColorSlider(QWidget):
    def __init__(self, on_change=None):
        super().__init__()
        self.hue = 0.95
        self.on_change = on_change
        self.setFixedHeight(16)
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
        grad = QLinearGradient(0, 0, self.width(), 0)
        for i in range(7):
            grad.setColorAt(i / 6, QColor.fromHsvF(i / 6, 1, 1))
        p.fillRect(self.rect().adjusted(0, 2, 0, -2), grad)
        p.setPen(QPen(QColor(WHITE), 2))
        p.drawRect(QRectF(self.hue * self.width() - 3, 0, 6, self.height()))


class BatteryChip(QWidget):
    def __init__(self):
        super().__init__()
        self.percent = None
        self.charging = False
        self.setFixedSize(120, 24)

    def paintEvent(self, _):
        p = QPainter(self)
        p.setRenderHint(QPainter.RenderHint.Antialiasing)
        p.setFont(QFont("DejaVu Sans", 9))
        p.setPen(QPen(QColor(WHITE), 1))
        if self.charging:
            p.drawText(0, 0, 70, 24, Qt.AlignmentFlag.AlignVCenter,
                       "⚡ charging*")
        else:
            p.drawText(0, 0, 46, 24, Qt.AlignmentFlag.AlignVCenter,
                       "—" if self.percent is None else f"{self.percent}%")
        bx, by, bw, bh = (74, 6, 20, 12) if self.charging else (46, 6, 20, 12)
        p.setPen(QPen(QColor(WHITE), 1.2))
        p.drawRoundedRect(QRectF(bx, by, bw, bh), 3, 3)
        p.drawRect(QRectF(bx + bw, by + 3.5, 2.5, 5))
        if self.percent is not None:
            p.setBrush(QBrush(QColor(GREEN if self.percent > 20 else RED)))
            p.setPen(Qt.PenStyle.NoPen)
            p.drawRoundedRect(QRectF(bx + 2, by + 2, (bw - 4) * max(0, min(1, self.percent / 100)), bh - 4), 2, 2)


# ---------------- main window ----------------

class QuantumUI(QWidget):
    def __init__(self, demo=False):
        super().__init__()
        self.setWindowTitle(APP_NAME)
        self.resize(1020, 660)
        self.setStyleSheet(f"""
            QWidget {{ background: transparent; color: {WHITE}; font-size: 12px; }}
            QComboBox, QLineEdit, QSpinBox {{
                background: {CARD_2}; border: 1px solid #3a3348; border-radius: 8px;
                color: {WHITE}; padding: 4px 8px; }}
            QSlider::groove:horizontal {{ height: 4px; background: #3a3348; border-radius: 2px; }}
            QSlider::handle:horizontal {{ background: {PURPLE_2}; width: 14px; height: 14px;
                margin: -6px 0; border-radius: 7px; }}
            QSlider::sub-page:horizontal {{ background: {PURPLE}; border-radius: 2px; }}
        """)
        self.demo = demo
        self.demo_state = {
            "present": True, "product": "JBL Quantum 810 Wireless", "battery": 80,
            "dial": 11, "anc": "on", "sidetone": "low", "lights": True, "mic": False,
            "auto_off_min": 60, "serial": "DEMO0810WRLSS00",
            "firmware": "1.2.7 / 0.9.4 / 2.1.0 / 1.0.3",
        }
        self.eq_values = list(EQ_PRESETS["RPG"])
        self.eq_preset = "RPG"
        self.light_preset = "DEFAULT"
        self.zone_hue = {"LOGO": 0.95, "RING": 0.45}
        self.zone_speed = {"LOGO": 3, "RING": 3}
        self.sync_all = False
        self.profiles = self._load_profiles()
        self._build()
        self._tick()
        QTimer(self, interval=2000, timeout=self._tick).start()

    # ---- shell ----
    def _build(self):
        root = QHBoxLayout(self)
        root.setContentsMargins(0, 0, 0, 0)
        root.setSpacing(0)

        # left icon rail
        rail = QWidget()
        rail.setFixedWidth(64)
        rail.setStyleSheet("background: #171221;")
        rv = QVBoxLayout(rail)
        rv.setContentsMargins(6, 12, 6, 12)
        rv.setSpacing(6)
        self.rail_buttons = []
        for i, (glyph, tip) in enumerate((("◉", "Headset — home"),
                                          ("🎙", "Microphone"),
                                          ("✦", "Spatial sound"),
                                          ("⚙", "System software"))):
            rb = RailButton(glyph, tip, lambda idx=i: self._nav(idx))
            rv.addWidget(rb, 0, Qt.AlignmentFlag.AlignHCenter)
            self.rail_buttons.append(rb)
        rv.addStretch(1)
        demo_rb = RailButton("D", "Demo mode (no headset)", self._toggle_demo)
        demo_rb.active = self.demo
        self.demo_rail = demo_rb
        rv.addWidget(demo_rb, 0, Qt.AlignmentFlag.AlignHCenter)
        root.addWidget(rail)

        # main column
        main = QWidget()
        mv = QVBoxLayout(main)
        mv.setContentsMargins(0, 0, 0, 0)
        mv.setSpacing(0)
        main.setStyleSheet(
            f"background: qlineargradient(x1:0,y1:0,x2:0,y2:1, stop:0 {BG_TOP}, stop:1 {BG_BOT});")

        # header
        head = QWidget(); hh = QHBoxLayout(head); hh.setContentsMargins(18, 12, 18, 4)
        self.h_title = QLabel("JBL Quantum 810 Wireless")
        self.h_title.setStyleSheet("font-size: 15px; font-weight: bold; color: white;")
        hh.addWidget(self.h_title)
        hh.addStretch(1)
        self.battery = BatteryChip()
        hh.addWidget(self.battery)
        prof = QPushButton("   User Profile   ")
        prof.setCursor(Qt.CursorShape.PointingHandCursor)
        prof.setFixedHeight(30)
        prof.clicked.connect(self._profile_dialog)
        prof.setStyleSheet(
            f"QPushButton {{ background: {CARD_2}; border: 1px solid #3a3348; border-radius: 15px;"
            f" color: {WHITE}; padding: 0 14px; }}"
            f"QPushButton:hover {{ border-color: {PURPLE_2}; }}")
        hh.addWidget(prof)
        demo_pill = QPushButton("DEMO")
        demo_pill.setCheckable(True)
        demo_pill.setChecked(self.demo)
        demo_pill.setFixedSize(58, 30)
        demo_pill.setCursor(Qt.CursorShape.PointingHandCursor)
        self._style_demo(demo_pill)
        demo_pill.toggled.connect(self._toggle_demo)
        self.demo_pill = demo_pill
        hh.addWidget(demo_pill)
        mv.addWidget(head)

        self.demo_banner = QLabel("  DEMO MODE — nothing is sent to hardware  ")
        self.demo_banner.setStyleSheet(
            f"background: {AMBER}; color: #141416; font-size: 10px; font-weight: bold;"
            f" letter-spacing: 1px; border-radius: 0px;")
        self.demo_banner.setFixedHeight(20)
        self.demo_banner.setVisible(self.demo)
        mv.addWidget(self.demo_banner)

        self.stack = QStackedWidget()
        self.stack.addWidget(self._page_home())      # 0
        self.stack.addWidget(self._page_mic())       # 1
        self.stack.addWidget(self._page_spatial())   # 2
        self.stack.addWidget(self._page_system())    # 3
        mv.addWidget(self.stack, 1)

        self.status = QLabel(" ")
        self.status.setStyleSheet(f"color: {GREY}; font-size: 10px; padding: 2px 18px 6px;")
        mv.addWidget(self.status)

        root.addWidget(main, 1)
        self._nav(0)

    def _nav(self, idx):
        for i, b in enumerate(self.rail_buttons):
            b.active = (i == idx)
            b.update()
        self.stack.setCurrentIndex(idx)

    def _toggle_demo(self, *a):
        self.demo = not self.demo
        self.demo_pill.setChecked(self.demo)
        self._style_demo(self.demo_pill)
        self.demo_rail.active = self.demo
        self.demo_rail.update()
        self.demo_banner.setVisible(self.demo)
        self._tick()

    def _style_demo(self, btn):
        on = btn.isChecked()
        btn.setStyleSheet(
            f"QPushButton {{ background: {'#e6b450' if on else 'transparent'};"
            f" color: {'#141416' if on else GREY}; border: 1px solid #e6b450;"
            f" border-radius: 15px; font-size: 10px; font-weight: bold; }}")

    # ---- pages ----
    def _page_home(self):
        pg = QWidget()
        v = QVBoxLayout(pg)
        v.setContentsMargins(18, 4, 18, 8)
        v.setSpacing(10)
        hero = HeadsetHero()
        hero.setMinimumHeight(130)
        v.addWidget(hero, 0, Qt.AlignmentFlag.AlignHCenter)

        vol_row = QWidget(); vh = QHBoxLayout(vol_row); vh.setContentsMargins(0, 0, 0, 0)
        self.dial_dots = DialDotsWidget()
        vh.addWidget(self.dial_dots, 2)
        vh.addWidget(self._cap("VOLUME"))
        self.volume = QSlider(Qt.Orientation.Horizontal)
        self.volume.setRange(0, 100); self.volume.setValue(100); self.volume.setFixedWidth(180)
        self.volume.sliderReleased.connect(self._set_volume)
        vh.addWidget(self.volume)
        v.addWidget(vol_row)

        grid = QGridLayout()
        grid.setSpacing(12)
        # EQUALIZER card
        eq_card = Card("EQUALIZER", toggle_cb=None)
        self.eq_curve = EqCurve(self.eq_values)
        eq_card.v.addWidget(self.eq_curve)
        self.eq_pill = Pill(self.eq_preset, items=EQ_PRESETS.keys(), on_pick=self._eq_preset)
        eq_card.v.addWidget(self.eq_pill)
        self.eq_extra = QWidget()
        ex = QHBoxLayout(self.eq_extra); ex.setContentsMargins(0, 0, 0, 0)
        self.eq_save = QLineEdit(); self.eq_save.setPlaceholderText("save custom preset…")
        self.eq_save.returnPressed.connect(self._eq_save_custom)
        ex.addWidget(self.eq_save, 1)
        eq_card.v.addWidget(self.eq_extra)
        self.eq_extra.hide()
        eq_card.add_more(lambda: (self.eq_extra.setVisible(not self.eq_extra.isVisible()),
                                  self.eq_more.setText("LESS  ‹") if self.eq_more.text().startswith("MORE") else self.eq_more.setText("MORE  ›")))
        self.eq_more = eq_card.findChildren(QLabel)[-1]
        grid.addWidget(eq_card, 0, 0)

        # LIGHTING card
        lt_card = Card("LIGHTING", toggle_cb=lambda on: self.set_dev("lights", on))
        self.light_pill = Pill(self.light_preset, items=LIGHT_PRESETS, on_pick=self._light_preset)
        lt_card.v.addWidget(self.light_pill)
        for zone in ("LOGO", "RING"):
            row = QWidget(); rh = QHBoxLayout(row); rh.setContentsMargins(0, 2, 0, 2); rh.setSpacing(8)
            zl = self._cap(zone); zl.setFixedWidth(38)
            rh.addWidget(zl)
            cs = ColorSlider(on_change=lambda h, z=zone: self._zone_colour(z, h))
            cs.set_hue = lambda h, c=cs: c.set_hue(h)
            cs.hue = self.zone_hue[zone]
            rh.addWidget(cs, 1)
            br = QSlider(Qt.Orientation.Horizontal); br.setRange(0, 6)
            br.setValue(self.zone_speed[zone]); br.setFixedWidth(70)
            br.valueChanged.connect(lambda val, z=zone: self._zone_brightness(z, val))
            rh.addWidget(br)
            self.zone_rows = getattr(self, "zone_rows", {})
            self.zone_rows[zone] = row
            lt_card.v.addWidget(row)
        lt_card.add_more(lambda: self.flash("zones: logo + ring (mirrored); brightness values 40–100% verified"))
        grid.addWidget(lt_card, 0, 1)

        # NOISE CANCELLING card
        nc_card = Card("NOISE CANCELLING", toggle_cb=None)
        self.anc_pill = Pill(" ANC", items=["OFF", "ANC", "AMBIENT AWARE"], on_pick=self._anc_pick)
        nc_card.v.addWidget(self.anc_pill)
        note = QLabel("verified report 0x46 — the 810's physical button cycles this too")
        note.setWordWrap(True)
        note.setStyleSheet(f"color: {DARKGREY}; font-size: 9px;")
        nc_card.v.addWidget(note)
        grid.addWidget(nc_card, 0, 2)
        v.addLayout(grid, 1)
        return pg

    def _page_mic(self):
        pg = QWidget()
        v = QVBoxLayout(pg); v.setContentsMargins(18, 10, 18, 8)
        mc = Card("MICROPHONE")
        vr = QWidget(); vh = QHBoxLayout(vr); vh.setContentsMargins(0, 0, 0, 0)
        vh.addWidget(self._cap("Volume:"))
        self.mic_state_lbl = QLabel("—")
        self.mic_state_lbl.setStyleSheet(f"color: {WHITE}; font-weight: bold;")
        vh.addStretch(1)
        vh.addWidget(self.mic_state_lbl)
        mc.v.addWidget(vr)
        hint = QLabel("boom mic down + headset mute button control the mic (hardware-side)")
        hint.setWordWrap(True)
        hint.setStyleSheet(f"color: {GREY}; font-size: 10px;")
        mc.v.addWidget(hint)
        sv = QWidget(); sh = QHBoxLayout(sv); sh.setContentsMargins(0, 4, 0, 0); sh.setSpacing(10)
        sh.addWidget(self._cap("Audio/Voice Monitor"))
        self.sidetone_pill = Pill(" LOW", items=SIDETONE_STEPS,
                                  on_pick=lambda n: self.set_dev("sidetone", n.lower()))
        sh.addWidget(self.sidetone_pill, 1)
        mc.v.addWidget(sv)
        mc.add_more(lambda: self.flash("sidetone = verified report 0x5D (4-step enum)"))
        v.addWidget(mc)
        v.addStretch(1)
        return pg

    def _page_spatial(self):
        pg = QWidget()
        v = QVBoxLayout(pg); v.setContentsMargins(18, 10, 18, 8)
        sc = Card("SPATIAL SOUND")
        self.spatial_pill = Pill(" JBL QuantumSURROUND", items=SPATIAL_MODES,
                                 on_pick=lambda n: self.flash(
                                     "spatial is host-side — the real app never sends it to the dongle (proven); PipeWire pending"))
        sc.v.addWidget(self.spatial_pill)
        note = QLabel("host-side even in the real app — Linux wiring via PipeWire filter-chain pending")
        note.setWordWrap(True)
        note.setStyleSheet(f"color: {DARKGREY}; font-size: 9px;")
        sc.v.addWidget(note)
        sc.add_more(lambda: self.flash("DTS Headphone:X v2.0 / QuantumSURROUND are host-side modes"))
        v.addWidget(sc)
        v.addStretch(1)
        return pg

    def _page_system(self):
        pg = QWidget()
        v = QVBoxLayout(pg); v.setContentsMargins(18, 10, 18, 8)
        sc = Card("SYSTEM SOFTWARE")
        self.sys_info = QLabel("—")
        self.sys_info.setStyleSheet(f"color: {WHITE};")
        sc.v.addWidget(self.sys_info)
        ap = self._cap("AUTO POWER OFF — verified report 0x75 (5-min units, verify by read-back)")
        sc.v.addWidget(ap)
        self.autoff_pill = Pill(" 60 MIN", items=["NEVER", "30 MIN", "60 MIN", "120 MIN"],
                                on_pick=lambda n: self.set_dev(
                                    "auto_off", 0 if n == "NEVER" else int(n.split()[0])))
        sc.v.addWidget(self.autoff_pill)
        rs = QPushButton("RESTORE FACTORY SETTINGS (undo our writes)")
        rs.setFixedHeight(30)
        rs.setCursor(Qt.CursorShape.PointingHandCursor)
        rs.setStyleSheet(
            f"QPushButton {{ background: {CARD_2}; border: 1px solid #3a3348; border-radius: 8px;"
            f" color: {WHITE}; }} QPushButton:hover {{ border-color: {PURPLE_2}; }}")
        rs.clicked.connect(self._restore)
        sc.v.addWidget(rs)
        sc.add_more(lambda: self.flash("firmware updates deliberately disabled — no firmware flows"))
        v.addWidget(sc)
        v.addStretch(1)
        return pg

    # ---- helpers ----
    @staticmethod
    def _cap(txt):
        l = QLabel(txt)
        l.setStyleSheet(f"color: {GREY}; font-size: 11px;")
        return l

    def _eq_preset(self, name):
        if name in EQ_PRESETS:
            self.eq_values[:] = EQ_PRESETS[name]
            self.eq_curve.values = self.eq_values
            self.eq_curve.update()
        self.flash(f"EQ preset {name} — host-side (PipeWire pending)")

    def _eq_save_custom(self):
        name = self.eq_save.text().strip().upper()
        if name:
            EQ_PRESETS[name] = list(self.eq_values)
            self.eq_pill.items = list(EQ_PRESETS.keys())
            self.eq_pill.setText(" " + name + "  ⌄")
            self.flash(f"custom preset '{name}' saved (local)")

    def _light_preset(self, name):
        self.light_preset = name
        if name == "OFF":
            self.set_dev("lights", False)
            return
        self.set_dev("lights", True)
        mode = LIGHT_PRESETS.index(name)
        for zone in ("LOGO", "RING"):
            self.set_dev("light_colour", {
                "element": 0 if zone == "LOGO" else 1, "slot": 0,
                "rgb": self._hue_rgb(self.zone_hue[zone]), "mode": mode - 1 if mode else 1,
                "last": 0})

    def _anc_pick(self, name):
        self.set_dev("anc", {"OFF": "off", "ANC": "on",
                             "AMBIENT AWARE": "talkthru"}.get(name, "off"))

    def _zone_colour(self, zone, hue):
        self.zone_hue[zone] = hue
        payload = {"element": 0 if zone == "LOGO" else 1, "slot": 0,
                   "rgb": self._hue_rgb(hue),
                   "mode": max(0, LIGHT_PRESETS.index(self.light_pill.text().strip().rstrip('⌄ ')) - 1),
                   "last": 0}
        self.set_dev("light_colour", payload)
        if self.sync_all:
            other = "RING" if zone == "LOGO" else "LOGO"
            self.zone_hue[other] = hue
            self.zone_rows[other].findChild(ColorSlider).set_hue(hue)
            self.set_dev("light_colour", {**payload, "element": 0 if other == "LOGO" else 1})

    def _zone_brightness(self, zone, val):
        self.zone_speed[zone] = val
        self.set_dev("light_zone", {
            "element": 0 if zone == "LOGO" else 1,
            "brightness": LIGHT_BRIGHTNESS[max(0, min(6, val))], "segments": 5})

    @staticmethod
    def _hue_rgb(h):
        c = QColor.fromHsvF(max(0.0, min(1.0, h)), 1, 1)
        return [c.red(), c.green(), c.blue()]

    def _set_volume(self):
        val = self.volume.value()
        if self.demo:
            self.flash(f"volume {val}% (demo — nothing sent)")
            return
        import subprocess
        try:
            subprocess.run(["pactl", "set-sink-volume", "@DEFAULT_SINK@", f"{val}%"],
                           timeout=3, check=False)
            self.flash(f"system volume → {val}%")
        except Exception as e:
            self.flash(f"volume failed: {e}", RED)

    def _restore(self):
        if self.demo:
            self.flash("demo — nothing sent to hardware")
            return
        import subprocess
        out = subprocess.run([sys.executable, os.path.join(os.path.dirname(__file__), "jblq"),
                              "restore"], capture_output=True, text=True, timeout=15)
        self.flash(out.stdout.strip() or out.stderr.strip() or "restore done")

    # ---- profiles ----
    @staticmethod
    def _load_profiles():
        try:
            with open(PROFILE_FILE) as f:
                return json.load(f)
        except Exception:
            return {}

    def _save_profiles(self):
        os.makedirs(os.path.dirname(PROFILE_FILE), exist_ok=True)
        with open(PROFILE_FILE, "w") as f:
            json.dump(self.profiles, f, indent=1)

    def _current_profile(self):
        return {"eq": list(self.eq_values), "eq_preset": self.eq_preset,
                "light_preset": self.light_preset,
                "hue": dict(self.zone_hue), "speed": dict(self.zone_speed)}

    def _apply_profile(self, d):
        self.eq_values[:] = d.get("eq", [0] * 10)
        self.eq_curve.values = self.eq_values
        self.eq_curve.update()
        for z in ("LOGO", "RING"):
            self.zone_hue[z] = d.get("hue", {}).get(z, 0.95 if z == "LOGO" else 0.45)
            row = self.zone_rows[z]
            row.findChild(ColorSlider).set_hue(self.zone_hue[z])

    def _profile_dialog(self):
        names = list(self.profiles.keys())
        name, ok = QInputDialog.getItem(self, "User Profile", "Load / overwrite:",
                                        ["+ NEW PROFILE…"] + names, 0, False)
        if not ok:
            return
        if name == "+ NEW PROFILE…":
            name, ok = QInputDialog.getText(self, "New profile", "Name:")
            name = name.strip().upper()
            if not ok or not name:
                return
        self.profiles[name] = self._current_profile()
        self._save_profiles()
        self.flash(f"profile '{name}' saved")

    def set_dev(self, feature, value):
        if self.demo:
            key = {"auto_off": "auto_off_min"}.get(feature, feature)
            self.demo_state[key] = value * 5 if feature == "auto_off" else value
            self.flash(f"{feature} → {value}   (demo — nothing sent to hardware)", AMBER)
            return
        resp = daemon_request({"cmd": "set", "feature": feature, "value": value})
        if resp.get("ok"):
            self.flash(f"{feature} → {value}")
            daemon_request({"cmd": "refresh"})
        else:
            self.flash(resp.get("error", "write failed"), RED)

    def flash(self, text, color=None):
        self.status.setText(text)
        self.status.setStyleSheet(f"color: {color or GREY}; font-size: 10px; padding: 2px 18px 6px;")

    # ---- state ----
    def _tick(self):
        st = daemon_request({"cmd": "state"})
        live = bool(st.get("present"))
        if self.demo and not live:
            st = dict(self.demo_state)
        elif not live:
            self.battery.percent = None
            self.battery.update()
            self.h_title.setText("JBL Quantum — no headset detected")
            self.sys_info.setText("No headset detected. Plug in the Quantum 810 dongle — it connects automatically.")
            self.demo_banner.setVisible(self.demo)
            return
        self.demo_banner.setVisible(self.demo)
        self.h_title.setText(st.get("product", "JBL Quantum"))
        self.battery.percent = st.get("battery")
        self.battery.charging = bool(st.get("charging"))
        self.battery.update()
        self.dial_dots.value = st.get("dial") or 0
        self.dial_dots.update()
        mic = st.get("mic")
        self.mic_state_lbl.setText(("ON" if mic else "OFF") if mic is not None else "—")
        sid = st.get("sidetone")
        if sid in ("off", "low", "mid", "high"):
            self.sidetone_pill.setText(" " + sid.upper() + "  ⌄")
        anc = st.get("anc")
        if anc in ("off", "on", "talkthru"):
            self.anc_pill.setText(" " + {"off": "OFF", "on": "ANC",
                                         "talkthru": "AMBIENT AWARE"}[anc] + "  ⌄")
        aom = st.get("auto_off_min")
        if aom is not None:
            self.autoff_pill.setText(" " + ("NEVER" if aom == 0 else f"{aom} MIN") + "  ⌄")
        self.sys_info.setText(
            f"product   : {st.get('product', '—')}\n"
            f"battery   : {st.get('battery', '—')}%\n"
            f"serial    : {st.get('serial', '—')}\n"
            f"firmware  : {st.get('firmware', '—')}\n"
            f"dial      : {st.get('dial', '—')}/16")


class DialDotsWidget(QWidget):
    def __init__(self):
        super().__init__()
        self.value = 11
        self.setFixedHeight(22)

    def paintEvent(self, _):
        p = QPainter(self)
        p.setRenderHint(QPainter.RenderHint.Antialiasing)
        n, w, h = 10, self.width(), self.height()
        gap = 13
        x0 = (w - n * gap) / 2 + gap / 2
        filled = round(self.value / 16 * n)
        for i in range(n):
            x = x0 + i * gap
            p.setBrush(QBrush(QColor(PURPLE_2 if i < filled else "#3a3348")))
            p.setPen(Qt.PenStyle.NoPen)
            p.drawEllipse(QPointF(x, h / 2), 3.4, 3.4)


def main():
    app = QApplication(sys.argv)
    w = QuantumUI(demo="--demo" in sys.argv)
    w.show()
    sys.exit(app.exec())


if __name__ == "__main__":
    main()
