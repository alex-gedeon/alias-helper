# Gets /bin/ project directory
BIN_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

# Extracts the base directory from the /bin/ directory
BASE_DIR=$(echo "$BIN_DIR" | sed 's,/*[^/]\+/*$,,')

cat ~/.bash_aliases | python3 $BASE_DIR