
cmake_minimum_required(VERSION 2.8)

project (verilog-dot-exe)

add_subdirectory(./verilog-parser)

set(VERILOG_DOT_SRC main.c
                    verilog-dot-emit.c
                    verilog-ast-walk.c
                    verilog-module-inherit.c)

set(VERILOG_DOT_EXE verilog-dot)

set(VERILOG_PARSER_LIB verilogparser)

SET(CMAKE_C_FLAGS_DEBUG "-g -O0 -Wall -W -fprofile-arcs -ftest-coverage")
SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "-fprofile-arcs -ftest-coverage")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE}")
SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE}")

add_executable(${VERILOG_DOT_EXE} ${VERILOG_DOT_SRC})
target_link_libraries(${VERILOG_DOT_EXE} verilogparser)


add_custom_target(dots
    COMMAND ${VERILOG_DOT_EXE} -v ../tests/simple.v
    COMMAND dot -Tsvg ../tests/simple.v.dot > ../tests/simple.svg
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    DEPENDS ${VERILOG_DOT_EXE}
    COMMENT "Testing Dot Exe"
    VERBATIM
)
