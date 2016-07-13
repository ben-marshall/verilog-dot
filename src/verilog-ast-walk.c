/*!
@file verilog-ast-walk.c
@brief Contains definitions of functions and structures used to walk the
verilog source tree.
*/

#include "verilog-ast-walk.h"

/*!
@brief Recursively decends the syntax tree, emiting the dot graph as it goes.
*/
void walk_syntax_tree(
    dot_file            * graph, //!< The graph to emit to.
    verilog_source_tree * tree   //!< The source tree to walk.
){
    dot_node root = dot_new_node(graph);

    dot_emit_node(graph,root,"Tree Root");
    
    int m;
    for(m = 0; m < tree -> modules -> items; m ++)
    {
        dot_node newModule = dot_new_node(graph);
        ast_module_declaration * module = ast_list_get(tree -> modules,m);
        
        dot_emit_node(graph,newModule, module -> identifier->identifier);
        dot_emit_edge(graph, root, newModule);

        printf("Added new module: '%s'\n", module -> identifier -> identifier);
    }
}
