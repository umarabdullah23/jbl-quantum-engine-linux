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

## 12. Session log (kept in sync — newest last)

- 2026-10-31 (final): repo restructured (app/ · docs/ · reverse-engineering/); UI v1.1
  shipped + running (official showcase videos = UI reference, frames in ~/jbl-re/newui/);
  everything pushed through commit "v1.1 UI". APP_VERSION = 1.1.0.
- Standing instruction from owner: **keep this file synced with the session after each
  round** ("also keep syncing current chat md file"). Owner said live verification happens
  LATER ("just push code, verify live later").
- Where things stand at sync time: working tree clean on main; daemon + GUI v1.1 running
  in demo mode (GUI via ZCode background task, DISPLAY=:0, venv python); dongle not yet
  plugged into Linux.
- Sync procedure for future rounds: append a dated line here + update §7 (pending) +
  docs/PROGRESS.md, commit, push. Memory file
  (gameloop-optimizer project memories: jbl-quantum-engine-linux-project.md) mirrors the
  big state too.

## 13. LIVE VERIFIED (2026-11-01)

Dongle attached; udev rule installed (plugdev). **All simple reports 0x45–0x75 verified
on the real headset — probe 8/8 + every setter with read-back + restore** (see
docs/PROGRESS.md 2026-11-01 entry). ANC needs ~1.5 s settle after SET before mirror-read.
Bugs fixed live: dual hidapi binding, daemon access-denied survival, snapshot int/bytes.
Remaining: RACE-command unlock round (PROTOCOL-RACE.md §5) — needs QuantumENGINE running
on the Windows side with USBPcap to capture per-command SET payloads, or send via our
tool once payloads are known. PipeWire EQ wiring still open.

## 14. Live session fixes (2026-11-01, round 2)

- Daemon REWRITTEN cleanly: state reads are lock-free (atomic dict swap — a wedged
  monitor can never block clients), snapshot() outside locks, EventStream no longer
  re-opens the control hidraw, handler timeout 5 s, catch-all answers. Root cause of the
  "daemon unreachable: Resource temporarily unavailable" the owner saw: earlier sed patches
  had left a NameError in the refresh path (`hs.get_mic_active()`) which killed handler
  threads → all future connects answered nothing.
- Charging: dongle does NOT report charging (fact — 0x49 byte2 is always 0x00, verified
  over multiple samples). Implemented INFERENCE: battery trend rising → "⚡ charging*"
  (sticky until a decrease or 100%), labelled inferred in the GUI.
- Dongle re-enumerates when the headset sleeps/wakes (device address changes) — callers
  must re-enumerate; the daemon handles it via its 2 s retry loop.

## 15. Owner switching to WINDOWS (2026-11-01) — next phase there

Owner is taking the headset/dongle to Windows. Linux side state at handoff:
- All simple reports 0x45–0x75 LIVE-VERIFIED (docs/PROGRESS.md 2026-11-01 entries).
- Daemon v2 (lock-free rewrite) + GUI v1.1 running; dongle unplug → app shows
  "no headset detected" (expected, it re-detects on replug).
- Battery/charging: 0x49 has NO charging flag byte (always 0x00 — verified); GUI shows
  "⚡ charging*" from battery-trend inference.

### Windows-phase plan (RACE unlock round — the missing features)
1. Install USBPcap + Wireshark on Windows (read-only capture).
2. With QuantumENGINE 2.8.6 running, capture SEPARATELY, one action per file, device idle
   before/after: game/chat balance SET (dial drag), mic volume change, voice guidance
   on/off, wear detection on/off, notification tone on/off, busy light (if exposed),
   AA/passthrough gain, factory reset (LAST, destructive), PEQ edit (BT mode if used).
   Name each file by action.
3. Copy the pcapngs into docs/captures/ (public-machine captures, no secrets).
4. Decode with docs/captures/usbpcap_parse.py (SET_REPORT on interface 5) — RACE packets
   sit inside the relay envelope (ASCII brackets, resp type 0x5D, relay race ID 0x0D01 —
   see docs/PROTOCOL-RACE.md §2). Extract per-feature RACE cmd IDs + payload bytes.
5. Cross-check cmd IDs against reverse-engineering/strings/race_cmd_table.txt (119 cmds).
6. Implement in app/jbl_quantum.py ONE command at a time: capture-fact payload → send →
   read-back verify → only then add to daemon `set` surface (fail-closed until proven).
7. Windows also needs the dual-host note: dongle links to whichever host it is plugged
   into; QuantumENGINE on Windows will reconnect automatically.

Remember: no firmware/DFU flows; one write at a time; stop on re-enumeration/glitch and
record DO-NOT-SEND. Push every round; keep this file synced (standing instruction).

## 16. WINDOWS APP SHIPPED (2026-11-01) — `app/windows/`, exe built

Owner brought the headset to Windows and asked to "continue its tasks for windows, and its
ui — see E:\quantum engine pics … complete this app" + "make exe app too".

- **`app/windows/jblq_win.py`** — PyQt6 Windows edition, UI rebuilt to the REAL
  QuantumENGINE Windows screenshots (frameless dark window + custom titlebar, left avatar
  rail, MY PRODUCTS home with banner + product card, device dashboard with the 6 cards
  (EQUALIZER / SPATIAL SOUND / MICROPHONE / AMBIENT SOUND CONTROL / LIGHTING / SUPPORT),
  spatial detail page (mode segmented, dts card, room size + head diameter, head-sphere
  "output channel: 7.1", reset), EQ detail (draggable curve + presets + custom save),
  mic detail (side tone 4-step verified, gain fail-closed pending), lighting detail
  (presets, LOGO/RING hue, brightness steps, seg param, sync-all), support (fw/serial/
  auto-off/restore), settings, and the 5-step onboarding tour with Skip (persisted flag,
  replayable from Settings).
- **No daemon on Windows.** `DeviceWorker(QThread)` owns the control-HID handle; all HID
  I/O is queued jobs so a wedged feature-report can never freeze the UI (same bug class
  the daemon rewrite fixed, see §14). Re-enumeration (headset sleep/wake) self-heals on
  the next 2 s tick. Charging inference (§14) ported into the worker.
- **Same shared engine** — imports `app/jbl_quantum.py` unchanged; Windows HID topology
  confirmed: dongle enumerates as ONE HID collection (MI_05, usage 0xFF13,
  "…Quantum810 Wireless Chat") and `find()` passes unmodified. Verified LIVE on Windows
  before writing any UI: probe snapshot read battery 30 / ANC on / serial / fw on the
  real dongle. Real QuantumENGINE (`JBLQuantumControl.exe`) running concurrently did NOT
  block our handle (Windows shared access), but README tells users to close it (writers
  can race).
- **System volume** via pycaw (popup slider from the dashboard volume label); Linux used
  pactl. Honesty rules carried over: only verified 0x45–0x75 reports are sent; EQ/spatial
  /mic-gain are host-side, labelled, saved to `%LOCALAPPDATA%\jblq\profiles.json`.
- **Exe:** `app/windows/build_exe.ps1` → `dist/JBLQuantumEngine.exe` (~49 MB onefile,
  windowed, drawn multi-size `jblq_icon.ico` — no JBL artwork; PIL's ICO writer only
  downsizes the base image, so the ico container is written manually — keep that).
  `jblq_win.spec` lists `jbl_quantum` as an explicit hiddenimport. Boot verified for the
  packaged exe.
- **UI verified offscreen** (every page rendered to PNG via `widget.grab()` with the
  window minimized — do NOT fullscreen-grab the owner's screen; a game was running).
  Fixed during verification: main column was missing its dark background, hero had no
  sizeHint (invisible), demo mode didn't prime the dashboard battery.
- Windows requirements: `app/windows/requirements.txt` (PyQt6, hidapi wheel — the bare
  `hid` package does NOT bundle hidapi.dll on Windows; pycaw/comtypes optional).
- **Still open (unchanged from §15):** RACE unlock round needs USBPcap captures on
  Windows (QuantumENGINE 2.8.6 is installed here — one action per capture, name by
  action, decode with docs/captures/usbpcap_parse.py) to unlock mic gain, chat balance
  SET, voice guidance, wear detection, notification tone, factory reset, AA gain.
  Real DTS/Quantum Spatial output needs the licensed host APO — our app saves the mode
  locally and says so in the UI.

### 16b. Windows round 2 — owner report "some things aren't working" → root-caused + all features verified (2026-11-01)

Owner: "i think some things arent working, e.g quantum engine and dts switch — fix it, and
see everything if works or not." Method: offscreen FUNCTIONAL TEST (synthesized mouse
events on every control, device attached) + a full §13-style live read-back round.

- **Bug 1 (big): `_hue_rgb` was never ported** from the Linux GUI — every lighting-COLOUR
  write (preset pick, LOGO/RING hue slider) crashed with AttributeError → "write failed".
  This is the real "doesn't work" behind the lighting card. Fixed.
- **Bug 2: side-tone StopSlider sent the LABEL string** ("HIGH") to the engine instead of
  the level int → refused (`invalid literal for int()`). StopSlider callbacks now always
  use the index; labels are display-only. Fixed.
- **Bug 3: successful writes were SILENT** — only failures flashed. A working switch read
  as "nothing happened". Every successful device write now flashes "feature applied ✓"
  (green) in the status bar. Standing rule: a control that works must SAY so.
- Spatial Quantum-Spatial/DTS switch verified WORKING as designed: it is host-side
  (dongle receives nothing — capture-proven fact), saves locally, and now gives visible
  feedback. Real Windows-Sonic wiring was researched (EarTrumpet issue #212 route =
  undocumented ISpatialAudioFormat COM) — deliberately NOT shipped blind.
- **Live read-back round on the real dongle: 13/13 PASS** — ANC 0/1/2 (1.5–2 s settle;
  a 1.6 s wait once raced the settle and read stale — wait ≥2 s or poll), sidetone 1/3/0,
  lights off/on, colour frames accepted, light-zone 80%/5, segments=6 refused (hardware
  safety), auto-off 30 min read-back. Device restored to session-start state afterwards
  (anc on, sidetone off, lights off, auto-off 30 min). GOTCHA: restoring after tests
  captures the TEST value as "original" — always restore from the session's FIRST probe.
- Rebuilt exe (02:09) + boot verified.

### 16c. Windows round 3 — the REAL "lighting first time doesn't work" root cause (2026-11-01)

Owner: "LIGHTING if off work then after that works true, first time issue only."
- **Root cause 1:** the dashboard LIGHTING card toggle was created checked=ON always and
  was NEVER synced with device state (`_apply_state` only synced the detail-page toggle).
  With lights actually OFF at boot, the owner's FIRST click moved the widget to OFF and
  sent set_lights(False) into an already-off device = visible no-op. The second click
  sent ON and worked — exactly "first time issue only". Fix: both lighting toggles now
  sync from device truth every state tick (`_lights_on_state` mirrors the device).
- **Root cause 2 (belt+braces):** a 0x4D colour frame sent immediately after master-on
  can be dropped by the lighting MCU (it boots with the master switch). `_light_preset`
  now delays the colour frames ~400 ms when lights were off, and `_zone_colour` turns
  the master ON first when it is off (choosing a colour = intent to light up).
- Verified by reproducing the owner's exact flow against the real dongle: boot with
  lights OFF → toggle syncs OFF → FIRST click → device read-back lights=1 → preset
  applied ✓ → restored lights=0. Exe rebuilt + boot verified.
- RULE (add to every UI port): any widget showing device state must be initialised FROM
  the device's first state tick, never from a hardcoded default.
