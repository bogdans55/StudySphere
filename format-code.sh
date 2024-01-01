#!/bin/bash

command="/usr/bin/clang-format"

files=("app/src/*.cpp" "app/lib/*.h" "server/*.cpp" "server/*.h")

$command -i $files

echo "Code formatting completed!"