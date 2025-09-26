#!/usr/bin/env bash
set -euo pipefail

BUILD_DIR="${1:-Build}"
INSTALL_DIR="${2:-Install}"

cmake -B "$BUILD_DIR" -G Ninja -S . \
    -DCMAKE_BUILD_TYPE=Debug \
    ${INSTALL_DIR:+-DCMAKE_INSTALL_PREFIX="$INSTALL_DIR"}

cmake --build "$BUILD_DIR" --parallel
