# jbl-quantum-engine-linux

Native Linux control for **JBL Quantum wireless headsets** (primary: **Quantum 810
Wireless**, USB `0ecb:2069` dongle) — pure Python + hidapi/hidraw. No Wine, no VM, no
JBL binaries. This is personal interoperability work: reimplementing the subset of
QuantumENGINE's device protocol that the community has verified, with full evidence.

- **`app/`** — the application: `jblq` CLI, hotplug-aware daemon, GUI, library, installer, udev rule
- **`docs/`** — protocol documentation, evidence, USB captures
  - [`PROTOCOL.md`](docs/PROTOCOL.md) — per-feature report table with
    evidence tags (our own capture parse vs upstream projects vs binary RTTI)
  - [`docs/PHASE0.md`](docs/PHASE0.md) — existing open-source work audit
    (don't re-RE what exists)
  - [`docs/captures/`](docs/captures/) — 23 action-labeled USBPcap captures
    (public, HeadsetControl issue #357) + our parser + analysis

## Quick start

```bash
sudo cp app/udev/99-jbl-quantum.rules /etc/udev/rules.d/
sudo udevadm control --reload && sudo udevadm trigger
pip install hid            # hidapi bindings
./app/jblq probe    # read-only state dump — safe first step
```

## Credits / sources

- [sidmax7/QuantumEngine](https://github.com/sidmax7/QuantumEngine) (MIT/Apache) — the
  verified report map; `evidence-quantumengine-*.rs` are reference copies.
- [taron-sys/JBL-Quantum-810-Linux-Tray-Tool](https://github.com/taron-sys/JBL-Quantum-810-Linux-Tray-Tool)
  — auto-off report 0x75, RGB safety ranges, mute bracketing.
- [Sapd/HeadsetControl issue #357](https://github.com/Sapd/HeadsetControl/issues/357)
  by SWW13 — the USB captures.

## License

MIT for our code. Reference copies in `research/` keep their upstream licenses
(MIT/Apache-2.0). No JBL/Harman software or firmware is included; suspected DFU report
IDs are deliberately unreachable in the code.
