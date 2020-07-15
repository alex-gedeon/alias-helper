#!/bin/bash
# Main driver for the alias management system. Reads in user commands
# to view, create, and delete aliases.

# Refresh aliases
source ~/.bash_aliases

# Gets /bin/ project directory
BIN_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
# Extracts the base directory from the /bin/ directory
BASE_DIR=$(echo "$BIN_DIR" | sed 's,/*[^/]\+/*$,,')

echo "Alias Helper v. 1.0"
printf "\n"

while true
do
    echo "Enter command (enter h for help):"
    read user_input
    case $user_input in
        h)
            echo "---The following inputs are valid---"
            echo "  h: Opens the help menu"
            echo "  l: Lists available aliases"
            echo "  b: List blacklisted aliases"
            echo "  c: Creates a new alias"
            echo "  d: Remove an alias from the printed list (doesn't remove from blacklist)"
            echo "  q: Quits the alias manager"
            ;;
        l)
            "$BIN_DIR/view_aliases.sh"
            ;;
        b)
            $BASE_DIR/src/table_driver.exe -t alias -f $BASE_DIR -b true
            cat "$BASE_DIR/local/aliases_formatted.txt"
            ;;
        c)
            printf "\n"
            "$BIN_DIR/create_alias.sh"
            ;;
        d)
            printf "\n"
            echo "Enter alias ID to remove from list: "
            read id_to_delte
            echo $id_to_delte >> "$BASE_DIR/local/blacklist.txt"
            ;;
        q)
            break
            ;;
        *)
            echo "Invalid input."
            ;;
    esac
    printf "\n"
done

# Refresh aliases
source ~/.bash_aliases
