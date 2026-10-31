#!/usr/bin/env bash
# install.sh — install JBL Quantum Engine (Linux) for the current user.
#   ./install.sh          install (user-level, no root needed except udev rule)
#   ./install.sh --uninstall
set -euo pipefail
HERE="$(cd "$(dirname "$0")" && pwd)"
PREFIX="${HOME}/.local"
APPDIR="${PREFIX}/share/jbl-quantum"
BIN="${PREFIX}/bin"
DESKTOP="${PREFIX}/share/applications"

if [[ "${1:-}" == "--uninstall" ]]; then
  rm -rf "$APPDIR" "${BIN}/jblq" "${BIN}/jblq-daemon" "${BIN}/jblq-gui" \
     "${DESKTOP}/jbl-quantum.desktop" "${PREFIX}/share/icons/hicolor/scalable/apps/jbl-quantum.svg"
  sudo rm -f /etc/udev/rules.d/99-jbl-quantum.rules 2>/dev/null || true
  echo "uninstalled."
  exit 0
fi

mkdir -p "$APPDIR" "$BIN" "$DESKTOP" "${HOME}/.config/jblq"
install -m 0644 jbl_quantum.py jblq_daemon.py jblq_gui.py "$APPDIR/"
install -m 0755 jblq "$APPDIR/jblq"
# CLI wrappers
cat > "${BIN}/jblq" <<EOF
#!/usr/bin/env bash
exec python3 "${APPDIR}/jblq" "\$@"
EOF
cat > "${BIN}/jblq-daemon" <<EOF
#!/usr/bin/env bash
exec python3 "${APPDIR}/jblq_daemon.py" "\$@"
EOF
cat > "${BIN}/jblq-gui" <<EOF
#!/usr/bin/env bash
exec python3 "${APPDIR}/jblq_gui.py" "\$@"
EOF
chmod +x "${BIN}/jblq" "${BIN}/jblq-daemon" "${BIN}/jblq-gui"
# icon (neutral headphone mark, our own)
cat > "${PREFIX}/share/icons/hicolor/scalable/apps/jbl-quantum.svg" <<'EOF'
<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 64 64">
  <rect width="64" height="64" rx="12" fill="#e8262d"/>
  <path d="M14 40 v-6 a18 18 0 0 1 36 0 v6" stroke="#fff" stroke-width="5" fill="none"/>
  <rect x="10" y="38" width="10" height="14" rx="3" fill="#fff"/>
  <rect x="44" y="38" width="10" height="14" rx="3" fill="#fff"/>
</svg>
EOF
# desktop entry
cat > "${DESKTOP}/jbl-quantum.desktop" <<EOF
[Desktop Entry]
Type=Application
Name=JBL Quantum Engine (Linux)
Comment=Control JBL Quantum wireless headsets (Quantum 810 verified)
Exec=${BIN}/jblq-gui
Icon=jbl-quantum
Categories=Audio;Settings;Utility;
Keywords=JBL;Quantum;headset;ANC;sidetone;
Terminal=false
EOF

# udev rule (needs sudo; skipped gracefully if unavailable)
if sudo -n true 2>/dev/null; then
  install -m 0644 udev/99-jbl-quantum.rules /etc/udev/rules.d/ 2>/dev/null \
    && sudo udevadm control --reload 2>/dev/null && echo "udev rule installed." \
    || echo "NOTE: udev rule not installed (no sudo) — install manually:"
else
  echo "NOTE: udev rule needs sudo — run manually:"
fi
echo "  sudo cp ${HERE}/udev/99-jbl-quantum.rules /etc/udev/rules.d/ && sudo udevadm control --reload"

# dependency hints
python3 -c "import hid" 2>/dev/null || echo "NOTE: python hidapi missing — sudo apt install python3-hidapi (or pip install hid)"
python3 -c "import PyQt6" 2>/dev/null || echo "NOTE: PyQt6 missing — pip install PyQt6 (or apt install python3-pyqt6)"

echo
echo "installed:"
echo "  ${BIN}/jblq           CLI   (jblq probe / battery / anc on …)"
echo "  ${BIN}/jblq-daemon    daemon (hotplug-aware, unix socket)"
echo "  ${BIN}/jblq-gui       app (this also appears in your app menu)"
