
cmake_minimum_required(VERSION 2.8)

add_subdirectory(./verilog-parser)

project (verilog-dot-exe)

set(VERILOG_DOT_SRC main.c)
set(VERILOG_DOT_EXE verilog-dot)
set(VERILOG_PARSER_LIB verilogparser)

add_executable(${VERILOG_DOT_EXE} ${VERILOG_DOT_SRC})

target_include_directories(
    ${VERILOG_DOT_EXE} 
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/verilog-parser/src
)

message("verilogparser: ${LIBRARY_NAME}")

target_link_libraries(${VERILOG_DOT_EXE} ${LIBRARY_NAME})
