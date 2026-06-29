#!/usr/bin/env bash
set -euo pipefail

if [ "$#" -ne 0 ]; then
  echo "build.sh does not take arguments yet." >&2
  exit 2
fi

# Keep Wine quiet and avoid needing an X display.
export WINEDEBUG="${WINEDEBUG:--all}"
export DISPLAY="${DISPLAY:-}"

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
exec python3 "$SCRIPT_DIR/tools/build.py"
