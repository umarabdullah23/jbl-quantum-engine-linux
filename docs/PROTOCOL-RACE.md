# RACE layer (deep RE) — QuantumENGINE's AirohaHidCoreLib.dll

Evidence tags: **[DECOMP]** = Ghidra 12.2 decompile of the installed QuantumENGINE 2.8.6
`AirohaHidCoreLib.dll` (dumps in `reverse-engineering/decomp/`: `decomp_features.c`, `decomp_race_frame.c`;
full dump kept locally, 11MB). **[RTTI]** = binary type/strings. **[INFERENCE]** = needs
live confirmation on the headset.

## 1. Is there encryption? — NO [DECOMP + strings]

Full string sweep of every device-logic binary (`AirohaHidCoreLib`, `HIDDevice`,
`USBDevice`, `DeviceDiscovery`, `quantum_engine`): **zero** occurrences of
encrypt/decrypt/AES/cipher/HMAC/CRC/obfuscation. The HID config channel is plaintext:

- The verified feature reports (0x45–0x75) carry raw bytes (community protocol works
  byte-transparently).
- The RACE layer is envelope-framing only — no crypto anywhere in the decompile. The only
  "hidden" structure is framing, documented below. Nothing to remove: there is no
  encryption layer on the configuration path. (Firmware/DFU signing was never examined —
  out of scope by design.)

## 2. Relay envelope (dongle path) [DECOMP]

The dongle wraps inner RACE packets in an ASCII-bracket envelope. The response parser
(`respParser`, `decomp_race_frame.c`) enforces:

- a `]` closing marker (and `[…` opening),
- relay resp **type byte `0x5D`** ("wrong relay resp type, expected 0x5D"),
- 2-byte LE **relay race ID `0x0D01`** ("wrong relay resp race ID, expected 0x0D01"),
- a length check ("wrong relay resp length"),
- everything after the header is copied out as the inner RACE packet.

[INFERENCE] Request direction uses the mirrored envelope with the same delimiters.

## 3. RACE command ID table — COMPLETE [DECOMP]

Recovered from the app's own command-name lookup switch (119 entries). Full list:
`reverse-engineering/strings/race_cmd_table.txt`. Highlights relevant to the 810's missing features:

| cmd | name | maps to |
|---|---|---|
| 0x04/0x05/0x06 | GET_ALL_EQ_SETTINGS / GET_RUNNING_EQ_SETTINGS / SET_EQ_SETTINGS | on-device EQ (Airoha DSP path — the BT/adaptive side; the 810 dongle exposes no EQ feature report) |
| 0x09 | GET_BATTERY_INFO | battery detail |
| 0x0A/0x0B | GET/SET_ANC_SETTINGS | ANC incl. per-mode gains |
| 0x0E/0x0F | GET/SET_AUTO_POWER_OFF_STATUS | auto-off (we already have simple report 0x75) |
| 0x1B/0x1C | GET/SET_SIDETONE_STATE | sidetone on/off (level = 0x32/0x33) |
| 0x1F | SET_FACTORY_RESET | **factory reset — real app has it (FactoryReset IPC)** |
| 0x20/0x21 | GET/SET_VOICE_PROMPTS_STATUS | voice guidance prompts |
| 0x22/0x23 | GET/SET_SOUND_MAX_VOLUME | max-volume limiter |
| 0x24/0x25 | GET/SET_ADVANCED_PASSTHROUGH_STATUS | ambient-aware gain path |
| 0x26–0x28 | ENVIRONMENT_DETECTION_* | adaptive ANC environment handling |
| 0x29/0x2A | GET/SET_ADAPTIVE_ANC_STATUS | adaptive ANC |
| 0x2B/0x2C | GET/SET_ADAPTIVE_EQ_STATUS | adaptive EQ |
| 0x32/0x33 | GET/SET_SIDETONE_LEVEL | sidetone level |
| 0x35/0x36 | GET/SET_GAME_CHAT_BALANCE_SETTINGS | **game/chat balance SET** (our GUI reads dial 0x62 only) |
| 0x4B/0x4C | GET/SET_DONGLE_MODE | dongle mode (ULL2 etc.) |
| 0x52/0x53 | GET/SET_WEAR_DETECTION_MIC_ONOFF | wear detection |
| 0x54/0x55 | GET/SET_BUSY_LIGHT_STATUS | busy light |
| 0x56/0x57 | SET/GET_UC_PROFILE | user profile sync to device |
| 0x59/0x5A | GET/SET_NOTIFICATION_ACTIVATION | notification tone on/off |
| 0x5B | GET_NOTIFICATION_MAP | per-app notification map |
| 0x5E/0x5F | GET/SET_VOICE_GUIDANCE | voice guidance |
| 0x60 | SET_AINR_STATUS | AI noise reduction (mic) |

Notes:
- The setter classes named `SetGameMicVolume`/`SetGameChatMixRatio`/`SetStandAloneMicVolume`
  [RTTI] funnel through the same schedule API; their exact RACE IDs are among the above
  (0x35/0x36 for chat balance; mic volume likely a payload variant) — [INFERENCE] pending
  live capture.
- Third argument in the name lookup = log-string length, NOT payload length. Payload
  layouts need live USB captures per command — document from device, never guess-send.

## 4. Lighting byte-2 correction (0x4C) — upgrades PROTOCOL.md §2

sidmax7's comment ("per-zone brightness and slot count") + QuantumENGINE's boot write
`4c 00 64 05` (=100%) agree: **0x4C byte2 = BRIGHTNESS %**, allowed values
{40, 50, 60, 70, 75, 80, 100} (0x28/0x32/0x3C/0x46/0x4B/0x50/0x64) — taron-sys's "speed
set" misread the same allowlist. Effect speed lives in the 0x4D colour frame's tail byte
(per-segment parameter 0–8). Our tool now: `light_zone = {element, brightness, segments}`;
GUI slider labelled BRIGHTNESS; effect speed = SEG PARAM on 0x4D.

## 5. Missing-feature unlock map (needs live verification before ANY send)

| Feature | Simple report? | RACE path | Plan |
|---|---|---|---|
| Game/chat balance SET | none (0x62 read-only) | 0x36 | capture SET from QuantumENGINE, verify read-back, then implement |
| Mic volume (game/standalone) | none | RACE (variant TBD) | same |
| Voice guidance on/off | none | 0x5E/0x5F | same |
| Wear detection | none | 0x52/0x53 | same |
| Notification tone on/off | none | 0x59/0x5A | same |
| Busy light | none | 0x54/0x55 | same |
| Factory reset | none | 0x1F | same (destructive — snapshot first) |
| AA passthrough gain | none | 0x24/0x25 | same |

Until each is captured and read-back-verified, these stay OUT of the daemon's `set`
surface (fail-closed) — only documented here.
