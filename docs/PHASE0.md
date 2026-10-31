# Phase 0 — existing open-source work check (2026-10-31)

Research-agent report, lightly formatted. Conclusion: the 810 dongle protocol is already
fully reversed by the community; we validate + package rather than re-RE. HeadsetControl
has NO JBL support (verified against current master), so a standalone tool is warranted.

---

**Bottom line: do NOT re-reverse-engineer the 810 protocol — it is already fully reversed, documented, and shipped.** [sidmax7/QuantumEngine](https://github.com/sidmax7/QuantumEngine) (Rust, actively developed, v0.4.8, Oct 2026) implements the complete 810 dongle protocol with a dedicated library crate, and [taron-sys/JBL-Quantum-810-Linux-Tray-Tool](https://github.com/taron-sys/JBL-Quantum-810-Linux-Tray-Tool) publishes a full HID report map including the one report QuantumEngine hasn't decoded (auto-off timer, `0x75`). HeadsetControl has **zero** JBL support (never has); the only 810 work there is an unmerged fork.

## 1. HeadsetControl (Sapd/HeadsetControl) — NO JBL support, ever

Verified 2026-10-31 against current `master` (repo restructured to `lib/devices/*.hpp`; last push 2026-10-28):

- Code search for `jbl` in the repo: **0 files**. Commit-history search for `jbl`/`quantum`: **0 commits**. Issues search: exactly **1** — [issue #357 "URB Interrupt / JBL Q810"](https://github.com/Sapd/HeadsetControl/issues/357) (opened 2024-06-18 by SWW13, **closed stale 2025-06-15 without being implemented**).
- No `jbl_quantum_610_wireless.c`, `jbl_quantum_810_wireless.c`, `jbl_quantum_910_wireless.c` exist at any path. README lists no JBL device.

**Issue #357 is still valuable**: SWW13's never-merged fork branch [`SWW13/HeadsetControl:jbl_q810`](https://github.com/SWW13/HeadsetControl/tree/jbl_q810) contains `src/devices/jbl_q810.c/.h` plus a [USB capture zip](https://github.com/user-attachments/files/15892328/headset-usb-capture.zip) of QuantumENGINE. Why it was never merged: the 810 pushes status (battery, ANC, dial) as **URB_INTERRUPT input reports**, which HeadsetControl's poll/response architecture can't consume.

Fork facts (`src/devices/jbl_q810.c`, 52 lines, only CAP_LIGHTS wired):
- VID JBL `0x0ECB`, PID `0x2069`; capability details: lights on **usage page `0xFF13`, usage `0x1`, interface 5**; commented-out hints: sidetone page `0xFF00` usage `0x1` iface 3, battery page `0xFF43` usage `0x202` iface 3.
- SET codes `SET_LIGHTS 0x4b`, `SET_ANC 0x46` (0=off/1=on/2=TalkThru), `SET_SIDETONE 0x5d` (0=off/1=low/2=mid/3=high); IRQ reports `0x02` ANC, `0x03` ?, `0x06` mic, `0x07` lights, `0x08` battery, `0x10` game/chat mix.

## 2. sidmax7/QuantumEngine — the definitive 810 project

Rust + Tauri (app, `quantumengined` D-Bus daemon, tray, Plasma widget, `quantumenginectl` CLI) + `jbl-quantum` library crate. Created 2026-09-16, 10 releases (v0.3.0→v0.4.8, latest 2026-10-26), MIT/Apache-2.0. Author states the protocol was reversed from the device on Linux and **every command tested on real hardware**.

Feature coverage: battery, mic state, game/chat dial, noise control Off/ANC/TalkThru, sidetone Off/Low/Mid/High, lights on/off, full per-zone RGB (logo + ring, colours/brightness/speed/7 effects), serial/firmware/paired-host-name, live event stream (`watch`). **EQ (19 ten-band profiles + custom 18-band parametric editor + AutoEQ/EqualizerAPO import) and virtual 7.1 surround are host-side (PipeWire)** — the headset has no on-device EQ; curves extracted from QuantumENGINE configs. **Explicitly NOT available over the dongle: on-headset spatial sound, auto-off timer, charging state, volume.**

Safety design worth copying: deliberately never defines firmware/DFU report IDs (0xF0/0xF1/0xF4/0xF5/0xF6/0x9A); unverified Harman models get a read-only probe path before any write.

### Protocol facts from `quantum-linux/crates/jbl-quantum/src/protocol.rs` (vendor HID interface; 2-byte feature reports `[id, value]`)

| Report | Direction | Meaning |
|---|---|---|
| `0x45` / `0x46` | GET / SET | ANC state (0=off, 1=on, 2=TalkThru) |
| `0x49` | GET (feature) | Battery percent 0–100 (also pushed as event `0x08`) |
| `0x4A` / `0x4B` | GET / SET | Lights on/off |
| `0x4C` | SET | Light config header: `[4c, element, speed, segments]` |
| `0x4D` | SET | Light colour frame: `[4d, element, index, R, G, B, mode, last]` |
| `0x51` | GET | Firmware: four 3-byte major.minor.patch triplets |
| `0x5B` | GET | Paired host name (len byte, unknown byte, ASCII) |
| `0x5C` / `0x5D` | GET / SET | Sidetone (0=off/1=low/2=mid/3=high — a 4-step enum, not a slider) |
| `0x61` | GET | Serial, 16 ASCII chars |
| `0x62` | GET | Game/chat dial 0–16 |
| `0x67` | GET | Mic active (boom down AND unmuted) |
| `0x68` / `0x69` | GET | Connection state (+mirror) |
| Events (interrupt IN) | — | `0x02` ANC, `0x03` Bluetooth, `0x06` mic, `0x07` lights, `0x08` battery, `0x09` unknown (connect burst), `0x10` dial |

- Lighting **zones** are element 0 = logo, 1 = ring (L/R mirrored in hardware). **Effects**: `0x00` Breathing, `0x01` Solid, `0x02` Wave, `0x03` Glitch, `0x04` Spin-CW, `0x05` Spin-CCW, `0x06` Rise; up to 10 colour slots/zone; plain RGB byte order.

### Model support matrix (README, from `models.rs`)

| Model | USB IDs | Status |
|---|---|---|
| **Quantum 810 Wireless** | **`0ecb:2069`** | fully verified (all features) |
| Quantum 800 | `0ecb:1f47`, `0ecb:203e` | reads OK (no serial); ANC only with mic boom raised |
| Quantum 850 | `0ecb:219a/b/c` | untested |
| Quantum 910 / 910P / 910X | `0ecb:2088`, `209c`, `20a2`, `20a4`, `209d`, `209f`, `2147`, `214a` | untested (recognized) |
| Quantum 950 / 950X | `0ecb:2127-2129`, `2141`, `213e`, `2140` | untested — 950 uses a *different* protocol (see MyJBx) |
| Quantum One | `0ecb:1f48`, `203a`, `20c2` | untested |
| Quantum 350/360/360P/360X/520/520X/600/610/650/650X | `2047/206b/20b2`, `2115`, `20ab`, `20a5/2142`, `218d/218e`, `21a7/21a9`, `1f46/203c`, `0ecb:205c` (610), `2125/2126`, `213b/213d` | untested |
| Quantum 400 (wired) | `0ecb:1f4c`, `2039`, `20ee` | reads; EQ host-side; no noise control |
| TWS / TWS Air / Stream / Stream Studio / Stream Talk / Stream Wireless | `208a/209b`, `20be`, `205f`, `20b0`, `20af`, `20ed` | recognized, not headsets |

Only the 810 is verified — other PIDs are "may share the protocol, may not", writes gated behind explicit per-feature opt-in.

## 3. taron-sys/JBL-Quantum-810-Linux-Tray-Tool — the missing report decoded

Python tray tool for the 810 (`0ecb:2069`), created 2026-10-16. Covers LED/RGB (colour, mode, speed with hard-clamped safe ranges), battery, ANC/mic/dial/sidetone status read-back, and — uniquely — the **auto power-off timer**. `docs/HID_Reports.md` (284 lines, "confirmed on a Quantum 810 dongle, HID interface 5, by live GET_REPORT probing + parsing the #357 captures") is the single best protocol document. Key facts:

- Vendor HID is **USB interface 5**. Access via hidraw; **claiming the interface with pyusb/libusb destroys the hidraw node until replug** — use hidraw/HIDIOCSFEATURE instead.
- **Event burst on headset power-on**: `02, 03, 06, 07, 08 (x4), 09, 10` — best way to (re)sync all state. Battery event `0x08` also pushed ~every 2 s in use.
- **Mute bracketing**: every mute change is bracketed by `0x2f` markers (`2f 02` toggle … `06 XX` authoritative … `2f 00` release); `2f 00` is NOT "unmuted" — treat `0x06`/`0x67` as authority. Mic arm up forces muted and suppresses the mute button entirely.
- **Read-back rule**: for every SET, GET id = SET id − 1 (`0x46`→`0x45`, `0x4b`→`0x4a`, `0x5d`→`0x5c`). **Sole exception: auto power off `0x75`, where GET = SET = `0x75`**, and it has **no event ACK** — confirmed only via GET read-back.
- **Auto-off timer (SET/GET `0x75`)**: value = timeout in 5-minute units — `0x00`=off, `0x06`=30 min, `0x0C`=1 h, `0x18`=2 h; byte2 `0x02` undecoded. Decoded from QuantumENGINE pcaps (SET `0x75 0c/0x06/0x00`).
- **RGB safe ranges (hardware-bricking hazard)**: segment count must be 1–5; the 0x4C tempo/speed byte ∈ {0x28, 0x32, 0x3C, 0x46, 0x4B, 0x50, 0x64}; frame index 0–4; `0x4D` "last" byte 0–8 is a per-segment parameter (NOT `index*2`); mode byte 0x00–0x06. **Segment counts >5 wedge the lighting MCU into a strobe lockup** — the only dangerous field. Commit = `0x4b 01`.
- Undecoded GETs: `0x51` (12-byte EQ-like block), `0x5b`, `0x71`, `0x47/0x50` static info, dynamic feature `0x07`. Firmware quirk: GET for an unknown report ID doesn't stall — it answers with the nearest known lower ID; kernel may leave stale tail bytes, so verify the echoed ID.

Cross-check: the same report IDs were **independently observed on the Quantum 360 Wireless dongle (`0ecb:2115`)** by Cluxnei/omarchy-jbl-quantum — the Airoha-dongle protocol family shares this report map across 6xx/8xx/9xx/3xx wireless models.

## 4. Other projects

| Project | Device(s) | What it does | Maturity |
|---|---|---|---|
| [Tymon3310/jbl-quantum-linux](https://github.com/Tymon3310/jbl-quantum-linux) | Quantum 910 (`0x2088`), 610 (`0x205c`) | Tray battery monitor; event `0x08` + poll `0x49`; charging bit = packet[2]&0x01; mic via `0x67`, link via `0x68`; PipeWire EQ conf | Python, small, Oct 2026 |
| [plugato/JBL_Baterry_Monitor](https://github.com/plugato/JBL_Baterry_Monitor) | Quantum 910 (`0x2088`) | Tray battery via pyusb interrupt endpoint 0x83 (iface 3), report `0x08`; logs `0x2f` mute markers | Python, Jan 2026, 5★ |
| [666mille/MyJBxHeadsetControl](https://github.com/666mille/MyJBxHeadsetControl) | **Quantum 950 Wireless (`0x2127`)** | Stream Deck plugin: battery, ANC, ambient-aware, mute, chat balance, EQ presets, spatial mode — via a **different envelope protocol**: feature write `88 00 DD 02 00 01 00 05 00 codeA codeB 01 00 value`, multi-packet chunked writes (54-byte chunks) for EQ (virtual FIDs `0x0E02`/`0x0E7F`), events start `86 00 DD …` (ANC=`18 00`, ambient=`19 00`, mute=`03 0C`, link=`35 00`, spatial mode `0x81 fixed/0x82 head-tracking`). Interface 5 | TypeScript, active (Oct 2026), 3★ |
| [Heiphaistos/PureRGB](https://github.com/Heiphaistos/PureRGB) `jbl_quantum.rs` | 610, **810**, 910, 910X, 910P, 910X-Black | Sidetone only, via HID collection **usage page `0xFF13`**, GET `0x5C` / SET `0x5D` | Rust backend |
| [alessandromrc/jbl-quantum-4-linux](https://github.com/alessandromrc/jbl-quantum-4-linux) | many models (Q300…Q950) | **No HID at all** — 91 EasyEffects presets (per-model JBL driver curve, surround-on and stereo-off variants, 8-/10-band game EQ presets, mic presets) extracted from QuantumENGINE configs | Python/graphs, Oct 2026 |
| [Cluxnei/omarchy-jbl-quantum](https://github.com/Cluxnei/omarchy-jbl-quantum) | Quantum 360 Wireless `0ecb:2115` | Waybar battery/health/usage from dongle (hidraw) | Oct 2026, 1★ |
| [KAJIKK/jbl-quantum-tws-linux](https://github.com/KAJIKK/jbl-quantum-tws-linux) | Quantum TWS earbuds | Battery + ANC/mic state tray | Sep 2026 |
| OpenRGB | Quantum 600 `0ecb:203c` | **No support.** Single unanswered feature request [OpenRGB issue #2206](https://gitlab.com/CalcProgrammer1/OpenRGB/-/issues/2206) (2022) | never implemented |

## 5. Kernel side (audio, not HID control)

- `sound/usb/quirks.c` (torvalds/master) carries `QUIRK_FLAG_FIXED_RATE` for `0ecb:205c` (610), `0ecb:2125` (650), **`0ecb:2069` (810)**, plus the older 2021 registration quirk delaying audio registration for JBL Quantum dual-interface headsets. hid-quirks.c has **no** 0ECB entries — the vendor HID interface binds to hid-generic/hidraw out of the box.
- [alsa-lib issue #279](https://github.com/alsa-project/alsa-lib/issues/279) ("Missing quirk for JBL Quantum 810") is **resolved**: fixed by kernel ~6.2/6.3 (`QUIRK_FLAG_FIXED_RATE`). Dongle audio on modern kernels needs no manual quirk.

## 6. Feature matrix (810 focus)

| Feature | QuantumEngine (sidmax7) | taron-sys tray tool | SWW13 fork (unmerged) | Others |
|---|---|---|---|---|
| Sidetone (4-step) | SET 0x5D | read-back 0x5C | defined, not wired | PureRGB |
| Chatmix / game-chat dial | read 0x62, event 0x10 | read | IRQ 0x10 defined | omarchy (360) |
| Battery | 0x49 + event 0x08 | yes | defined | Tymon3310/plugato/omarchy |
| ANC | SET 0x46 | yes | defined | MyJBx (950, different protocol) |
| Ambient aware / TalkThru | 0x46=2 | yes | — | MyJBx (950) |
| QuantumSURROUND / spatial | not on dongle; host-side (PipeWire) | — | — | alessandromrc host-side; MyJBx (950) device spatial mode |
| EQ | host-side: profiles + parametric + AutoEQ import | — | — | alessandromrc EasyEffects |
| Mic monitoring/mute state | 0x67 + event 0x06 | incl. 0x2f bracket rule | IRQ 0x06 defined | Tymon3310 |
| Lighting | full RGB: zones, 7 effects | with safe-range clamps | only feature wired | OpenRGB: no |
| Auto-off timer | "not exposed / not found yet" | **0x75** (only implementation anywhere) | — | — |
| Volume wheel / hw volume | not over dongle | — | — | system mixer only |
| Firmware version / serial | 0x51 / 0x61 | yes | — | omarchy 0x61 |

**Charging state**: dongle doesn't report it (omarchy infers from battery rising; Tymon3310 reads packet[2]&0x01 on 910/610 — unverified on 810).
