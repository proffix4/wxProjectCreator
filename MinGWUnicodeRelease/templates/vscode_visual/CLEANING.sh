#!/bin/bash

# Включаем режим "fail-safe" для ошибок
set -e

# Удаление всех файлов с расширением .exe в текущей директории
rm -f *.exe 2>/dev/null

echo "Cleaning of project is completed."
