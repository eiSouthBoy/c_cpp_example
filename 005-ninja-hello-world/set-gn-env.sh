#!/bin/bash

GN_DIR="/home/caojun/C/005-ninja-hello-world/gn/out"
if [ ! -d $GN_DIR ]; then
    echo "Error: GN directory '$GN_DIR' not found."
    exit 1
fi

echo "set gn env: $GN_DIR"
export PATH="$GN_DIR:$PATH"

GN_VERSION=$(gn --version)
echo "gn version: $GN_VERSION"