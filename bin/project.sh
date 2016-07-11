#!/bin/sh

echo "------------------- Setting Up Verilog-Dot Workspace -----------------"

git submodule update --remote src/verilog-parser/

mkdir -p ./build/
cd ./build
cmake ..
cd -

echo "----------------------- Workspace setup complete ---------------------"

