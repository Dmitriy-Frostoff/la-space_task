#!/bin/bash

# ---start log---
printf '⚙️  run "%s"\n' "$0"

# ---exit on any error---
set -euo pipefail

# ---set cwd as current script's folder---
# e.g. ./task (cwd relative)
cd "$(dirname "$0")" || exit 1

# ---variables---
# compiled file name
COMPILED_FILE_NAME="main"
# folders for excluding
EXCLUDE_FOLDERS='tests'
# get all *c files ('\0' separated) to the array => C_FILES
mapfile -t C_FILES < <(find . -name "$EXCLUDE_FOLDERS" -prune -o -name "*.c" -type f -print)

# ---check that C_FILES array is not empty---
if [[ "${#C_FILES[@]}" -eq 0 ]]; then
  printf '😒 ❌ *.c files are not found in the "%s" folder' "$$PWD"
  exit 1
fi

# ---compile *.c files---
printf '⚗️ ⏳ compiling "%s.exe" ...\n' "$COMPILED_FILE_NAME"
gcc -g -I. -Wall -std=c23 "${C_FILES[@]}" -o "$COMPILED_FILE_NAME"

# ---handle EXIT signal---
trap 'echo "📜✅ script done"' EXIT

# ---handle the script's execution result---
if [[ "$?" -eq 0 ]]; then
  printf '✅ Compilation Succeed\n'
  exit 0
else
  printf '❌ Compilation finished with exit code %d\n' "$?"
  exit 1
fi
