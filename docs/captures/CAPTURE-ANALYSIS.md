# Capture analysis — QuantumENGINE traffic (JBL Quantum 810)

Source: public USBPcap captures attached to Sapd/HeadsetControl issue #357 by SWW13
("USB Captures of most status changes by the device and software", 2024-06-18) —
23 action-labeled `*.pcapng` files recorded while QuantumENGINE drove a Quantum 810
dongle (`0ecb:2069`). Downloaded to this folder unchanged; not re-distributed JBL
software, only USB traffic recordings of the user's own device.

Parser: `usbpcap_parse.py` (this folder). Run with any Python ≥3.9:

    python3 usbpcap_parse.py '*.pcapng'

Method: walk pcapng Enhanced Packet Blocks → USBPcap pseudo-header (headerLen is 28,
not 27, in these captures) → keep control transfers (`transfer==2`) with an HID class
setup packet (`bmRequestType & 0x60 == 0x20`, `bRequest==0x09` SET_REPORT) and
interrupt-IN payloads (`transfer==1`, complete direction).

## Headline findings (first-hand evidence for PROTOCOL.md)

Every setting change is a **2-byte HID SET_REPORT(FEATURE)** on interface 5
(`wValue=0x03<report_id>`, `wIndex=0x0005`), payload `[report_id, value]`:

| Capture | wValue | payload | meaning |
|---|---|---|---|
| anc-set-off / anc-set-on | 0346 | `46 00` / `46 01` | ANC off / on |
| tt-set-on | 0346 | `46 02` | TalkThru (ambient aware) |
| mic-sidetone-off/low/mid/high | 035d | `5d 00`…`5d 03` | sidetone 4-step enum |
| headset-light-off / -on | 034b | `4b 00` / `4b 01` | lights master off/on |
| headset-light-change | 034c | `4c 00 32 05` | zone config: element 0, speed 0x32, segments 5 |
| | 034d | `4d 00 00 99ff00 00 00` … | colour frames: element, slot, R,G,B, mode, last |
| headset-usb-connect | 034c/034d | `4c 00 64 05`, 2 colour frames | QuantumENGINE re-writes light state at boot |
| mic-on / mic-off | 0100 (wIdx 0602) | `01` | standard HID alt-interface mic LED path, not the vendor feature reports |

Interrupt-IN events (endpoint `0x83`, 2 bytes, `[id, value]`):

- `02 00/01/02` ANC mode, `03 00` Bluetooth, `06 00/01` mic,
  `07 00/01` lights, `08 5f` battery 95%, `08 5a` battery 90%,
  `09 01` wireless-link burst, `10 00…10 10` game/chat dial 0–16.

**Spatial audio is host-side (key negative result):** `spatial-sound-dts`,
`spatial-sound-jbl-quatumsurrond`, `spatial-sound-off` contain **zero** HID class
transfers — switching QuantumSURROUND/DTS/off never writes the device. EQ likewise has
no device report. On the 810 dongle, EQ/spatial = Windows host DSP → on Linux,
PipeWire filter-chain is the correct equivalent, not more HID RE.
