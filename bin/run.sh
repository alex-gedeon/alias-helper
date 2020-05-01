#!/bin/bash

set -Eeuo pipefail
set -x

# Gets base project directory with a sweet one-liner
BIN_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

BASE_DIR=$(echo "$BIN_DIR" | sed 's,/*[^/]\+/*$,,')

EXE_PATH="/src/table_driver.exe"
FINAL_EXE="$BASE_DIR$EXE_PATH"

# Run table driver exe with alias parameter and base directory
$FINAL_EXE -t alias -f $BASE_DIR

# read -r line
