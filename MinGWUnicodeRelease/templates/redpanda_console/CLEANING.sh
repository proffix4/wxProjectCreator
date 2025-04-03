#!/bin/bash

# Включаем режим "fail-safe" для ошибок
set -e

# Удаление файлов с определёнными расширениями
rm -f *.o *.exe *.bookmarks *.debug *.Manifest *.layout *_private.* *.win 2>/dev/null

echo "Cleaning of project is completed."
