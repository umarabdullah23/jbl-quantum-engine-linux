# JBL Quantum Engine — Windows edition

Native Windows port of the Linux app (repo root `app/`), rebuilt to match the **real
QuantumENGINE Windows UI** (reference screenshots: `E:\quantum engine pics`). Same shared
engine: imports `app/jbl_quantum.py` — one protocol implementation for both OSes.

## Run from source

```powershell
pip install -r app/windows/requirements.txt
python app/windows/jblq_win.py            # live (dongle plugged in)
python app/windows/jblq_win.py --demo     # demo mode — never sends anything
```

## Build the exe

```powershell
powershell -ExecutionPolicy Bypass -File app/windows/build_exe.ps1
# -> app/windows/dist/JBLQuantumEngine.exe  (one-file, ~49 MB)
```

The script: installs deps if missing → generates `jblq_icon.ico` (drawn open-Q mark, no
JBL artwork) → compile-checks → PyInstaller (`jblq_win.spec`; `jbl_quantum` is a named
hiddenimport so a collect miss can't drop the shared engine).

## What's verified vs host-side (honesty rules, unchanged from the Linux app)

- **Sent to the device (verified reports 0x45–0x75, live-verified 2026-11-01):** ANC
  (0x46), side tone 4-step (0x5D), lights master (0x4B), light zones/brightness
  (0x4C, brightness 40–100% steps, segments hard-clamped 1–5), light colour frames
  (0x4D, mode 0–6, tail byte 0–8), auto power-off (0x75, read-back verified).
- **Read-only:** battery (0x49 — no charging flag; charging is inferred from battery
  trend and shown as `⚡ charging*`), game/chat dial (0x62), mic active (0x67),
  serial (0x61), firmware (0x51).
- **Host-side, saved locally, never faked as device writes:** EQ presets/curve, spatial
  mode (Quantum Spatial / DTS) + room size + head diameter, mic gain + voice preset
  (RACE-level, fail-closed until a live capture — see `docs/PROTOCOL-RACE.md` §5).
- Firmware/DFU report IDs are deliberately unreachable. Restore button rolls back every
  write this app made (first-write-wins undo registry in the shared engine).

## Notes

- Close JBL QuantumENGINE while using this app — both can open the HID handle (Windows
  shared access), but two writers can race.
- The dongle re-enumerates when the headset sleeps/wakes; the worker re-detects on the
  next 2-second tick.
- All HID I/O runs on a worker thread (`DeviceWorker`) — a wedged feature-report can
  never freeze the UI (the Linux daemon needed a rewrite for exactly this bug class).
- Profiles: `%LOCALAPPDATA%\jblq\profiles.json`; tour flag: HKCU\Software\jblq.
