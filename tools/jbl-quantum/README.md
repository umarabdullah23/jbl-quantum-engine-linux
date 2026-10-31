# jbl-quantum (Linux)

Native Linux control for **JBL Quantum wireless headsets** — Python + hidapi/hidraw only.
No Wine, no VM, no JBL binaries. Protocol documentation + evidence:
[`research/jbl-quantum/PROTOCOL.md`](../../research/jbl-quantum/PROTOCOL.md).

Primary target: **JBL Quantum 810 Wireless** (`0ecb:2069`, the USB-C dongle) — verified
against this user's hardware. ~30 sibling Quantum PIDs (800/850/910/910X/910P/950/950X/ONE/
610/600/400/360) are recognized from JBL's own INF device table and share the report map,
but only the 810 is hardware-verified here — reads are safe, writes use the same verified
report ids (gated; probe first on any other model).

## Features vs QuantumENGINE (Windows)

| Feature | QuantumENGINE | jbl-quantum | Notes |
|---|---|---|---|
| Sidetone (mic monitoring) | ✅ 4-step | ✅ `jblq sidetone off\|low\|mid\|high` | 4-step enum on the device, not a slider |
| ANC / noise cancelling | ✅ | ✅ `jblq anc off\|on\|talkthru` | TalkThru = ambient aware |
| Game/chat dial | ✅ | ✅ read `jblq dial` + live events | value 0–16 |
| Battery | ✅ | ✅ `jblq battery` + live events | charging state NOT exposed by dongle |
| Lighting (on/off, RGB zones/effects) | ✅ | ✅ library API (`set_light_zone`, `set_light_colour`) + master switch | **segments hard-clamped 1–5** (≥6 wedges the lighting MCU) |
| Auto power-off timer | ✅ | ✅ `jblq autooff 0\|30\|60\|120` | 5-min steps; verify-by-readback |
| Mic status / mute | ✅ | ✅ events + `0x67` read | `0x2f` mute bracket handled in event stream |
| Serial / firmware / paired host | ✅ | ✅ `jblq info` | |
| EQ (custom 10-band, parametric) | ✅ | **host-side via PipeWire** (planned hook, see below) | the 810 has **no on-device EQ** over the dongle — QuantumENGINE does host DSP too (proven: zero HID writes in spatial/EQ captures) |
| QuantumSURROUND / spatial | ✅ | **host-side via PipeWire virtual surround** (planned) | same proof as EQ |
| Volume wheel | ✅ (device knob) | use system mixer | dongle doesn't control host volume |
| Bluetooth mode (Airoha GATT) | ✅ | ❌ out of scope v1 | separate RACE-over-BLE protocol |

## Install

```bash
sudo apt install python3-hidapi          # or: pip install hid  (hidapi bindings)
sudo cp udev/99-jbl-quantum.rules /etc/udev/rules.d/
sudo udevadm control --reload && sudo udevadm trigger
```

## CLI

```bash
./jblq probe                    # READ-ONLY full state dump (safe first step)
./jblq battery
./jblq dial
./jblq info
./jblq sidetone high
./jblq anc on | off | talkthru
./jblq lights on | off
./jblq autooff 60               # minutes (0 = never)
./jblq listen                   # live dial/battery/mic/ANC events
./jblq restore                  # restore values captured before writes (undo)
```

Every setter snapshots the original value first (in-process and in `/tmp/jblq-undo.json`);
`restore` puts them back. Absent/unsupported devices are refused explicitly — the tool
never sends speculative reports, and the firmware/DFU report IDs are deliberately absent
from the code.

## Daemon

```bash
./jblq_daemon.py &
echo '{"cmd":"state"}'   | socat - UNIX-CONNECT:$XDG_RUNTIME_DIR/jblq.sock
echo '{"cmd":"set","feature":"anc","value":"on"}' | socat - UNIX-CONNECT:$XDG_RUNTIME_DIR/jblq.sock
```

Hotplug-aware: waits for the dongle, serves JSON state/commands on a unix socket for a
future GUI/waybar widget.

## EQ / surround (host-side, PipeWire)

The headset applies no EQ from the dongle; QuantumENGINE's own EQ/spatial writes never
touch the device (see `research/jbl-quantum/captures/CAPTURE-ANALYSIS.md`). The equivalent
Linux implementation is a PipeWire filter-chain (10-band EQ / virtual surround), which can
be driven from the daemon. Community-measured JBL tuning curves:
alessandromrc/jbl-quantum-4-linux (EasyEffects presets per model).

## Safety notes

- One write at a time; every value read back where the protocol allows.
- If the headset re-enumerates or glitches after a write, stop — record it as DO-NOT-SEND
  in `research/jbl-quantum/PROGRESS.md`.
- Nothing here touches firmware: DFU-suspect report ids `0xF0/0xF1/0xF4/0xF5/0xF6/0x9A`
  are structurally unreachable (see `jbl_quantum.py::FORBIDDEN_REPORTS`).
- Claiming the vendor interface with libusb/pyusb **destroys the hidraw node until
  replug** — this tool uses hidapi feature-report ioctls only, never interface claiming.
