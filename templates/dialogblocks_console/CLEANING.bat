@echo off
del /Q *.bak *.sln *.vcxproj *.vcxproj.user >nul 2>&1
del /Q makefile.gcc >nul 2>&1
del /Q Makefile >nul 2>&1
echo Cleaning of project configurations is completed.
