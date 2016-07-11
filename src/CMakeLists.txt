
cmake_minimum_required(VERSION 2.8)

project (verilog-dot-exe)

set(VERILOG_DOT_SRC main.c)
set(VERILOG_DOT_EXE verilog-dot)
SET(VERILOG_PARSER_LIB verilogparser)

add_custom_command(TARGET ${VERILOG_DOT_EXE}
                   PRE_BUILD
                   COMMAND make app
                   WORKING_DIRECTORY ./verilog-parser
                   COMMENT "Building parser library"
                   VERBATIM
                  )

link_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/verilog-parser/build/lib
)

add_executable(${VERILOG_DOT_EXE} ${VERILOG_DOT_SRC})

target_include_directories(
    ${VERILOG_DOT_EXE} 
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/verilog-parser/src
    ${CMAKE_CURRENT_SOURCE_DIR}/verilog-parser/build/gen
)

target_link_libraries(${VERILOG_DOT_EXE} ${VERILOG_PARSER_LIB})
