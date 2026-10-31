# -*- mode: python ; coding: utf-8 -*-
# PyInstaller spec — JBL Quantum Engine (Windows edition)
# Build:  pyinstaller jblq_win.spec --noconfirm   (from app/windows/)
import os

block_cipher = None
HERE = os.path.abspath(SPECPATH)
APP_PARENT = os.path.dirname(HERE)  # app/ — holds the shared engine jbl_quantum.py

a = Analysis(
    ['jblq_win.py'],
    pathex=[HERE, APP_PARENT],          # so `from jbl_quantum import ...` resolves
    binaries=[],
    datas=[(os.path.join(HERE, 'vendor', 'SoundVolumeView.exe'), 'vendor'),
           (os.path.join(HERE, 'vendor', 'SoundVolumeView-LICENSE.txt'), 'vendor')],
    hiddenimports=['jbl_quantum',       # the shared engine must never be missed
                   'spatial_win',       # real host-side spatial sound module
                   'pycaw', 'pycaw.pycaw',          # volume control (lazy imports in
                   'comtypes', 'comtypes.client'],  # _volume_popup — explicit, verified
                                                    # by `exe --selftest` pycaw_ok
    hookspath=[],
    hooksconfig={},
    runtime_hooks=[],
    excludes=['tkinter'],
    cipher=block_cipher,
    noarchive=False,
)
pyz = PYZ(a.pure, a.zipped_data, cipher=block_cipher)

exe = EXE(
    pyz,
    a.scripts,
    a.binaries,
    a.zipfiles,
    a.datas,
    [],
    name='JBLQuantumEngine',
    debug=False,
    bootloader_ignore_signals=False,
    strip=False,
    upx=False,
    upx_exclude=[],
    runtime_tmpdir=None,
    console=False,                       # windowed app
    disable_windowed_traceback=False,
    argv_emulation=False,
    target_arch=None,
    codesign_identity=None,
    entitlements_file=None,
    icon='jblq_icon.ico',
)
