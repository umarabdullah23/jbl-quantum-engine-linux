# PROTOCOL-QEIPC.md — QuantumENGINE's host-side DSP control channel (RE in progress)

Goal: drive the REAL JBL spatial DSP (DTS Headphone:X + HX3D "Quantum Spatial" /
"JBL 3D effect & Equalizer") from OUR app, exactly like QuantumENGINE does — with zero
endpoint changes (emulator-safe). This file is the round-1 recon map (2026-11-01) so the
next round starts here, not from zero.

## 1. The architecture (verified on this machine)

```
QE UI (JBLQuantumControl.exe, .NET MAUI)
   │  TCP 127.0.0.1:14025 (framed request/response, silent — no banner)
   ▼
QuantumServer.exe  (service, PID varies)
   │  shared memory (CreateFileMappingA, "Global\…") + named pipes
   ▼
SpatialAPO.dll  ("JBL 3D effect & Equalizer", CLSID {3D640EF5-6952-3BE3-9ED4-D2D20BC847B3})
   │  registered as PostMixClsid/EndpointEffectClsid on the Game endpoint's FxProperties
   │  (INF oem7.inf [FxEffect.Game.SpatialAPO.AddReg]; bypass APO {3609DE9C-…} = PreMix/Stream)
   ▼
HarmanFilter.sys  ("HarmanAudioService" kernel driver, RUNNING, KMDF,
                   quantumusbaudio.inf, upper filter on USB\VID_0ECB&PID_2069&MI_00)
```

- The APO stack lives in `C:\Windows\System32\JBLQuantumENGINE\apo\`:
  `SpatialAPO.dll`, `BypassAPO.dll`, `HX3DMagic.dll` + `HX3DSystem*.bin` (DTS:H3D),
  **`dts/` = real DTS Headphone:X v2** (`dtsapo64.dll`, `dtscnt64.dll`, `dtstech64.dll`,
  `dts-eagle.lic` licence, `dts_apo4_hpxv2_oem_config.xml`, `dts_hpeq_48k.bin`),
  `qeSpatial.bin` (18 MB spatial data), `EqConfig-Q810.xml` (real JBL Q810 EQ),
  `ShareMemory.dll`/`IPC.dll` (the IPC layer), `SoundEffect.dll`, `quantum_engine.dll`.
- **Why QE never disturbs the emulator:** the DSP is a permanent endpoint effect; QE
  only changes its MODE (shared-memory message), never the endpoint format/identity.
- **Why no APO shows in AudioEngine\AudioProcessingObjects:** the APO is registered per-
  endpoint in FxProperties (HKR FX\0), not globally.
- FxProperties subkeys {45da5c30-…}/{08e54ab7-…} exist (Default/User/Volatile) but were
  EMPTY at runtime — live state is in shared memory, not the registry.

## 2. What QE's managed assemblies expose (JBLQuantumControl.dll, 3622 types)

Decompilable .NET (use ILSpy — NOTE: ilspycmd failed to run on this box, .NET 6 missing;
use a version matching installed runtimes (net7/net8) or another decompiler).

Spatial enums (decoded from metadata constants):
- `QESE.HXSpatialMode`: 0=MODE_BYPASS, 1=MODE_STATIC_SURROUND, 2=MODE_DYNAMIC_SURROUND,
  **3=MODE_DTS_SURROUND**   (HX = HX3D = the "Quantum Spatial" engine)
- `QESE.AESpkSpatialMode`: 0=bypass, 1=static, 2=dynamic (AE = AudioEndpoint path)
- `QECommon.HIDV3_SPATIAL_SOUND_MODE`: ENABLE_MASK=0x80, MODE_MASK=0x7F
- Structure types: `SPATIAL_SOUND_MODE{ProviderType, Mode}`,
  `HX_SPATIAL_SOUND_TYPE{eCur, ePrev}`, `AE_SPATIAL_SOUND_TYPE{eCur, ePrev}`,
  `HX_SPATIAL_INFO`, `AESpkSpatialAudioScene`, `Hx3DSpatialEffect`, `AESpatialEffect`

Property classes (pub/sub over the TCP protocol), each with
GetMsgID/SetMsgID/NotifyMsgID/GetRespMsgID/SubscribeMsgID/UnsubscribeMsgID fields:
`AESpatialEnableProp`, `HXSpatialSoundTypeProp`, `AESpatialSoundTypeProp`,
`HXSpatialSoundTypeProf`/`AESpatialSoundTypeProf` (ID+NAME descriptors),
`OverlaySpatialSoundModeProp`, `HIDV3SpatialSoundModeProp` (+Recenter),
`SupportEqualizerProp`, `ProductUACModeProp`, `FactoryResetProp`, `RebootProp`, …
(ctor IL chains to a base — message IDs are in the base classes / descriptors, NOT the
ctor; next step is decompiling the base + `QECommon.IPCPath`, `QEIPC.Client`.)

The DSP command API (quantum_engine.dll strings): `setSpkDspMode`, `setSpkUserEQ`,
`calcSpkUserEQCoefs`, `setSpkDeviceEQ`, `setSpatialAudioHeadPosition`,
`setSpatialAudioScene`, "Spatial sound mode changed: from 0x%x to 0x%x",
"HMDSP_CMD", "DSP working mode: %d(0:Normal, 1:HWTEST, 2:bypass)",
"Can't open qeSpatial data file".

IPC layer (IPC.dll / ShareMemory.dll strings): request/response with
"Start request, Request ID=%d %ls" / "Finish request, Request RequestID=%d",
per-property Subscribe/Unsubscribe/Notify, `QESMCreateShareMemory` family,
CreateFileMappingA/PeekNamedPipe. Client re-use: "Client exist, re-use it(%d)".

## 3. Next steps (in order)

1. Decompile `JBLQuantumControl.dll` (ILSpy on a machine with .NET 6, or decompile the
   QE `QECommon.*` + `QEIPC.*` assemblies) → exact frame format (length prefix? msg id
   width?), message-ID table for the spatial/EQ properties, payload schemas.
2. Mirror-listen: connect to 127.0.0.1:14025 as a second client, subscribe to the
   spatial properties, and READ while the owner toggles spatial in QE → verify decode
   passively before ever sending (fail-closed: read-only first, like the Linux HID
   round).
3. Only then: send the same Set request the QE UI sends (HXSpatialSoundType /
   AESpatialEnable with mode 0–3) → REAL DTS + REAL Quantum Spatial from our app,
   endpoint untouched. Wrap in the same verify-then-enable ladder as the HID work.
4. Bonus (same APO): `SupportEqualizerProp` + `setSpkUserEQ` = REAL host-side EQ with
   JBL's own filter chain — replaces our "EQ is host-side, saved locally" limitation.
   `EqConfig-Q810.xml` gives JBL's real device correction curves.
5. Fall back gracefully when QuantumServer isn't running (QE uninstalled): keep the
   current Windows-Sonic path as the documented fallback.

## 4. Safety rules (unchanged)

Read-only first; never send a frame whose response semantics we haven't observed; stop
on any audio glitch; document every message in this file as it's proven. No firmware
flows. The dongle HID side stays exactly as verified (docs/PROTOCOL.md).
