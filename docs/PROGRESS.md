# JBL QuantumENGINE → Linux RE — PROGRESS LOG

Task: RE JBL QuantumENGINE (Windows) protocol → native Linux replacement (hidapi), personal
interoperability. No JBL binaries redistributed; no firmware flows; headset is only hardware.

## 2026-10-31 — Phase 0 setup + target identification

- **No Windows box/capture possible from this Linux env** → adapted: Phase A (USBPcap) is
  deferred; static RE of QuantumENGINE binaries instead (they ARE available on the Windows
  partition of this dual-boot machine, mounted READ-ONLY at
  `/run/media/umar/56E2B9D1E2B9B599`).
- **Headset identified from Windows registry hives (offline, read-only copy in ~/jbl-re/hives/):**
  - **JBL Quantum 810 Wireless** — actual hardware on this machine.
  - USB dongle: `VID_0ECB PID_2069` (JBL vendor ID is **0x0ECB**, NOT 0x0DC4 as the task
    guessed). Interfaces: MI_00 "Game" audio (usbaudio + UpperFilters `HarmanAudioService`),
    MI_02 "Chat" audio, MI_05 **"JBL Quantum USB Input Device" = control HID** (HidUsb,
    boot subclass). RE target interface = MI_05.
  - Bluetooth: MAC 68:D6:ED:4A:9F:AD, exposes **Airoha custom GATT service**
    (UUID 00000000-0000-0000-0099-aabbccddeeff; BT VID 0x0094 = Airoha).
- **Install found on Windows drive:** `C:\Program Files\JBL\QuantumENGINE`, FileVersion
  2.8.6.0 — same version as the freshly downloaded installer
  (`~/Downloads/JBL_QuantumENGINE_Installer_2.8.6_x64.exe`). Copy of device-logic DLLs in
  `~/jbl-re/scratch/binaries/` (scratch only, never committed/redistributed).
- **Binary survey:** UI layer `JBLQuantumControl.dll/.exe` = .NET (MAUI). Device layer =
  **native x64 C++**: `AirohaHidCoreLib.dll` (2.3MB, PDB path
  `C:\work\code\quantum\lib\3rdparty\airoha_hid_core_lib\...`), `AirohaPeqLibrary.dll`,
  `HIDDevice.dll` (wraps **hidapi**: hid_enumerate/hid_open/hid_get_feature_report...),
  `DeviceDiscovery.dll`, `USBDevice.dll`.
- **Protocol family identified (FACT, from RTTI strings in AirohaHidCoreLib.dll):**
  **Airoha RACE protocol** over HID (`RaceGetBattery`, `genRawRacePacket()`, relay resp
  race ID 0x0D01, `RaceReadNv`/`RaceWriteNv` NVRAM commands, dongle types
  AB1565/1568/1571D/1585/1588 ULL2/LEA). Recovered command/task class map:
  battery (Get/Dual/Race), sidetone (Get/Set Level + State), game/chat mix
  (Get/SetGameChatMixRatio, GameChatBalance), mic volume (Game + StandAlone), ANC
  (On/Off/PassThruGain/Settings, ReadAncNv/SaveAncNv → NVRAM), advanced passthrough
  (ambient aware), voice guidance, wear detection, notification tone
  (Get/SetNotificationActivation + Map), busy light, PEQ parametric EQ
  (Load/SavePeqUiData, RealTimeUpdatePeq, SavePeqCoef, SetPeqGroupIndex, ReclaimPeqNvKey),
  agent/fw version, telemetry. Full string dumps in `~/jbl-re/scratch/airoha_strings*.txt`.
- **Complete USB ID table extracted (FACT, from oem93.inf "QuantumAI.inf" on the Windows
  drive, driver 07/02/2026 v2.0.0.010)** — every Quantum model's VID_0ECB PID + control
  interface index (e.g. 810=2069 MI_05, 910=2088 MI_05, 610=205C MI_05, 800=1F47/203E
  MI_05, 950=2127/2128 MI_05, ONE=1F48/203A MI_05, 300=1F52 MI_01/MI_03 …) → seed for
  `tools/jbl-quantum` supported-device table.
- Ghidra headless setup in progress (JDK25 + Ghidra 12.2 downloading) to decompile
  `genRawRacePacket` + RACE command ID tables from AirohaHidCoreLib.dll.
- Phase 0 existing-work check (HeadsetControl devices etc.) running as background agent.

Next: decompile RACE framing + per-feature command IDs/ranges → PROTOCOL.md → Python CLI/daemon.

## 2026-10-31 — Phase 0 complete + protocol validated + Linux tool built

- **Phase 0 verdict (PHASE0.md):** HeadsetControl = ZERO JBL support (verified vs master,
  0 files/commits; only stale unmerged issue #357 fork). The working open implementations
  are sidmax7/QuantumEngine (Rust, all-features hardware-verified) and
  taron-sys/JBL-Quantum-810-Linux-Tray-Tool (auto-off 0x75 + RGB safety ranges).
  → per the task rule, no re-RE; we validate + package.
- **Captures (research/jbl-quantum/captures/):** 23 action-labeled USBPcap pcapng files
  (public SWW13/HeadsetControl #357 attachment) + our own USBPcap parser
  (usbpcap_parse.py) + CAPTURE-ANALYSIS.md. **Our independent parse confirms**: SET_REPORT
  FEATURE on interface 5, 2-byte `[id, value]`: ANC 0x46 (0/1/2), sidetone 0x5D (0–3),
  lights 0x4B, light config 0x4C (`4c 00 32 05`), light colour 0x4D frames, and interrupt
  events on ep 0x83 (02 ANC, 03 BT, 06 mic, 07 lights, 08 battery `085f`=95, 09 link,
  10 dial 0–16). **Negative result proven**: spatial-sound-*/EQ captures contain zero HID
  writes → QuantumSURROUND/EQ are host-side DSP (Windows spatial sound), not device
  reports. QuantumENGINE also re-writes light state at boot (`4c 00 64 05`).
- **PROTOCOL.md written** — per-feature table with evidence tags (CAPTURE/QE/TT/RTTI/INF),
  persistence + undo columns, GET=SET−1 read-back rule + 0x75 exception, unknown-id quirk,
  model coverage seed from oem93.inf (30 PIDs, control interface per model).
- **tools/jbl-quantum built:** `jbl_quantum.py` (library: discovery via hidapi, verified
  report ids only, DFU ids structurally forbidden, first-write-wins undo registry,
  segments hard-clamped 1–5), `jblq` CLI (probe/battery/dial/info/sidetone/anc/lights/
  autooff/restore/listen), `jblq_daemon.py` (hotplug-aware, unix-socket JSON), udev rule
  (0ecb hidraw 0660+uaccess), README with feature matrix vs QuantumENGINE.
  Compiles clean; graceful failure verified (absent device → explicit error, exit 2;
  unsupported → exit 3). hidapi built from source into ~/jbl-re/lib for testing
  (no passwordless sudo for apt).
- **PENDING live verification:** the dongle is not plugged into the Linux side right now.
  When plugged: `jblq probe` (read-only) first, then one setter at a time with read-back.
  (USBPcap Phase-A on Windows not needed — captures + protocol already public.)


## 2026-10-31 — Deep RE round 2 (RACE layer decompiled)

- Ghidra 12.2 full-binary decompile of AirohaHidCoreLib.dll (dumps in repo re-work/).
- **Complete RACE command-ID table recovered: 119 commands** (re-work/strings/race_cmd_table.txt,
  PROTOCOL-RACE.md §3) — includes the missing-feature unlock paths: game/chat balance SET
  (0x35/0x36), voice guidance (0x5E/0x5F), wear detection (0x52/0x53), notification tone
  (0x59/0x5A), busy light (0x54/0x55), factory reset (0x1F), AA passthrough (0x24/0x25),
  adaptive ANC/EQ, on-device EQ (0x04-0x06).
- **Relay envelope decoded [DECOMP]**: dongle wraps RACE in ASCII-bracket envelope;
  resp type 0x5D, relay race ID 0x0D01 (parser enforces both + length).
- **Encryption: NONE.** Full string sweep + decompile: no AES/CRC/HMAC/cipher in any
  device binary — config channel is plaintext (feature reports + envelope framing).
  Nothing to "remove"; firmware signing untouched by design.
- **Lighting correction**: 0x4C byte2 = BRIGHTNESS % (40/50/60/70/75/80/100), not "speed"
  (sidmax7 comment + QE boot write 0x64=100). GUI/daemon/library renamed; effect speed =
  0x4D tail byte ("SEG PARAM" 0-8).
- Small missing features from the UI property dump now documented with unlock map
  (PROTOCOL-RACE.md §5) — all stay fail-closed until live-verified per-command.

## 2026-11-01 — LIVE VERIFICATION ROUND 1: ALL PASS (real Quantum 810, dongle 0ecb:2069)

Read-only probe — 8/8 getters verified live:
ANC on · Sidetone off · Lights off · Auto-off 30 min · Battery 30% · Dial 16/16 ·
Serial MM0168-JO0050195 · Firmware 0.3.2/0.3.2/0.0.0/0.3.2. Includes 0x75 GET=SET
exception + unknown-id quirk handling (no false reads).

Writes (each: set → settle → read-back → restore to original):
- Sidetone 0x5D: off→mid→off ✓ (read-back exact)
- ANC 0x46: on→talkthru→off→on ✓ (NOTE: needs ~1.5 s settle after SET before the
  0x45 mirror read is trustworthy — 0.4 s raced the device)
- Lights 0x4B: on↔off ✓
- Zone config 0x4C: brightness 50% logo / 100% ring, segments 5 ✓ (visually confirmed)
- Zone colour 0x4D: logo (255,51,0) Solid ✓
- Auto-off 0x75: 30→120→30 min ✓ (read-back both)
- Session undo/restore ✓ — headset left in the user's original state (ANC on, sidetone
  off, lights off, auto-off 30).

Bugs found + fixed live: dual hidapi binding support (hid.Device vs hid.device);
daemon crashed on access-denied (now survives); snapshot() mixed int/bytes originals
(now normalized). udev rule installed live (plugdev 0660 on the JBL hidraw0).

VERDICT: all simple feature reports (0x45–0x75) verified on real hardware. The
community protocol + our tool are proven. RACE-layer commands remain documented-only
until their own capture round.

## 2026-11-01 — Handoff to Windows phase

Owner moving headset+dongle to Windows for the RACE unlock capture round (USBPcap +
QuantumENGINE). Full procedure in SESSION-HANDOFF.md §15. Linux daemon/GUI left running —
they re-detect the dongle automatically when it returns.
