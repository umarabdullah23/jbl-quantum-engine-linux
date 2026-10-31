# jbl-quantum-linux

Native Linux control for **JBL Quantum wireless headsets** (primary: **Quantum 810
Wireless**, USB `0ecb:2069` dongle) — pure Python + hidapi/hidraw. No Wine, no VM, no
JBL binaries. This is personal interoperability work: reimplementing the subset of
QuantumENGINE's device protocol that the community has verified, with full evidence.

- **`tools/jbl-quantum/`** — `jblq` CLI, hotplug-aware daemon, library, udev rule
- **`research/jbl-quantum/`** — protocol documentation, evidence, USB captures
  - [`PROTOCOL.md`](research/jbl-quantum/PROTOCOL.md) — per-feature report table with
    evidence tags (our own capture parse vs upstream projects vs binary RTTI)
  - [`PHASE0.md`](research/jbl-quantum/PHASE0.md) — existing open-source work audit
    (don't re-RE what exists)
  - [`captures/`](research/jbl-quantum/captures/) — 23 action-labeled USBPcap captures
    (public, HeadsetControl issue #357) + our parser + analysis

## Quick start

```bash
sudo cp tools/jbl-quantum/udev/99-jbl-quantum.rules /etc/udev/rules.d/
sudo udevadm control --reload && sudo udevadm trigger
pip install hid            # hidapi bindings
./tools/jbl-quantum/jblq probe    # read-only state dump — safe first step
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
