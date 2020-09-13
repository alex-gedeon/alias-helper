#!/bin/bash
# This script will handle the creation of a new alias by
# adding the entry to the unformatted.txt file and to ~/.bash_aliases

# Refresh aliases
source ~/.bash_aliases

# Gets /bin/ project directory
BIN_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

# Extracts the base directory from the /bin/ directory
BASE_DIR=$(echo "$BIN_DIR" | sed 's,/*[^/]\+/*$,,')

echo "---NEW ALIAS CREATION---"
echo "Enter q at any time to exit."
printf "\n"
echo "Enter the alias type (must be one word):"
echo "This can be any string, like \"directory\", \"online\", \"program\", etc."
read alias_type
compare="q"
if [ "$alias_type" == "$compare" ]; then
    exit
fi
printf "\n"
echo "Enter the alias you wish to substitute the command for (must be one word):"
read alias_name
if [ "$alias_name" == "$compare" ]; then
    exit
fi
printf "\n"
echo "Enter the command to substitute (spaces allowed, format strings carefully)"
read alias_command
if [ "$alias_command" == "$compare" ]; then
    exit
fi
printf "\n"
echo "Enter a description for the alias (spaces allowed):"
read alias_description
if [ "$alias_description" == "$compare" ]; then
    exit
fi

echo "$alias_type#$alias_name#$alias_description" >> "$BASE_DIR/local/aliases_unformatted.txt"
# Following line should be commented if you don't want ~/.bash_aliases to be modified when testing
echo "alias $alias_name='$alias_command'" >> ~/.bash_aliases

# Refresh aliases
source ~/.bash_aliases
