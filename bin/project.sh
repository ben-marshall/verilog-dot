#!/bin/sh

echo "------------------- Setting Up Verilog-Dot Workspace -----------------"

mkdir -p ./build/
cd ./build
cmake ..
cd -

echo "----------------------- Workspace setup complete ---------------------"

