/*!
@file verilog-module-inherit.h
@brief Contains declarations of functions and structures used to draw the
module inheritance hierarchy of a set of files
*/

#include "verilog-dot.h"
#include "verilog-dot-emit.h"
#include "verilog-ast-walk.h"
#include "verilog-parser/src/verilog_parser.h"

#ifndef VERILOG_MODULE_INHERIT_H
#define VERILOG_MODULE_INHERIT_H

/*!
@brief Draws the module inheritance hierarchy of a source tree.
*/
void dot_draw_module_hierarchy(
    verilog_source_tree * source,
    dot_file            * graph
);

#endif

