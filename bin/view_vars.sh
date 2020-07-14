#!/bin/bash

# This script runs the table_driver.exe program which formats the variables
# provided by the user previously, and then outputs the contents of the
# formatted file to standard out.

set -Eeuo pipefail
# set -x

# Gets /bin/ project directory with a sweet one-liner
BIN_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

# Extracts the base directory from the /bin/ directory
BASE_DIR=$(echo "$BIN_DIR" | sed 's,/*[^/]\+/*$,,')

# Creates the path to table_driver.exe
EXE_PATH="/src/table_driver.exe"
FINAL_EXE="$BASE_DIR$EXE_PATH"

# Runs table driver exe with alias parameter and base directory
$FINAL_EXE -t var -f $BASE_DIR -a 15

# Prints output to terminal
cat "$BASE_DIR/local/variables_formatted.txt"