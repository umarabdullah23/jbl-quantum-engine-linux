# SESSION HANDOFF — JBL Quantum Engine (Linux) — 2026-10-31

Everything from the "RE QuantumENGINE → Linux app" task, condensed so any future session
can continue without re-deriving. Authoritative docs: `docs/PROTOCOL.md`,
`PHASE0.md`, `PROGRESS.md`, `captures/CAPTURE-ANALYSIS.md`.

## 1. What was asked

RE JBL QuantumENGINE (Windows) and build a working native Linux replacement app (no Wine/VM)
covering the same device features. Interoperability for personal use; no redistribution of
JBL binaries; no firmware flows; headset is the only hardware; label facts vs inference.

## 2. Hardware & target identification

- User's headset: **JBL Quantum 810 Wireless**. Identified from the Windows partition's
  registry hives (dual-boot machine; Windows mounted READ-ONLY at
  `/run/media/umar/56E2B9D1E2B9B599`).
- Dongle: `VID_0ECB:PID_2069` (JBL vendor = **0x0ECB**, NOT the 0x0DC4 the task guessed).
  Interfaces: MI_00 game audio (+`HarmanAudioService` filter), MI_02 chat audio,
  MI_03 HID events (interrupt IN ep 0x83), **MI_05 = control HID ("QuantumAI" driver)**.
- Bluetooth mode: MAC 68:D6:ED:4A:9F:AD, Airoha GATT service
  (`00000000-0000-0000-0099-aabbccddeeff`) — NOT implemented (separate RACE-over-BLE).
- QuantumENGINE 2.8.6 installed on Windows drive (`C:\Program Files\JBL\QuantumENGINE`);
  same version as downloaded installer `~/Downloads/JBL_QuantumENGINE_Installer_2.8.6_x64.exe`.
  Device logic = native C++ (`AirohaHidCoreLib.dll` = Airoha RACE protocol over HID);
  UI = .NET MAUI (`JBLQuantumControl.dll`).

## 3. Phase 0 result (why we didn't re-RE)

HeadsetControl has ZERO JBL support (verified vs master). The 810 protocol is fully reversed
by open source: **sidmax7/QuantumEngine** (Rust, hardware-verified, MIT/Apache) and
**taron-sys/JBL-Quantum-810-Linux-Tray-Tool** (auto-off 0x75 + RGB safety ranges).
We validated + packaged instead of re-RE-ing — independently confirmed by parsing the
public USBPcap captures ourselves (SWW13, HeadsetControl issue #357; 23 action-labeled
pcapng files now in `docs/captures/`).

## 4. Protocol summary (details + evidence tags in PROTOCOL.md)

- 2-byte HID feature reports `[id, value]` on interface 5. GET id = SET id − 1
  (exception: auto-off `0x75` GET=SET, no ACK — verify by read-back).
- SET 0x46 ANC (0 off/1 on/2 talkthru) · 0x5D sidetone (0–3 enum, 4-step NOT slider) ·
  0x4B lights master · 0x4C zone config `[id, element, speed, segments]` (speed ∈
  {0x28,0x32,0x3C,0x46,0x4B,0x50,0x64}; **segments 1–5 HARD LIMIT — >5 wedges lighting MCU**) ·
  0x4D colour frame `[id, element, slot, R,G,B, mode(0–6), last(0–8)]` · 0x75 auto-off
  (5-min units, byte2=0x02 undecoded).
- GET: 0x45 ANC mirror · 0x49 battery 0–100 · 0x4A lights mirror · 0x51 fw (4 triplets) ·
  0x5B host name · 0x5C sidetone mirror · 0x61 serial (16 ascii) · 0x62 dial 0–16 ·
  0x67 mic active · 0x68/0x69 link.
- Interrupt events (ep 0x83): 02 ANC · 03 BT · 06 mic (0x2f mute brackets; 2f 00 ≠ unmuted) ·
  07 lights · 08 battery · 09 link burst · 10 dial. Power-on burst 02,03,06,07,08×4,09,10.
- **EQ/QuantumSURROUND are HOST-SIDE** (our parse of spatial-*.pcapng: zero HID writes).
  Charging state + volume not exposed by dongle. Unknown-id GET quirk: answers with nearest
  lower known id — verify echoed id byte.
- Full model/USB-ID map from `oem93.inf` (30 PIDs; 810 verified, others gated probe-first).
- DFU-suspect reports 0xF0/0xF1/0xF4/0xF5/0xF6/0x9A deliberately unreachable in code.

## 5. What's built (all committed + pushed)

Repo: **github.com/umarabdullah23/jbl-quantum-engine-linux** (public, MIT).
Working copy: `~/Documents/Projects/jbl-quantum-linux`.

- `app/jbl_quantum.py` — library: hidapi discovery, verified reports only, undo registry
  (first-write-wins), safety clamps.
- `app/jblq` — CLI: probe/battery/dial/info/sidetone/anc/lights/autooff/restore/listen.
- `app/jblq_daemon.py` — hotplug-aware daemon, unix socket `$XDG_RUNTIME_DIR/jblq.sock`,
  JSON `{cmd: state|refresh|set}`; set supports sidetone/anc/lights/auto_off/light_zone/
  light_colour.
- `app/jblq_gui.py` — **PyQt6 replica of the real QuantumENGINE UI** (built from frame
  studies of YouTube walkthroughs + the app's own binary strings): top status bar
  (VOLUME/MICROPHONE/CHAT··GAME dial dots/SPATIAL/ANC/BATTERY icon/CONNECTED TO),
  JBL QUANTUM810 logo row + hatch strip + working USER PROFILES
  (`~/.config/jblq/profiles.json`, ✎ save / 🗑 delete), left rail (EQUALIZER/LIGHTING/
  SPATIAL SOUND/MICROPHONE/SYSTEM SOFTWARE/HELP + extra NOISE CANCELLING), EQ page
  (draggable 10-bar canvas, dB scale, preset dropdown with curve thumbnails, custom save ✓,
  red headset wireframe), LIGHTING (presets BREATH…RISE/OFF, ADVANCED MODE + SYNC ALL LIGHTS
  toggles, LOGO/RING colour-gradient + SPEED + TEMPO), SPATIAL (DTS logo card), MIC page,
  SYSTEM SOFTWARE (fw/serial/auto-off/restore), HELP (credits). DEMO pill + amber banner.
- `app/install.sh` — user install (`~/.local/bin/jblq*`, app-menu .desktop, icon, udev
  rule via sudo), `--uninstall`. Version APP_VERSION="1.0.0".
- Known crash fixed late: missing QFrame import (verify after any GUI edit with
  `python -m py_compile` AND an actual launch + `ps` check — pgrep self-matches!).

## 6. Environment gotchas (this machine)

- GUI needs `DISPLAY=:0` and PyQt6 from `~/jbl-re/venv` (system python lacks it).
  Launch via ZCode background task (`run_in_background`), NOT nohup+disown (it dies with
  the shell). Verify with `ps aux | grep jblq_gui.py`, not pgrep -f (self-match).
- hidapi built from source: `~/jbl-re/lib/libhidapi-hidraw.so` (no sudo for apt) → run
  CLI/daemon with `LD_LIBRARY_PATH=$HOME/jbl-re/lib ~/jbl-re/venv/bin/python …`.
- Offline hives + JBL DLL copies + string dumps + Ghidra/JDK25: `~/jbl-re/` (NOT committed).
- Windows drive must stay read-only (owner rule).

## 7. Pending / next steps

1. **Live verification** — dongle not yet plugged into Linux. Procedure: `jblq probe`
   (read-only) → one setter at a time with read-back → log results in PROGRESS.md.
2. **PipeWire EQ/surround** (the real missing feature) — host-side filter-chain wiring;
   community curves: alessandromrc/jbl-quantum-4-linux; our EQ_CURVES are approximations
   except WARZONE (community-exact: 31+5 62+2 125+2 250+4 500+5 1k+1 2k+2 4k+5 8k+9 16k+10).
3. Optional: extract exact EQ curves from QuantumENGINE's own configs (AppData search came
   up empty — the user's Windows account barely used the app).
4. Optional: Bluetooth Airoha GATT (RACE-over-BLE) support; advanced hue-wheel lighting
   editor; AA passthrough gain (RACE-level, needs capture evidence).
5. Owner UX asks already done: repo renamed jbl-quantum-engine-linux; demo mode; UI
   replicated; installer. Owner asked "answer first: self-RE vs open source?" → answer
   given (protocol = community + our independent capture verification; implementation ours).

## 8. Key decisions log

- Adapted Phase A (Windows USBPcap) → used SWW13's public captures instead (no Windows
  capture box; same machine dual-boot, Windows side off-limits for running).
- Phase C (Ghidra) deprioritized: protocol fully known; binary RTTI inventory enough.
- No secrets in repo; no JBL binaries committed; captures are public-attachment copies.
- UI: replicate real app look (not "gaming style") — owner explicitly rejected gaming UI.
- Every non-verified control is labeled host-side/pending in the UI; demo mode never sends.

## 9. Deep RE round 2 (added 2026-10-31 late)

- Full Ghidra decompile of AirohaHidCoreLib.dll landed. **PROTOCOL-RACE.md** is the new
  authoritative RACE doc; highlights: 119 RACE command IDs (reverse-engineering/strings/race_cmd_table.txt),
  relay envelope = ASCII brackets + resp type 0x5D + relay race ID 0x0D01,
  **NO encryption anywhere in the config channel** (plaintext; verified string+decompile).
- Lighting 0x4C byte2 = BRIGHTNESS (40/50/60/70/75/80/100), not speed — fixed across
  GUI/daemon/library; effect speed = 0x4D tail byte (GUI "SEG PARAM" 0–8).
- Missing features (mic volume, chat-balance SET, voice guidance, wear detection,
  notification tone, busy light, factory reset, AA gain) now have RACE unlock paths
  documented — ALL stay fail-closed in the daemon until each is live-captured + verified.

## 10. Repo layout (restructured 2026-10-31)

`app/` = the application (CLI/daemon/GUI/installer/udev) · `docs/` = protocol docs, evidence, captures · `reverse-engineering/` = decompile dumps, string dumps, UI-ref frames, scripts (its `binaries/` is gitignored — JBL proprietary, local only).

## 11. UI v1.1 (current QuantumENGINE design)

- Old v1 GUI (2.x black layout from YouTube videos) kept as app/jblq_gui_v1_legacy.py.
- v1.1 = app/jblq_gui.py: rebuilt to the CURRENT app design, studied frame-by-frame from
  the official JBL showcase videos (downloaded from jbl.com/quantum-engine media, saved in
  ~/jbl-re/newui/): left icon rail with circular avatars, User Profile pill, rounded cards
  with purple preset pills, magenta EQ curve card, Audio/Voice Monitor mic card, hero
  headset with ambient rings. DEMO = rail button "D" + amber pill/banner.
