#!/bin/bash
# This script will handle the creation of a new alias by
# adding the entry to the unformatted.txt file and to ~/.bash_aliases

# Gets /bin/ project directory with a sweet one-liner
BIN_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

# Extracts the base directory from the /bin/ directory
BASE_DIR=$(echo "$BIN_DIR" | sed 's,/*[^/]\+/*$,,')

echo "---NEW VARIABLE CREATION---"
echo "Enter q at any time to exit."
printf "\n"
echo "Enter the variable type (must be one word):"
echo "This can be any string, like \"directory\", \"online\", \"program\", etc."
read variable_type
compare="q"
if [ "$variable_type" == "$compare" ]; then
    exit
fi
printf "\n"
echo "Enter the variable you wish to substitute the command for (must be one word):"
read variable_name
if [ "$variable_name" == "$compare" ]; then
    exit
fi
printf "\n"
echo "Enter the command/path to substitute (spaces allowed, format strings carefully)"
read variable_command
if [ "$variable_command" == "$compare" ]; then
    exit
fi
printf "\n"
echo "Enter a description for the variable (spaces allowed):"
read variable_description
if [ "$variable_description" == "$compare" ]; then
    exit
fi

echo "$variable_type#$variable_name#$variable_description" >> "$BASE_DIR/local/variables_unformatted.txt"
# Following line should be commented if you don't want ~/.bash_aliases to be modified when testing
echo "$variable_name=\"$variable_command\"" >> ~/.bash_aliases
