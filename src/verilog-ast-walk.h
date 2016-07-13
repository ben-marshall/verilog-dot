/*!
@file verilog-ast-walk.h
@brief Contains declarations of functions and structures used to walk the
verilog source tree.
*/

#include "verilog-dot.h"
#include "verilog-dot-emit.h"

#include "verilog-parser/src/verilog_parser.h"

#ifndef VERILOG_AST_WALK_H
#define VERILOG_AST_WALK_H

/*!
@brief Recursively decends the syntax tree, emiting the dot graph as it goes.
*/
void walk_syntax_tree(
    dot_file            * graph, //!< The graph to emit to.
    verilog_source_tree * tree   //!< The source tree to walk.
);

#endif
