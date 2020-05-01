#!/bin/bash

set -Eeuo pipefail
set -x

# Gets base project directory with a sweet one-liner
BASE_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
