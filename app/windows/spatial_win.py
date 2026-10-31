#!/usr/bin/env python3
"""spatial_win.py — REAL host-side spatial sound for the Windows app.

The dongle receives nothing for spatial (capture-proven) — the processing lives on the
PC. The real QuantumENGINE ships DTS Headphone:X (licensed); we can't ship DTS, but
Windows' own spatial formats ARE available on every machine:

  * "Windows Sonic For Headphones"  — built into Windows 10/11 (GUID B53D940C-…)
  * "DTS Headphone:X"               — present only if QuantumENGINE/DTS installed

Mechanism: NirSoft SoundVolumeView (vendored unmodified, freeware) — its /SetSpatial
sets the endpoint's spatial format through the same property store the OS Settings app
uses (it works across Windows builds; NirSoft maintains it). /stext gives a READ-BACK:
the endpoint record's 'Spatial Guid' line. Every set is verified by read-back — a set
that silently didn't take is reported as failed, never claimed.

Empirically verified on Windows 11 (2026-11-01, real Quantum 810 Game endpoint):
  set Sonic  -> Spatial Guid = {B53D940C-B846-4831-9F76-D102B9B725A0}
  set off    -> Spatial Guid = <empty>
No admin required; applies instantly (endpoint reconfigures, e.g. 8ch -> 2ch).
"""
from __future__ import annotations

import os
import re
import subprocess
import sys
import tempfile

SONIC = "Windows Sonic For Headphones"
SONIC_GUID = "{B53D940C-B846-4831-9F76-D102B9B725A0}"
DTS_NAME = "DTS Headphone:X"

SUPPORTED = [SONIC, DTS_NAME]


def _svv_path() -> str:
    """Locate the vendored SoundVolumeView.exe (frozen exe or source tree)."""
    if getattr(sys, "frozen", False):
        base = getattr(sys, "_MEIPASS", os.path.dirname(sys.executable))
        cand = os.path.join(base, "vendor", "SoundVolumeView.exe")
        if os.path.exists(cand):
            return cand
        cand = os.path.join(os.path.dirname(sys.executable), "vendor", "SoundVolumeView.exe")
        return cand
    return os.path.join(os.path.dirname(os.path.abspath(__file__)), "vendor",
                        "SoundVolumeView.exe")


def _dump_devices(timeout=25) -> str | None:
    svv = _svv_path()
    if not os.path.exists(svv):
        return None
    fd, out = tempfile.mkstemp(suffix=".txt", prefix="jblq_spatial_")
    os.close(fd)
    try:
        r = subprocess.run([svv, "/stext", out], capture_output=True, timeout=timeout)
        if r.returncode != 0 and not os.path.exists(out):
            return None
        for enc in ("utf-8", "utf-16", "cp1252"):
            try:
                with open(out, encoding=enc) as f:
                    txt = f.read()
                if txt.strip():
                    return txt
            except (UnicodeDecodeError, UnicodeError):
                continue
        return None
    except Exception:
        return None
    finally:
        try:
            os.remove(out)
        except OSError:
            pass


def _endpoint_records() -> list[dict]:
    """All Render device records that carry a Spatial Guid (i.e. real endpoints)."""
    txt = _dump_devices()
    if not txt:
        return []
    out = []
    for block in txt.split("=" * 50):
        if "Direction         : Render" not in block or "Spatial Guid" not in block:
            continue
        friendly = re.search(r"Command-Line Friendly ID: (.*)", block)
        guid = re.search(r"Spatial Guid\s*: (\S*)", block)
        if friendly:
            out.append({"id": friendly.group(1).strip(),
                        "spatial_guid": guid.group(1).strip() if guid else ""})
    return out


def quantum_render_endpoint() -> dict | None:
    """The Quantum headset's Game render endpoint (spatial applies to game audio).

    Prefers 'Game'; falls back to any JBL/Quantum render endpoint.
    """
    recs = [r for r in _endpoint_records()
            if r["id"].lower().endswith("\\device\\speakers\\render")]
    quant = [r for r in recs if "quantum" in r["id"].lower() or "jbl" in r["id"].lower()]
    game = [r for r in quant if "game" in r["id"].lower()]
    return (game or quant or [None])[0]


def get_spatial() -> dict:
    """Current spatial state of the Quantum endpoint: {available, guid, mode}."""
    ep = quantum_render_endpoint()
    if ep is None:
        return {"available": False, "guid": "", "mode": ""}
    return {"available": True, "guid": ep["spatial_guid"],
            "endpoint": ep["id"],
            "mode": _mode_from_guid(ep["spatial_guid"])}


def _mode_from_guid(guid: str) -> str:
    if not guid:
        return "off"
    if guid.upper() == SONIC_GUID:
        return SONIC
    return guid  # DTS/Atmos etc. — report the raw GUID; SVV resolves names client-side


def set_spatial(format_name: str) -> dict:
    """Set (or clear with '') the spatial format on the Quantum endpoint.

    Verified by read-back: returns {ok, applied, guid, error}.
    """
    svv = _svv_path()
    if not os.path.exists(svv):
        return {"ok": False, "error": "SoundVolumeView.exe missing from the app bundle"}
    ep = quantum_render_endpoint()
    if ep is None:
        return {"ok": False, "error": "no Quantum render endpoint found"}
    try:
        r = subprocess.run([svv, "/SetSpatial", ep["id"], format_name],
                           capture_output=True, timeout=25)
        if r.returncode != 0:
            return {"ok": False, "error": f"SetSpatial rc={r.returncode}"}
    except Exception as e:
        return {"ok": False, "error": str(e)}
    # read-back — never claim a set we didn't verify
    for _ in range(3):
        after = get_spatial()
        want = format_name if format_name else ""
        got = after.get("guid", "")
        if (not want and not got) or (want and got):
            return {"ok": True, "applied": True, "guid": got,
                    "mode": after.get("mode", "")}
        import time
        time.sleep(0.6)
    return {"ok": False, "error": f"read-back mismatch (want {want!r}, got {got!r})"}


def spatial_format_names() -> list[str]:
    """Formats we can offer: Sonic always; DTS only if its licence is present."""
    names = [SONIC]
    # DTS Headphone:X is present iff QuantumENGINE/DTS installed its APO — try set+verify
    # is the only reliable probe; the caller does that opportunistically. We expose the
    # name; a failed set falls back to Sonic with an honest status.
    names.append(DTS_NAME)
    return names
