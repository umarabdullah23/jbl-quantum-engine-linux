# reverse-engineering/ — RE working files

Tracked: our own analysis outputs (string dumps, UI-reference frames, scripts).
Gitignored (NEVER push): `binaries/` — JBL proprietary binaries + installer, kept locally
for reference only. Windows registry hive copies are NOT stored here at all (they contain
machine secrets); they live only in ~/jbl-re/hives on this machine.

- `binaries/` (ignored — local only) — DLL/EXE copies from the installed QuantumENGINE 2.8.6 + installer
- `strings/` — string/RTTI dumps: airoha_strings*.txt (AirohaHidCoreLib), *_s.txt (other
  device DLLs), Languages.en.json (UI string table)
- `ui-ref/` — frames from public YouTube walkthroughs of the real app (layout reference)
- `decomp/` — Ghidra decompile dumps (features + RACE framing)
- `scripts/`→`tools/` — our analysis scripts (find_xrefs, byte_xref, usbpcap_parse)
