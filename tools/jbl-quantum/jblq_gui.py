#!/usr/bin/env python3
"""JBL Quantum Engine (Linux) — replica of QuantumENGINE for JBL Quantum headsets.

The UI reproduces the real QuantumENGINE (v2.x) interface from screen recordings and
the app's own strings. Protocol facts are documented in research/jbl-quantum/PROTOCOL.md
(community-verified + independently confirmed from public USB captures).

Honesty layer:
  * device-verified controls (ANC/AA, sidetone, lights, auto-off, battery, dial) write
    through the jblq daemon;
  * spatial/EQ are host-side even in the real app — marked as such; PipeWire pending;
  * DEMO pill forces a fully populated UI with no headset (nothing sent to hardware).
"""
import json
import os
import socket
import sys

from PyQt6.QtCore import Qt, QTimer, QRectF, QPointF
from PyQt6.QtGui import (QColor, QFont, QIcon, QPainter, QPen, QBrush, QPixmap,
                         QLinearGradient, QPainterPath)
from PyQt6.QtWidgets import (
    QApplication, QWidget, QLabel, QPushButton, QComboBox, QSlider, QVBoxLayout,
    QHBoxLayout, QGridLayout, QStackedWidget, QLineEdit, QRadioButton, QButtonGroup,
    QSpinBox, QMessageBox, QInputDialog,
)

APP_NAME = "JBL Quantum Engine (Linux)"
APP_VERSION = "1.0.0"
SOCKET_PATH = os.path.join(
    os.environ.get("XDG_RUNTIME_DIR", f"/run/user/{os.getuid()}"), "jblq.sock")
PROFILE_FILE = os.path.expanduser("~/.config/jblq/profiles.json")

BG, PANEL, CARD = "#141416", "#1b1b1e", "#202024"
WHITE, GREY, DARKGREY, RED = "#f2f2f2", "#9a9a9f", "#5a5a60", "#e8262d"
HAIR, AMBER = "#3a3a3f", "#e6b450"

RAIL = ["EQUALIZER", "LIGHTING", "SPATIAL SOUND", "MICROPHONE", "SYSTEM SOFTWARE", "HELP"]
RAIL_EXTRA = ["NOISE CANCELLING"]  # our verified addition beyond QE 2.x
EQ_BANDS = ["31Hz", "62Hz", "125Hz", "250Hz", "500Hz", "1kHz", "2kHz", "4kHz", "8kHz", "16kHz"]
EQ_PRESETS = {
    "MUSIC BOOST":   [5, 4, 2, 0, -1, 0, 2, 3, 4, 4],
    "HARD RESET":    [6, 5, 3, 1, 0, 0, 2, 4, 5, 5],
    "QUIETY":        [-3, -2, -1, 0, 1, 1, 0, -1, -2, -3],
    "FLAT":          [0] * 10,
    "GAMING":        [2, 1, 0, 0, 1, 2, 3, 4, 3, 2],
    "VOICE BOOST":   [-4, -3, -1, 1, 3, 5, 4, 2, 0, -1],
    "LOFI VERSION":  [4, 3, 1, 0, -1, -2, -3, -3, -2, -1],
    "WARZONE":       [5, 2, 2, 4, 5, 1, 2, 5, 9, 10],
}
LIGHT_PRESETS = ["BREATH", "SOLID", "WAVE", "GLITCH", "SPIN CW", "SPIN CCW", "RISE", "OFF"]
SPEED_BYTES = [0x28, 0x32, 0x3C, 0x46, 0x4B, 0x50, 0x64]


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


# ---------------- custom painted widgets ----------------

class HatchStrip(QWidget):
    def paintEvent(self, _):
        p = QPainter(self)
        p.fillRect(self.rect(), QColor(BG))
        p.setPen(QPen(QColor("#2e2e33"), 1))
        step = 7
        for x in range(-self.height(), self.width() + step, step):
            p.drawLine(x, self.height(), x + self.height(), 0)


class DialDots(QWidget):
    def __init__(self):
        super().__init__()
        self.value = 11
        self.setFixedHeight(26)

    def paintEvent(self, _):
        p = QPainter(self)
        n, w, h = 10, self.width(), self.height()
        gap, dot_r = 13, 2.2
        x0 = 40 + (w - 80 - n * gap) / 2 + gap / 2
        y = h / 2
        filled = round(self.value / 16 * n)
        p.setFont(QFont("DejaVu Sans", 7))
        p.setPen(QPen(QColor(GREY), 1))
        p.drawText(0, 0, 34, h, Qt.AlignmentFlag.AlignVCenter, "CHAT")
        p.drawText(w - 36, 0, 36, h, Qt.AlignmentFlag.AlignVCenter, "GAME")
        for i in range(n):
            x = x0 + i * gap
            p.setBrush(QBrush(QColor(WHITE if i < filled else Qt.GlobalColor.transparent)))
            p.setPen(QPen(QColor(WHITE if i < filled else DARKGREY), 1.2))
            p.drawEllipse(QPointF(x, y), dot_r, dot_r)


class BatteryIcon(QWidget):
    def __init__(self):
        super().__init__()
        self.percent = None
        self.setFixedSize(46, 22)

    def paintEvent(self, _):
        p = QPainter(self)
        p.setRenderHint(QPainter.RenderHint.Antialiasing)
        p.setFont(QFont("DejaVu Sans", 8))
        p.setPen(QPen(QColor(GREY), 1))
        p.drawText(0, 0, 42, 22, Qt.AlignmentFlag.AlignVCenter,
                   "—" if self.percent is None else f"{self.percent}%")
        # battery glyph
        bx, by, bw, bh = 24, 6, 16, 10
        p.setPen(QPen(QColor(WHITE), 1.2))
        p.drawRect(QRectF(bx, by, bw, bh))
        p.drawRect(QRectF(bx + bw, by + 3, 2.5, 4))
        if self.percent is not None:
            fill = max(0, min(1, self.percent / 100))
            p.setBrush(QBrush(QColor("#4ade80" if self.percent > 20 else RED)))
            p.drawRect(QRectF(bx + 2, by + 2, (bw - 4) * fill, bh - 4))


class Toggle(QWidget):
    def __init__(self, checked=False, on_change=None):
        super().__init__()
        self.checked = checked
        self.on_change = on_change
        self.setFixedSize(34, 16)
        self.setCursor(Qt.CursorShape.PointingHandCursor)

    def mousePressEvent(self, _):
        self.checked = not self.checked
        self.update()
        if self.on_change:
            self.on_change(self.checked)

    def paintEvent(self, _):
        p = QPainter(self)
        p.setPen(QPen(QColor(WHITE), 1.4))
        p.drawRect(QRectF(0.5, 0.5, self.width() - 1, self.height() - 1))
        p.setBrush(QBrush(QColor(WHITE)))
        x = 3 if self.checked else self.width() - 13
        p.drawRect(QRectF(x, 3, 10, self.height() - 6))


class HeadsetVisual(QWidget):
    """Red wireframe headset, echoing the real app's 3D model view."""
    def paintEvent(self, _):
        p = QPainter(self)
        p.setRenderHint(QPainter.RenderHint.Antialiasing)
        w, h = self.width(), self.height()
        pen = QPen(QColor(RED), 1.6)
        p.setPen(pen)
        cx, cy = w / 2, h / 2
        # head band
        path = QPainterPath()
        path.moveTo(cx - 42, cy + 8)
        path.cubicTo(cx - 48, cy - 58, cx + 48, cy - 58, cx + 42, cy + 8)
        p.drawPath(path)
        for off in (-3, 3):  # band thickness
            p.drawArc(int(cx - 46 - off), int(cy - 56), 92 + 2 * off, 90, 180 * 16, 180 * 16)
        # ear cups
        for sx in (-1, 1):
            ex = cx + sx * 52
            p.drawEllipse(QPointF(ex, cy + 22), 20, 27)
            p.drawEllipse(QPointF(ex, cy + 22), 13, 19)
            # yokes
            p.drawLine(int(ex), int(cy + 22 - 27), int(ex + sx * 6), int(cy - 24))
        # mic boom from left cup
        p.drawLine(int(cx - 52), int(cy + 40), int(cx - 70), int(cy + 66))
        p.drawEllipse(QPointF(cx - 73, cy + 70), 6, 6)


class EqBars(QWidget):
    def __init__(self, values):
        super().__init__()
        self.values = values
        self.setMinimumHeight(220)
        self.setMouseTracking(True)

    def _band_at(self, x):
        n = len(self.values)
        x0, x1 = 50, self.width() - 30
        return max(0, min(n - 1, round((x - x0) / (x1 - x0) * (n - 1))))

    def mousePressEvent(self, e):
        self._drag(e)

    def mouseMoveEvent(self, e):
        if e.buttons() & Qt.MouseButton.LeftButton:
            self._drag(e)

    def _drag(self, e):
        i = self._band_at(e.position().x())
        y0, y1 = 14, self.height() - 30
        v = 10 - (e.position().y() - y0) / (y1 - y0) * 20
        self.values[i] = max(-10.0, min(10.0, round(v * 2) / 2))
        self.update()

    def paintEvent(self, _):
        p = QPainter(self)
        p.setRenderHint(QPainter.RenderHint.Antialiasing)
        w, h = self.width(), self.height()
        n = len(self.values)
        x0, x1 = 50, w - 30
        ytop, ybot = 14, h - 30
        p.setFont(QFont("DejaVu Sans", 7))
        for db in (10, 5, 0, -5, -10):
            y = ytop + (10 - db) / 20 * (ybot - ytop)
            p.setPen(QPen(QColor(HAIR), 1))
            p.drawLine(int(x0), int(y), int(x1), int(y))
            p.setPen(QPen(QColor(GREY), 1))
            p.drawText(4, int(y) - 6, 40, 12, Qt.AlignmentFlag.AlignLeft, f"{db:+d}dB")
        bw = (x1 - x0) / (n - 1)
        for i, v in enumerate(self.values):
            x = x0 + i * bw
            yz = ytop + 10 / 20 * (ybot - ytop)
            y = ytop + (10 - v) / 20 * (ybot - ytop)
            p.setPen(QPen(QColor(WHITE), 2))
            p.drawLine(int(x), int(yz), int(x), int(y))
            p.setPen(QPen(QColor(GREY), 1))
            p.drawText(int(x - 22), ybot + 6, 44, 14, Qt.AlignmentFlag.AlignHCenter, EQ_BANDS[i])


class ColorSlider(QWidget):
    def __init__(self, on_change=None):
        super().__init__()
        self.hue = 0.0
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
        grad = QLinearGradient(0, 0, self.width(), 0)
        for i in range(7):
            grad.setColorAt(i / 6, QColor.fromHsvF(i / 6, 1, 1))
        p.fillRect(self.rect().adjusted(0, 3, 0, -3), grad)
        p.setPen(QPen(QColor(WHITE), 2))
        p.drawRect(QRectF(self.hue * self.width() - 3, 1, 6, self.height() - 2))


def curve_icon(values, w=56, h=16):
    pm = QPixmap(w, h)
    pm.fill(QColor(PANEL))
    p = QPainter(pm)
    p.setRenderHint(QPainter.RenderHint.Antialiasing)
    n = len(values)
    bw = (w - 8) / (n - 1)
    for i, v in enumerate(values):
        x = 4 + i * bw
        yz = h - 3
        y = h - 3 - (v + 10) / 20 * (h - 6)
        p.setPen(QPen(QColor(WHITE), 1.2))
        p.drawLine(int(x), int(yz), int(x), int(y))
    return QIcon(pm)


# ---------------- app ----------------

class QuantumUI(QWidget):
    def __init__(self, demo=False):
        super().__init__()
        self.setWindowTitle(APP_NAME)
        self.resize(980, 640)
        self.setStyleSheet(f"QWidget {{ background: {BG}; color: {WHITE}; font-size: 12px; }}")
        self.demo = demo
        self.demo_state = {
            "present": True, "product": "JBL Quantum 810 Wireless", "battery": 80,
            "dial": 11, "anc": "on", "sidetone": "low", "lights": True, "mic": False,
            "auto_off_min": 60, "serial": "DEMO0810WRLSS00",
            "firmware": "1.2.7 / 0.9.4 / 2.1.0 / 1.0.3",
        }
        self.eq_values = list(EQ_PRESETS["FLAT"])
        self.light_preset = "BREATH"
        self.zone_hue = {"LOGO": 0.95, "RING": 0.45}
        self.zone_speed = {"LOGO": 3, "RING": 3}
        self.sync_all = False
        self.profiles = self._load_profiles()
        self._build()
        self._nav(0)
        self._tick()
        QTimer(self, interval=2000, timeout=self._tick).start()

    # ---- small helpers ----
    @staticmethod
    def _cap(txt):
        l = QLabel(txt)
        l.setStyleSheet(f"color: {GREY}; font-size: 10px; letter-spacing: 1px;")
        return l

    def _combo(self):
        c = QComboBox()
        c.setFixedHeight(24)
        c.setStyleSheet(
            f"QComboBox {{ background: {BG}; border: 1px solid {WHITE}; color: {WHITE};"
            f" font-size: 10px; letter-spacing: 1px; padding-left: 8px; }}"
            f" QComboBox QAbstractItemView {{ background: {PANEL}; color: {WHITE};"
            f" selection-background-color: {RED}; border: 1px solid {WHITE}; }}")
        return c

    def _rail_qss(self, active):
        if active:
            return (f"QPushButton {{ background: {WHITE}; color: {BG}; border: 1px solid {WHITE};"
                    f" font-size: 10px; letter-spacing: 1px; text-align: left; padding-left: 10px; }}")
        return (f"QPushButton {{ background: {BG}; color: {WHITE}; border: 1px solid {WHITE};"
                f" font-size: 10px; letter-spacing: 1px; text-align: left; padding-left: 10px; }}"
                f" QPushButton:hover {{ background: {PANEL}; }}")

    # ---- chrome ----
    def _titlebar(self):
        bar = QWidget()
        lay = QHBoxLayout(bar)
        lay.setContentsMargins(10, 6, 10, 0)
        self.demo_pill = QPushButton("DEMO")
        self.demo_pill.setCheckable(True)
        self.demo_pill.setChecked(self.demo)
        self.demo_pill.setFixedSize(60, 20)
        self.demo_pill.setCursor(Qt.CursorShape.PointingHandCursor)
        self._style_demo_pill()
        self.demo_pill.toggled.connect(self._toggle_demo)
        lay.addWidget(self.demo_pill)
        lay.addWidget(self._cap("demo UI — no headset needed"))
        lay.addStretch(1)
        ver = QLabel(f"{APP_NAME}  v{APP_VERSION}")
        ver.setStyleSheet(f"color: {DARKGREY}; font-size: 10px;")
        lay.addWidget(ver)
        return bar

    def _style_demo_pill(self):
        on = self.demo_pill.isChecked()
        self.demo_pill.setStyleSheet(
            f"QPushButton {{ background: {'#e6b450' if on else 'transparent'};"
            f" color: {'#141416' if on else GREY}; border: 1px solid #e6b450;"
            f" border-radius: 2px; font-size: 10px; font-weight: bold; letter-spacing: 1px; }}")

    def _topbar(self):
        bar = QWidget()
        lay = QHBoxLayout(bar)
        lay.setContentsMargins(16, 4, 16, 2)
        lay.setSpacing(16)

        vwrap = QWidget(); vh = QHBoxLayout(vwrap); vh.setContentsMargins(0, 0, 0, 0); vh.setSpacing(6)
        vh.addWidget(self._cap("VOLUME"))
        self.volume = QSlider(Qt.Orientation.Horizontal)
        self.volume.setRange(0, 100); self.volume.setValue(100); self.volume.setFixedWidth(110)
        self.volume.setStyleSheet(
            "QSlider::groove:horizontal { height: 2px; background: #5a5a60; }"
            "QSlider::handle:horizontal { background: #f2f2f2; width: 8px; margin: -5px 0; }")
        self.volume.sliderReleased.connect(self._set_volume)
        vh.addWidget(self.volume)
        self.volume_lbl = self._cap("100%")
        vh.addWidget(self.volume_lbl)
        lay.addWidget(vwrap)

        self.mic_lbl = QLabel("MICROPHONE")
        self.mic_lbl.setStyleSheet(f"color: {RED}; font-size: 10px; letter-spacing: 1px;")
        self.mic_lbl.setCursor(Qt.CursorShape.PointingHandCursor)
        self.mic_lbl.mousePressEvent = self._mic_clicked
        lay.addWidget(self.mic_lbl)

        self.dial_dots = DialDots()
        self.dial_dots.setFixedWidth(230)
        lay.addWidget(self.dial_dots)

        swrap = QWidget(); sh = QHBoxLayout(swrap); sh.setContentsMargins(0, 0, 0, 0); sh.setSpacing(6)
        sh.addWidget(self._cap("SPATIAL SOUND"))
        self.spatial_toggle = Toggle(checked=False, on_change=self._spatial_toggled)
        sh.addWidget(self.spatial_toggle)
        lay.addWidget(swrap)

        awrap = QWidget(); ah = QHBoxLayout(awrap); ah.setContentsMargins(0, 0, 0, 0); ah.setSpacing(6)
        ah.addWidget(self._cap("ANC"))
        self.anc_lbl = QLabel("—")
        self.anc_lbl.setStyleSheet(f"color: {WHITE}; font-size: 10px; letter-spacing: 1px;")
        ah.addWidget(self.anc_lbl)
        lay.addWidget(awrap)

        bwrap = QWidget(); bh = QHBoxLayout(bwrap); bh.setContentsMargins(0, 0, 0, 0); bh.setSpacing(6)
        self.battery_icon = BatteryIcon()
        bh.addWidget(self.battery_icon)
        lay.addWidget(bwrap)

        self.conn_lbl = self._cap("CONNECTED TO: —")
        lay.addWidget(self.conn_lbl)
        lay.addStretch(1)
        return bar

    def _logo_row(self):
        row = QWidget()
        lay = QHBoxLayout(row)
        lay.setContentsMargins(16, 6, 16, 6)
        logo = QLabel()
        logo.setTextFormat(Qt.TextFormat.RichText)
        logo.setText(
            f"<span style='background-color:{RED};color:white;font-weight:bold;"
            f"font-size:20px;'>&nbsp;JBL&nbsp;</span>"
            f"<span style='color:white;font-weight:bold;font-size:20px;'> QUANTUM</span>"
            f"<span style='color:white;font-size:12px;'>810</span>"
            f"<span style='color:{GREY};font-size:9px;'> WIRELESS</span>")
        lay.addWidget(logo)
        lay.addStretch(1)
        self.demo_banner = QLabel("DEMO MODE — nothing is sent to hardware")
        self.demo_banner.setStyleSheet(
            "background: #e6b450; color: #141416; font-size: 10px; font-weight: bold;"
            " letter-spacing: 1px; padding: 3px 10px; border-radius: 2px;")
        lay.addWidget(self.demo_banner)
        lay.addStretch(1)
        hatch = HatchStrip(); hatch.setFixedSize(140, 22)
        lay.addWidget(hatch)
        self.profile = self._combo()
        self.profile.setFixedSize(170, 24)
        lay.addWidget(self.profile)
        pencil = QPushButton("✎")
        pencil.setFixedSize(24, 24)
        pencil.setCursor(Qt.CursorShape.PointingHandCursor)
        pencil.setStyleSheet(f"QPushButton {{ border: 1px solid {WHITE}; background: {BG};"
                             f" color: {WHITE}; }} QPushButton:hover {{ background: {WHITE}; color: {BG}; }}")
        pencil.clicked.connect(self._profile_dialog)
        lay.addWidget(pencil)
        trash = QPushButton("🗑")
        trash.setFixedSize(24, 24)
        trash.setCursor(Qt.CursorShape.PointingHandCursor)
        trash.setStyleSheet(pencil.styleSheet())
        trash.clicked.connect(self._profile_delete)
        lay.addWidget(trash)
        return row

    def _rail(self):
        rail = QWidget()
        lay = QVBoxLayout(rail)
        lay.setContentsMargins(16, 10, 0, 10)
        lay.setSpacing(8)
        self.rail_buttons = []
        names = RAIL + RAIL_EXTRA
        for i, name in enumerate(names):
            b = QPushButton(name)
            b.setCheckable(True)
            b.setFixedHeight(26)
            b.setCursor(Qt.CursorShape.PointingHandCursor)
            b.setStyleSheet(self._rail_qss(False))
            b.clicked.connect(lambda _=False, idx=i: self._nav(idx))
            lay.addWidget(b)
            self.rail_buttons.append(b)
        lay.addStretch(1)
        extra = QLabel("AUTO POWER OFF\nalso on the SYSTEM\nSOFTWARE page")
        extra.setStyleSheet(f"color: {DARKGREY}; font-size: 9px; letter-spacing: 1px;")
        lay.addWidget(extra)
        return rail

    def _nav(self, idx):
        for i, b in enumerate(self.rail_buttons):
            b.setChecked(i == idx)
            b.setStyleSheet(self._rail_qss(i == idx))
        self.stack.setCurrentIndex(idx)

    # ---- pages ----
    def _page_eq(self):
        pg = QWidget()
        grid = QGridLayout(pg)
        grid.setContentsMargins(18, 4, 18, 14)
        top = QWidget(); th = QHBoxLayout(top); th.setContentsMargins(0, 0, 0, 0); th.setSpacing(8)
        self.eq_combo = self._combo()
        for name, curve in EQ_PRESETS.items():
            self.eq_combo.addItem(curve_icon(curve), name)
        self.eq_combo.setCurrentText("FLAT")
        self.eq_combo.currentTextChanged.connect(self._eq_preset)
        th.addWidget(self.eq_combo, 3)
        self.eq_save = QLineEdit()
        self.eq_save.setPlaceholderText("SAVE CUSTOM PRESET — TYPE NAME + ✓")
        self.eq_save.setFixedHeight(24)
        self.eq_save.setStyleSheet(
            f"QLineEdit {{ background: {BG}; border: 1px solid {WHITE}; color: {WHITE};"
            f" font-size: 10px; letter-spacing: 1px; padding-left: 8px; }}")
        th.addWidget(self.eq_save, 2)
        ok = QPushButton("✓"); ok.setFixedSize(26, 24)
        ok.setStyleSheet(f"QPushButton {{ border: 1px solid {WHITE}; color: {WHITE}; background: {BG}; }}"
                         f"QPushButton:hover {{ background: {WHITE}; color: {BG}; }}")
        ok.clicked.connect(self._eq_save_custom)
        th.addWidget(ok)
        grid.addWidget(top, 0, 0, 1, 2)
        self.eq_bars = EqBars(self.eq_values)
        grid.addWidget(self.eq_bars, 1, 0)
        hv = HeadsetVisual()
        grid.addWidget(hv, 1, 1)
        note = QLabel("HOST-SIDE — the 810 dongle applies no EQ (proven by capture analysis); "
                      "Linux wiring via PipeWire pending. Preset names from the real app; curves "
                      "approximate (WARZONE = community-exact set). Drag the bars to edit.")
        note.setWordWrap(True)
        note.setStyleSheet(f"color: {DARKGREY}; font-size: 9px;")
        grid.addWidget(note, 2, 0, 1, 2)
        return pg

    def _page_lighting(self):
        pg = QWidget()
        v = QVBoxLayout(pg)
        v.setContentsMargins(18, 4, 18, 14)
        top = QWidget(); th = QHBoxLayout(top); th.setContentsMargins(0, 0, 0, 0); th.setSpacing(16)
        self.light_combo = self._combo()
        self.light_combo.addItems(LIGHT_PRESETS)
        self.light_combo.currentTextChanged.connect(self._light_preset)
        th.addWidget(self.light_combo, 1)
        th.addStretch(1)
        for label, cb in (("ADVANCED MODE", lambda on: self.flash(
                "advanced hue-wheel mode pending — basic colour/speed is device-verified")),
                ("SYNC ALL LIGHTS", self._sync_toggled)):
            wrap = QWidget(); wh = QHBoxLayout(wrap); wh.setContentsMargins(0, 0, 0, 0); wh.setSpacing(6)
            wh.addWidget(self._cap(label))
            wh.addWidget(Toggle(checked=False, on_change=cb))
            th.addWidget(wrap)
        v.addWidget(top)
        self.zone_rows = {}
        for zone in ("LOGO", "RING"):
            row = QWidget(); rh = QHBoxLayout(row); rh.setContentsMargins(0, 8, 0, 8); rh.setSpacing(8)
            zlbl = QLabel(zone)
            zlbl.setStyleSheet(f"color: {GREY}; font-size: 10px; letter-spacing: 1px;")
            zlbl.setFixedWidth(40)
            rh.addWidget(zlbl)
            col = ColorSlider(on_change=lambda h_, z=zone: self._zone_colour(z, h_))
            col.set_hue = lambda h_, c=col: c.set_hue(h_)
            col.hue = self.zone_hue[zone]
            rh.addWidget(col, 2)
            rh.addWidget(self._cap("SPEED"))
            sp = QSlider(Qt.Orientation.Horizontal); sp.setRange(1, 7)
            sp.setValue(self.zone_speed[zone]); sp.setFixedWidth(80)
            sp.setStyleSheet(
                "QSlider::groove:horizontal { height: 2px; background: #5a5a60; }"
                "QSlider::handle:horizontal { background: #f2f2f2; width: 8px; margin: -5px 0; }")
            sp.valueChanged.connect(lambda val, z=zone: self._zone_speed(z, val))
            rh.addWidget(sp)
            rh.addWidget(self._cap("TEMPO"))
            tempo = QSpinBox(); tempo.setRange(1, 10); tempo.setValue(5); tempo.setFixedWidth(46)
            tempo.setStyleSheet(
                f"QSpinBox {{ background: {BG}; border: 1px solid {WHITE}; color: {WHITE}; }}")
            rh.addWidget(tempo)
            self.zone_rows[zone] = row
            v.addWidget(row)
        note = QLabel("Zones: JBL logo + ear-cup ring (L/R mirrored in hardware). Colour + speed "
                      "are device-verified (0x4C/0x4D); segment count safety-clamped 1–5 — "
                      "higher wedges the lighting MCU. Presets map to the 7 verified effects.")
        note.setWordWrap(True)
        note.setStyleSheet(f"color: {DARKGREY}; font-size: 9px;")
        v.addWidget(note)
        v.addStretch(1)
        return pg

    def _page_spatial(self):
        pg = QWidget()
        h = QHBoxLayout(pg); h.setContentsMargins(18, 4, 18, 14)
        left = QWidget(); lv = QVBoxLayout(left); lv.setContentsMargins(0, 0, 0, 0)
        self.spatial_combo = self._combo()
        self.spatial_combo.addItems(["JBL QuantumSURROUND", "DTS", "OFF"])
        self.spatial_combo.currentIndexChanged.connect(self._spatial_mode)
        lv.addWidget(self.spatial_combo)
        lv.addStretch(1)
        h.addWidget(left, 1)
        dts = QLabel()
        dts.setTextFormat(Qt.TextFormat.RichText)
        dts.setText(
            f"<div style='background-color:#000;border:2px solid {WHITE};padding:14px 22px;'>"
            f"<span style='color:white;font-weight:bold;font-size:22px;'>dts</span><br>"
            f"<span style='color:white;font-size:12px;letter-spacing:2px;'>HEADPHONE:X</span><br>"
            f"<span style='color:{GREY};font-size:9px;'>v2.0</span></div>")
        dts.setAlignment(Qt.AlignmentFlag.AlignCenter)
        h.addWidget(dts, 1)
        note = QLabel("HOST-SIDE — our capture analysis proves the real app never sends spatial "
                      "mode to the dongle; it is Windows spatial sound + host DSP. Linux "
                      "equivalent: PipeWire filter-chain (pending).")
        note.setWordWrap(True)
        note.setStyleSheet(f"color: {DARKGREY}; font-size: 9px;")
        h.addWidget(note, 1)
        return pg

    def _page_mic(self):
        pg = QWidget()
        v = QVBoxLayout(pg); v.setContentsMargins(18, 4, 18, 14)
        row = QWidget(); rh = QHBoxLayout(row); rh.setContentsMargins(0, 0, 0, 0); rh.setSpacing(10)
        mic_lbl = QLabel("MIC")
        mic_lbl.setStyleSheet("font-size: 16px; font-weight: bold; letter-spacing: 1px;")
        rh.addWidget(mic_lbl)
        self.mic_state = QLabel("—")
        self.mic_state.setStyleSheet(f"color: {RED}; font-size: 16px; font-weight: bold;")
        rh.addWidget(self.mic_state)
        rh.addStretch(1)
        v.addWidget(row)
        hint = QLabel("LOWER THE BOOM MIC TO ENABLE MIC AND PRESS THE MUTE BUTTON ON THE HEADSET")
        hint.setStyleSheet(f"color: {GREY}; font-size: 10px; letter-spacing: 1px;")
        v.addWidget(hint)
        v.addSpacing(14)
        sv = QVBoxLayout()
        sv.addWidget(self._cap("SIDETONE (AUDIO/VOICE MONITOR) — DEVICE-VERIFIED (0x5D)"))
        srow = QWidget(); sh = QHBoxLayout(srow); sh.setContentsMargins(0, 0, 0, 0); sh.setSpacing(14)
        self.sidetone_group = QButtonGroup(self)
        for i, v_ in enumerate(("OFF", "LOW", "MID", "HIGH")):
            rb = QRadioButton(v_)
            rb.setStyleSheet(f"QRadioButton {{ color: {WHITE}; font-size: 10px; letter-spacing: 1px; }}")
            rb.clicked.connect(lambda _=False, val=v_.lower(): self.set_dev("sidetone", val))
            self.sidetone_group.addButton(rb, i)
            sh.addWidget(rb)
        sh.addStretch(1)
        sv.addWidget(srow)
        v.addLayout(sv)
        v.addStretch(1)
        return pg

    def _page_system(self):
        pg = QWidget()
        v = QVBoxLayout(pg); v.setContentsMargins(18, 4, 18, 14)
        head = QLabel("SYSTEM SOFTWARE")
        head.setStyleSheet("font-size: 14px; font-weight: bold; letter-spacing: 1px;")
        v.addWidget(head)
        self.sys_info = QLabel("—")
        v.addWidget(self.sys_info)
        upd = QPushButton("CHECK FOR UPDATES")
        upd.setFixedSize(180, 26)
        upd.setCursor(Qt.CursorShape.PointingHandCursor)
        upd.setStyleSheet(f"QPushButton {{ border: 1px solid {WHITE}; color: {WHITE}; background: {BG};"
                          f" font-size: 10px; letter-spacing: 1px; }}"
                          f"QPushButton:hover {{ background: {WHITE}; color: {BG}; }}")
        upd.clicked.connect(lambda: self.flash(
            "firmware updates are deliberately disabled — no firmware flows in this tool", RED))
        v.addWidget(upd, 0, Qt.AlignmentFlag.AlignLeft)
        v.addSpacing(14)
        v.addWidget(self._cap("AUTO POWER OFF — DEVICE-VERIFIED (0x75, 5-MIN UNITS, VERIFY BY READ-BACK)"))
        arow = QWidget(); ah = QHBoxLayout(arow); ah.setContentsMargins(0, 0, 0, 0); ah.setSpacing(14)
        self.autoff_group = QButtonGroup(self)
        for i, mins in enumerate(("NEVER", "30 MIN", "60 MIN", "120 MIN")):
            rb = QRadioButton(mins)
            rb.setStyleSheet(f"QRadioButton {{ color: {WHITE}; font-size: 10px; letter-spacing: 1px; }}")
            rb.clicked.connect(lambda _=False, m=mins: self.set_dev(
                "auto_off", 0 if m == "NEVER" else int(m.split()[0])))
            self.autoff_group.addButton(rb, i)
            ah.addWidget(rb)
        ah.addStretch(1)
        v.addWidget(arow)
        v.addSpacing(14)
        rs = QPushButton("RESTORE FACTORY SETTINGS (undo our writes)")
        rs.setFixedSize(280, 26)
        rs.setCursor(Qt.CursorShape.PointingHandCursor)
        rs.setStyleSheet(upd.styleSheet())
        rs.clicked.connect(self._restore)
        v.addWidget(rs, 0, Qt.AlignmentFlag.AlignLeft)
        v.addStretch(1)
        return pg

    def _page_help(self):
        pg = QWidget()
        v = QVBoxLayout(pg); v.setContentsMargins(18, 4, 18, 14)
        body = QLabel(
            f"{APP_NAME} v{APP_VERSION}\n\n"
            "A Linux replica of JBL QuantumENGINE for Quantum wireless headsets\n"
            "(verified on Quantum 810 Wireless, 0ecb:2069).\n\n"
            "• Protocol documentation + evidence: research/jbl-quantum/PROTOCOL.md\n"
            "• Only device-verified feature reports are used; firmware/DFU reports are\n"
            "  structurally unreachable (no firmware flows, by design)\n"
            "• Protocol source: community-verified (sidmax7/QuantumEngine, taron-sys tray tool)\n"
            "  and independently confirmed by parsing public USB captures (HeadsetControl #357)\n"
            "• EQ / spatial sound are host-side even in the real app — PipeWire wiring pending\n\n"
            "github.com/umarabdullah23/jbl-quantum-engine-linux")
        body.setWordWrap(True)
        body.setStyleSheet(f"color: {GREY}; font-size: 11px;")
        v.addWidget(body)
        v.addStretch(1)
        return pg

    def _page_anc(self):
        pg = QWidget()
        v = QVBoxLayout(pg); v.setContentsMargins(18, 4, 18, 14)
        v.addWidget(self._cap("NOISE CANCELLING / AMBIENT AWARE — DEVICE-VERIFIED (0x46)"))
        row = QWidget(); rh = QHBoxLayout(row); rh.setContentsMargins(0, 8, 0, 0); rh.setSpacing(14)
        self.anc_group = QButtonGroup(self)
        for i, (val, lbl) in enumerate((("off", "OFF"), ("on", "ANC"), ("talkthru", "AMBIENT AWARE"))):
            rb = QRadioButton(lbl)
            rb.setStyleSheet(f"QRadioButton {{ color: {WHITE}; font-size: 10px; letter-spacing: 1px; }}")
            rb.clicked.connect(lambda _=False, v_=val: self.set_dev("anc", v_))
            self.anc_group.addButton(rb, i)
            rh.addWidget(rb)
        rh.addStretch(1)
        v.addWidget(row)
        note = QLabel("The 810 also cycles this with its physical button; QE 2.x does not expose "
                      "it — this page is a verified addition.")
        note.setWordWrap(True)
        note.setStyleSheet(f"color: {DARKGREY}; font-size: 9px;")
        v.addWidget(note)
        v.addStretch(1)
        return pg

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
        return {
            "eq": list(self.eq_values),
            "eq_preset": self.eq_combo.currentText(),
            "light_preset": self.light_combo.currentText(),
            "hue": dict(self.zone_hue),
            "speed": dict(self.zone_speed),
            "spatial": self.spatial_combo.currentIndex(),
        }

    def _apply_profile(self, data):
        self.eq_values[:] = data.get("eq", [0] * 10)
        self.eq_bars.values = self.eq_values
        self.eq_bars.update()
        self.eq_combo.setCurrentText(data.get("eq_preset", "FLAT"))
        self.light_combo.setCurrentText(data.get("light_preset", "BREATH"))
        for z in ("LOGO", "RING"):
            self.zone_hue[z] = data.get("hue", {}).get(z, 0.95 if z == "LOGO" else 0.45)
            self.zone_speed[z] = data.get("speed", {}).get(z, 3)
            row = self.zone_rows[z]
            slider = row.findChild(ColorSlider)
            slider.set_hue(self.zone_hue[z])
        self.spatial_combo.setCurrentIndex(data.get("spatial", 0))

    def _profile_dialog(self):
        names = list(self.profiles.keys())
        name, ok = QInputDialog.getItem(
            self, "User profiles", "Load / overwrite profile:", ["+ NEW PROFILE…"] + names, 0, False)
        if not ok:
            return
        if name == "+ NEW PROFILE…":
            name, ok = QInputDialog.getText(self, "New profile", "Profile name:")
            name = name.strip().upper()
            if not ok or not name:
                return
        self.profiles[name] = self._current_profile()
        self._save_profiles()
        self._reload_profile_combo(select=name)
        self.flash(f"profile '{name}' saved (EQ + lighting + spatial)")

    def _profile_delete(self):
        names = list(self.profiles.keys())
        if not names:
            self.flash("no profiles saved yet")
            return
        name, ok = QInputDialog.getItem(self, "Delete profile", "Profile:", names, 0, False)
        if ok and name in self.profiles:
            del self.profiles[name]
            self._save_profiles()
            self._reload_profile_combo()
            self.flash(f"profile '{name}' deleted")

    def _reload_profile_combo(self, select=None):
        self.profile.blockSignals(True)
        self.profile.clear()
        self.profile.addItem("USER PROFILE")
        for n in self.profiles:
            self.profile.addItem(n)
        if select:
            self.profile.setCurrentText(select)
        self.profile.blockSignals(False)

    # ---- actions ----
    def _toggle_demo(self, on):
        self.demo = on
        self._style_demo_pill()
        self.demo_banner.setVisible(on)
        self._tick()

    def _eq_preset(self, name):
        if name in EQ_PRESETS:
            self.eq_values[:] = EQ_PRESETS[name]
            self.eq_bars.values = self.eq_values
            self.eq_bars.update()
        self.flash(f"EQ preset {name} — host-side (PipeWire pending)")

    def _eq_save_custom(self):
        name = self.eq_save.text().strip().upper()
        if name:
            EQ_PRESETS[name] = list(self.eq_values)
            if not [self.eq_combo.itemText(i) for i in range(self.eq_combo.count())].count(name):
                self.eq_combo.addItem(curve_icon(self.eq_values), name)
            self.eq_combo.setCurrentText(name)
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
                "rgb": self._hue_rgb(self.zone_hue[zone]), "mode": mode, "last": 0})

    def _sync_toggled(self, on):
        self.sync_all = on

    def _zone_colour(self, zone, hue):
        self.zone_hue[zone] = hue
        payload = {"element": 0 if zone == "LOGO" else 1, "slot": 0,
                   "rgb": self._hue_rgb(hue),
                   "mode": max(0, LIGHT_PRESETS.index(self.light_combo.currentText())),
                   "last": 0}
        self.set_dev("light_colour", payload)
        if self.sync_all:
            other = "RING" if zone == "LOGO" else "LOGO"
            self.zone_hue[other] = hue
            self.zone_rows[other].findChild(ColorSlider).set_hue(hue)
            self.set_dev("light_colour", {**payload, "element": 0 if other == "LOGO" else 1})

    def _zone_speed(self, zone, val):
        self.zone_speed[zone] = val
        self.set_dev("light_zone", {
            "element": 0 if zone == "LOGO" else 1,
            "speed": SPEED_BYTES[max(0, min(6, val - 1))], "segments": 5})

    @staticmethod
    def _hue_rgb(h):
        c = QColor.fromHsvF(max(0.0, min(1.0, h)), 1, 1)
        return [c.red(), c.green(), c.blue()]

    def _spatial_toggled(self, on):
        self.spatial_combo.setCurrentIndex(0 if on else 2)

    def _spatial_mode(self, idx):
        self.spatial_toggle.checked = (idx != 2)
        self.spatial_toggle.update()
        self.flash("spatial sound — host-side (PipeWire pending); the real app never sends it to the dongle")

    def _mic_clicked(self, _):
        if self.demo:
            self.demo_state["mic"] = not self.demo_state["mic"]
            self.flash(f"mic {'on' if self.demo_state['mic'] else 'off'} (demo — mute is hardware-side)")
        else:
            self.flash("mic mute is hardware-side on the 810 (boom arm + mute button); state shown live")

    def _set_volume(self):
        v = self.volume.value()
        self.volume_lbl.setText(f"{v}%")
        if self.demo:
            self.flash(f"volume {v}% (demo — nothing sent)")
            return
        import subprocess
        try:
            subprocess.run(["pactl", "set-sink-volume", "@DEFAULT_SINK@", f"{v}%"],
                           timeout=3, check=False)
            self.flash(f"system volume → {v}%")
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
        self.status.setStyleSheet(f"color: {color or GREY}; font-size: 10px;")

    # ---- state loop ----
    def _tick(self):
        st = daemon_request({"cmd": "state"})
        live = bool(st.get("present"))
        if self.demo and not live:
            st = dict(self.demo_state)
        elif not live:
            self.battery_icon.percent = None
            self.battery_icon.update()
            self.conn_lbl.setText("CONNECTED TO: — (plug in the dongle)")
            self.dial_dots.value = 0
            self.dial_dots.update()
            self.anc_lbl.setText("—")
            self.mic_state.setText("—")
            self.sys_info.setText("No headset detected.\n"
                                  "Plug in the Quantum 810 wireless dongle — it connects automatically.")
            self.demo_banner.setVisible(self.demo)
            return
        self.demo_banner.setVisible(False)
        self.battery_icon.percent = st.get("battery")
        self.battery_icon.update()
        self.conn_lbl.setText(f"CONNECTED TO: {str(st.get('product', '—')).upper()}")
        self.dial_dots.value = st.get("dial") or 0
        self.dial_dots.update()
        anc = st.get("anc")
        self.anc_lbl.setText({"off": "OFF", "on": "ANC", "talkthru": "AA"}.get(anc, "—"))
        mic = st.get("mic")
        self.mic_state.setText(("ON" if mic else "OFF") if mic is not None else "—")
        sid = st.get("sidetone")
        if sid in ("off", "low", "mid", "high"):
            idx = ("off", "low", "mid", "high").index(sid)
            btns = self.sidetone_group.buttons()
            if idx < len(btns):
                btns[idx].setChecked(True)
        anc2 = st.get("anc")
        if anc2 in ("off", "on", "talkthru"):
            btns = self.anc_group.buttons()
            idx = ("off", "on", "talkthru").index(anc2)
            if idx < len(btns):
                btns[idx].setChecked(True)
        aom = st.get("auto_off_min")
        if aom is not None:
            btns = self.autoff_group.buttons()
            which = {0: 0, 30: 1, 60: 2, 120: 3}.get(aom)
            if which is not None and which < len(btns):
                btns[which].setChecked(True)
        self.sys_info.setText(
            f"product   : {st.get('product', '—')}\n"
            f"battery   : {st.get('battery', '—')}%\n"
            f"serial    : {st.get('serial', '—')}\n"
            f"firmware  : {st.get('firmware', '—')}\n"
            f"link      : connected via wireless dongle\n"
            f"dial      : {st.get('dial', '—')}/16")

    # ---- assembly ----
    def _build(self):
        root = QVBoxLayout(self)
        root.setContentsMargins(0, 0, 0, 0)
        root.setSpacing(0)
        root.addWidget(self._titlebar())
        root.addWidget(self._topbar())
        root.addWidget(self._logo_row())
        line = QFrame(); line.setFixedHeight(1)
        line.setStyleSheet(f"background: {HAIR};")
        root.addWidget(line)
        mid = QWidget(); mh = QHBoxLayout(mid); mh.setContentsMargins(0, 0, 0, 0)
        mh.addWidget(self._rail())
        self.stack = QStackedWidget()
        for pg in (self._page_eq(), self._page_lighting(), self._page_spatial(),
                   self._page_mic(), self._page_system(), self._page_help(),
                   self._page_anc()):
            self.stack.addWidget(pg)
        mh.addWidget(self.stack, 1)
        root.addWidget(mid, 1)
        self.status = QLabel("")
        self.status.setContentsMargins(16, 2, 16, 6)
        root.addWidget(self.status)
        self._reload_profile_combo()


def main():
    app = QApplication(sys.argv)
    w = QuantumUI(demo="--demo" in sys.argv)
    w.show()
    sys.exit(app.exec())


if __name__ == "__main__":
    main()
