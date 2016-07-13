
cmake_minimum_required(VERSION 2.8)

project (verilog-dot-exe)

add_subdirectory(./verilog-parser)

set(VERILOG_DOT_SRC main.c
                    verilog-dot-emit.c)

set(VERILOG_DOT_EXE verilog-dot)

set(VERILOG_PARSER_LIB verilogparser)

add_executable(${VERILOG_DOT_EXE} ${VERILOG_DOT_SRC})
target_link_libraries(${VERILOG_DOT_EXE} verilogparser)
