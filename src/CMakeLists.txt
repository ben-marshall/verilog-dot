
cmake_minimum_required(VERSION 2.6)

project (verilog-dot-exe)

set(VERILOG_DOT_SRC main.c)
set(VERILOG_DOT_EXE verilog-dot)

add_executable(${VERILOG_DOT_EXE} ${VERILOG_DOT_SRC})
