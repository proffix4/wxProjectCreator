@echo off
setlocal enabledelayedexpansion

for %%f in (*.exe) do del /Q /F "%%f" >nul 2>&1

echo Cleaning of project is completed.
