#!/usr/bin/env python3
"""Generate app/windows/jblq_icon.ico — drawn open-Q mark (no trademarked artwork).

Renders each size with Qt, assembles a REAL multi-resolution .ico with Pillow
(QPixmap.save('*.ico') writes a single-size file PyInstaller/Pillow can't parse).
"""
import io
import os

from PyQt6.QtCore import QPointF, QRectF, Qt
from PyQt6.QtGui import QColor, QPainter, QPen, QPixmap, QBrush

OUT = os.path.join(os.path.dirname(os.path.abspath(__file__)), "jblq_icon.ico")
SIZES = (16, 24, 32, 48, 64, 128, 256)


def render(size: int) -> QPixmap:
    pm = QPixmap(size, size)
    pm.fill(Qt.GlobalColor.transparent)
    p = QPainter(pm)
    p.setRenderHint(QPainter.RenderHint.Antialiasing)
    s = size / 256
    p.setBrush(QColor("#17111f"))
    p.setPen(Qt.PenStyle.NoPen)
    p.drawRoundedRect(QRectF(4 * s, 4 * s, 248 * s, 248 * s), 56 * s, 56 * s)
    p.setBrush(QBrush(QColor("#f2f2f4")))
    p.drawEllipse(QPointF(128 * s, 122 * s), 62 * s, 56 * s)
    p.setBrush(QColor("#17111f"))
    p.drawEllipse(QPointF(128 * s, 122 * s), 30 * s, 27 * s)
    p.setBrush(QColor("#f2f2f4"))
    p.drawEllipse(QPointF(164 * s, 168 * s), 17 * s, 17 * s)
    p.setPen(QPen(QColor("#8f6bff"), 6 * s))
    p.setBrush(Qt.BrushStyle.NoBrush)
    p.drawRoundedRect(QRectF(14 * s, 14 * s, 228 * s, 228 * s), 50 * s, 50 * s)
    p.end()
    return pm


def main():
    from PyQt6.QtWidgets import QApplication
    from PIL import Image
    import sys
    app = QApplication(sys.argv)
    imgs = []
    import tempfile
    with tempfile.TemporaryDirectory() as td:
        for sz in SIZES:
            png_path = os.path.join(td, f"icon_{sz}.png")
            render(sz).save(png_path, "PNG")
            imgs.append(Image.open(png_path).convert("RGBA"))
        # PIL's ICO writer derives sizes only by downscaling the base image and is
        # unreliable here — write the ICO container manually (PNG entries, Vista+).
        import struct
        pngs = []
        for img, sz in zip(imgs, SIZES):
            buf = io.BytesIO()
            img.save(buf, "PNG")
            pngs.append((sz, buf.getvalue()))
        out = io.BytesIO()
        out.write(struct.pack("<HHH", 0, 1, len(pngs)))  # reserved, type=icon, count
        offset = 6 + 16 * len(pngs)
        for sz, data in pngs:
            b = 0 if sz >= 256 else sz
            out.write(struct.pack("<BBBBHHII", b, b, 0, 0, 1, 32, len(data), offset))
            offset += len(data)
        for _, data in pngs:
            out.write(data)
        with open(OUT, "wb") as f:
            f.write(out.getvalue())
    print("icon written:", OUT, os.path.getsize(OUT), "bytes")


if __name__ == "__main__":
    main()
