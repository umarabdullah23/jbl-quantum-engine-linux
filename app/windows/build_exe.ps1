# Build JBLQuantumEngine.exe (Windows edition) — one-file, windowed.
# Usage:  powershell -ExecutionPolicy Bypass -File build_exe.ps1
$ErrorActionPreference = "Stop"
$here = Split-Path -Parent $MyInvocation.MyCommand.Path
Set-Location $here

python --version
pip show pyinstaller >$null 2>&1
if ($LASTEXITCODE -ne 0) { pip install pyinstaller }
pip show PyQt6 >$null 2>&1
if ($LASTEXITCODE -ne 0) { pip install PyQt6 }
pip show hidapi >$null 2>&1
if ($LASTEXITCODE -ne 0) { pip install hidapi }

Write-Host "==> generating icon" -ForegroundColor Cyan
python make_icon.py
if (-not (Test-Path "$here\jblq_icon.ico")) { throw "icon generation failed" }

Write-Host "==> compile check" -ForegroundColor Cyan
python -m py_compile jblq_win.py ..\jbl_quantum.py

Write-Host "==> pyinstaller" -ForegroundColor Cyan
python -m PyInstaller jblq_win.spec --noconfirm --clean
if ($LASTEXITCODE -ne 0) { throw "pyinstaller failed" }

$exe = "$here\dist\JBLQuantumEngine.exe"
if (-not (Test-Path $exe)) { throw "exe missing: $exe" }
$size = "{0:N1} MB" -f ((Get-Item $exe).Length / 1MB)
Write-Host "OK: $exe ($size)" -ForegroundColor Green
