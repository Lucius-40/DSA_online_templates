@echo off
powershell -Command "Get-ChildItem -Path '%~dp0' -Filter '*.exe' -Recurse | Remove-Item -Force"
echo All .exe files removed successfully.
pause
