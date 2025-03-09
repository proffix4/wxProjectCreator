@echo off

REM Определение шаблонов файлов для удаления
set FILE_PATTERNS=*.bak *.sln *.vcxproj *.vcxproj.user makefile.gcc Makefile linux_app *-autosave.pjd *.rc

REM Удаление указанных шаблонов файлов
for %%f in (%FILE_PATTERNS%) do (
    del /Q %%f >nul 2>&1
)

REM Определение каталогов для удаления
set DIRS=Debug MinGWUnicodeDebug MinGWUnicodeRelease Release

REM Удаление указанных каталогов, если они существуют
for %%d in (%DIRS%) do (
    if exist %%d rmdir /S /Q %%d
)

echo Cleaning of project configurations is completed.
