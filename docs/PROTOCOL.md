# JBL Quantum 810 Wireless — HID control protocol (Linux interop)

Device under study: **JBL Quantum 810 Wireless** (the headset physically owned by the user),
USB `VID 0x0ECB` (Harman/JBL) `PID 0x2069` — the **USB-C wireless dongle** enumeration.

Evidence tags:
- **[LIVE]** = verified on the real Quantum 810 by this tool (2026-11-01, all 0x45–0x75 simple reports + writes)
- **[CAPTURE]** = our own parse of the public QuantumENGINE USBPcap captures (SWW13,
  HeadsetControl issue #357 attachment) — see `captures/CAPTURE-ANALYSIS.md`. First-hand.
- **[QE]** = sidmax7/QuantumEngine `jbl-quantum/src/protocol.rs` (hardware-verified project,
  copy in `evidence-quantumengine-protocol.rs`).
- **[TT]** = taron-sys/JBL-Quantum-810-Linux-Tray-Tool `docs/HID_Reports.md`
  (`evidence-traysys-HID_Reports.md`) — includes the auto-off report and RGB safety ranges.
- **[RTTI]** = strings/RTTI extracted from the locally installed QuantumENGINE 2.8.6
  `AirohaHidCoreLib.dll` (feature-command inventory; corroborates the feature set, not byte
  offsets — see "RACE layer" at the bottom).
- **[INF]** = `oem93.inf` (QuantumAI.inf) from the Windows drive — the full model/USB-ID map.

Anything not tagged with at least one of these is **[INFERENCE]** and the tool refuses to send it.

---

## 1. Topology (FACT)

- Dongle exposes 6 USB interfaces: `MI_00` game audio (usbaudio, `HarmanAudioService`
  upper filter), `MI_02` chat audio, `MI_03` **HID event interface** (interrupt IN
  `0x83`, 8-byte reports — events observed here in [CAPTURE]), `MI_05` **"JBL Quantum USB
  Input Device" = control HID** (QuantumAI driver) — all configuration feature reports live
  here [CAPTURE wIndex=5 / INF / TT].
- Bluetooth mode exposes an Airoha custom GATT service
  (`00000000-0000-0000-0099-aabbccddeeff`, BT VID 0x0094=Airoha) — **not covered by this
  tool** (separate RACE-over-BLE protocol; see §5).
- Vendor ID note: the task brief guessed 0x0DC4 — the real JBL/Harman VID is **0x0ECB**.

## 2. Feature reports — control interface (MI_05), 2-byte reports `[id, value]`

All writes are HID **SET_REPORT(FEATURE)** (`bmRequestType 0x21, bRequest 0x09,
wValue 0x03<id>`, wIndex=5); reads are GET_REPORT on the mirror id. [CAPTURE + QE]

| Feature | SET id | GET id | Values | Persistent? | Evidence | Undo/default |
|---|---|---|---|---|---|---|
| ANC (noise cancelling) | `0x46` | `0x45` (mirror) | `0`=off `1`=on `2`=TalkThru (ambient aware) | RAM-state; device restores last mode on power-on [INFERENCE] | SET `4600`/`4601`/`4602` seen [CAPTURE]; enums [QE] | read `0x45` before first write; restore it |
| Sidetone (mic monitoring) | `0x5D` | `0x5C` (mirror) | **4-step enum, not a slider**: `0`off `1`low `2`mid `3`high | persists across reconnect [INFERENCE] | SET `5d00`–`5d03` seen [CAPTURE] | read `0x5C` first; restore |
| Lights master on/off | `0x4B` | `0x4A` (mirror) | `0`=off `1`=on | persists [INFERENCE] | SET `4b00`/`4b01` [CAPTURE] | read `0x4A` |
| Light zone config | `0x4C` | (read = status block, byte0 = lights state — NOT what was written) | `[4c, element, speed, segments]`; element 0=logo 1=ring; speed ∈ {0x28,0x32,0x3C,0x46,0x4B,0x50,0x64}; **segments 1–5 (HARD SAFETY LIMIT — >5 wedges the lighting MCU)** | volatile frame pipeline [TT] | `4c003205`, `4c006405` [CAPTURE] | factory: read at boot (QuantumENGINE writes `4c006405` at connect [CAPTURE]) |
| Light colour/effect | `0x4D` | (status block as 0x4C) | `[4d, element, slot, R, G, B, mode, last]`; mode 0–6 = Breathing/Solid/Wave/Glitch/Spin-CW/Spin-CCW/Rise; slot 0–4; **byte8 is a per-segment param 0–8, not index×2** [TT] | volatile [TT] | `4d000099ff000000` etc. [CAPTURE] | commit set = `4b 01` |
| Auto power-off timer | `0x75` | **`0x75` (same id — sole exception to the GET=SET−1 rule)** | 5-minute units: `0`off `06`30min `0C`1h `18`2h; byte2 `0x02` undecoded; **no event ACK — verify by read-back only** [TT] | persists [INFERENCE] | [TT] only (not in our captures) | read `0x75` first |
| Battery % | — | `0x49` | 0–100 (bit: charging on some models [INFERENCE]) | — | event `08 5f`=95% [CAPTURE]; id [QE] | — |
| Game/chat dial | — | `0x62` | 0–16 (0=all chat, 16=all game) | — | events `1000`…`1010` [CAPTURE]; id [QE] | — |
| Mic active | — | `0x67` | boom down AND unmuted | — | events `0600`/`0601` [CAPTURE] | — |
| Link state | — | `0x68`/`0x69` | connected | — | [QE] | — |
| Firmware | — | `0x51` | 4× major.minor.patch triplets | — | [QE] | — |
| Serial | — | `0x61` | 16 ASCII | — | [QE] | — |
| Paired-host name | — | `0x5B` | len byte, 1 unknown, ASCII | — | [QE] | — |

**Read-back rule [TT, confirmed by report-id structure]:** GET id = SET id − 1, except `0x75`.
**Quirk:** a GET for an unknown report id does not stall — the device answers with the nearest
known lower id, so always verify the echoed id byte before trusting a read [TT].

## 3. Interrupt-IN events (MI_03, endpoint `0x83`) — pushed, 2-byte reports `[id, value]`

[CAPTURE — all observed verbatim in the pcapng set; ids also in QE/TT]

| id | Meaning | Observed |
|---|---|---|
| `0x02` | ANC mode | `0200`/`0201`/`0202` |
| `0x03` | Bluetooth state | `0300` in connect burst |
| `0x06` | Mic state | `0600`/`0601`; every mute toggle is bracketed by `0x2f` markers (`2f 02`…`2f 00`) — `2f 00` is NOT "unmuted"; treat `0x06` as authority [TT] |
| `0x07` | Lights state | `0700`/`0701` |
| `0x08` | Battery % | `085f`=95, `085a`=90; fires on any host interaction and ~2 s in use [TT] |
| `0x09` | wireless connect burst | `0901` |
| `0x10` | dial turn | `1000`…`1010` (0–16) |

Power-on burst order: `02 03 06 07 08(×4) 09 10` — the cleanest full-state resync [TT].
**Never claim charging state from the dongle** — not reported.

## 4. What QuantumENGINE does NOT do over the dongle (FACT)

- **EQ / parametric EQ, QuantumSURROUND / DTS spatial**: our parse of
  `spatial-sound-*.pcapng` (DTS, QuantumSURROUND, off) contains **zero** HID class writes to
  the device — spatial audio switching is entirely host-side (Windows spatial sound + host
  DSP). Sidmax7 independently reached the same conclusion; the headset exposes no on-device
  EQ via the dongle. → Our Linux replacement implements EQ/surround with **PipeWire
  filter-chain** (host-side), mirroring what the Windows app actually does.
  (`AirohaPeqLibrary.dll`/`RealTimeUpdatePeq` in the binary relates to the Airoha BT/BLE
  audio path, not the dongle feature reports.)
- **Volume wheel / charging state**: not exposed by the dongle; use system mixer.

## 5. Not implemented (deliberately)

- **Firmware/DFU**: suspected DFU report ids `0xF0/0xF1/0xF4/0xF5/0xF6/0x9A` are
  deliberately ABSENT from our tool (design borrowed from QuantumEngine) — no firmware
  flows, per task rules.
- **Bluetooth (Airoha GATT / RACE-over-BLE)** and **on-headset spatial mode**
  (950-family only, different envelope protocol) — out of scope for the 810.
- **QuantumENGINE's RACE layer** (`AirohaHidCoreLib.dll`): the Windows app speaks Airoha
  RACE packets (relay resp ID 0x0D01; `RaceGetBattery`, `RaceReadNv`/`RaceWriteNv`,
  `SetSidetoneLevel`, `SetGameChatMixRatio`, `SetAncPassThruGain`, PEQ cmds, … — [RTTI
  inventory]) wrapped over HID. The community report ids above are the device-side
  simple-report surface of the same feature set and are sufficient for all user-facing
  features; RACE-level RE is only needed if a future feature is missing.

## 6. Model coverage seed [INF — oem93.inf v2.0.0.010]

`0ECB:` 2069=810*, 1F47/203E=800, 2088/209C=910, 20A2=910PS, 209D/209F/2147/214A=910X,
2127/2128/2129=950, 2141/213E/2140=950X, 1F48/203A/20C2=ONE, 205C=610, 1F46/203C=600,
1F4C/2039/20EE=400, 2115=360, 20A5/2142=360X, 20AB=360PS, 2047/206B/20B2=350,
2125/2126/213B/213D=650, 218D/218E/21A7/21A9=520, 219A/B/C=850.
Control interface index varies by model (MI_05 for the wireless family above, MI_01/MI_03
for 300/350/TWS/Stream). (* = hardware-verified here; the others are recognized but writes
stay gated per-device — probe-read-only first.)
