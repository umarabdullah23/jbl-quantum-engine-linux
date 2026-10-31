"""spatial_linux.py — Linux counterpart of windows/spatial_win.py.

Real spatial sound on Linux = PipeWire filter-chain attached to the EXISTING default
sink WITHOUT changing its format or device (reformatting the sink makes emulators
treat the headset as disconnected — rule learned live on Windows, see
docs/PROTOCOL-QEIPC.md). Until that is implemented, this reports unavailable
honestly: the UI stays in working local state and never fakes a device change.
"""

SONIC = "PipeWire Virtual Surround"
DTS_NAME = "DTS Headphone:X (PipeWire)"


def get_spatial() -> dict:
    return {"available": False, "guid": "", "mode": "off", "endpoint": "",
            "error": "PipeWire filter-chain not wired yet (host-side pending)"}


def set_spatial(format_name: str) -> dict:
    if not format_name:
        return {"ok": True, "mode": "off", "note": "off is free — nothing to apply"}
    return {"ok": False, "available": False,
            "error": "spatial sound on Linux needs the PipeWire filter-chain "
                     "(host-side pending) — the dongle receives nothing for it "
                     "(capture-proven), and Windows Sonic/DTS are Windows-only"}
