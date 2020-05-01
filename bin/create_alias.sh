#!/bin/bash
# This script will handle the creation of a new alias by
# adding the entry to the unformatted.txt file and to ~/.bash_aliases

# Gets /bin/ project directory with a sweet one-liner
BIN_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

# Extracts the base directory from the /bin/ directory
BASE_DIR=$(echo "$BIN_DIR" | sed 's,/*[^/]\+/*$,,')

echo "NEW ALIAS CREATION"
echo "Enter the alias type (must be one word):"
echo "This can be any string, like directory, online, program, etc."
read alias_type
echo "Enter the alias name (must be one word):"
read alias_name
echo "Enter the actual alias command (spaces allowed, format strings carefully)"
read alias_command
echo "Enter a description for the alias (spaces allowed):"
read alias_description

echo "$alias_type#$alias_name#$alias_description" >> "$BASE_DIR/local/aliases_unformatted.txt"
echo "alias $alias_name=\"$alias_command\"" >> ~/.bash_aliases