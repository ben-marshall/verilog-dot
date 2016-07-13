/*!
@file verilog-ast-walk.c
@brief Contains definitions of functions and structures used to walk the
verilog source tree.
*/

#include "verilog-ast-walk.h"

/*!
@brief Walks over a module declaration, emiting nodes as appropriate.
*/
void walk_port_declaration(
    dot_file                * graph, //!< The graph to emit to.
    dot_node                  parent, //!< parent node of the module.
    ast_port_declaration    * port   //!< The port to walk.
){
    int P;
    for(P = 0; P < port -> port_names -> items; P++)
    {
        dot_node id = dot_new_node(graph);
        ast_identifier name = ast_list_get(port -> port_names, P);

        dot_emit_node(graph, id, name -> identifier);
        dot_emit_edge(graph, parent, id);
    }
}

/*!
@brief Walks over a module declaration, emiting nodes as appropriate.
*/
void walk_module_declaration(
    dot_file                * graph, //!< The graph to emit to.
    dot_node                  parent, //!< parent node of the module.
    ast_module_declaration  * module //!< The module to walk.
){
    dot_node newModule = dot_new_node(graph);

    dot_emit_node(graph,newModule, module -> identifier->identifier);
    dot_emit_edge(graph, parent, newModule);

    dot_node portsParent = dot_new_node(graph);
    dot_emit_node(graph, portsParent, "Ports");
    dot_emit_edge(graph, newModule, portsParent);

    int p;
    for(p = 0; p < module -> ports -> items; p ++)
    {
        ast_port_declaration * port = ast_list_get(module->ports,p);
        walk_port_declaration(graph,portsParent,port);
    }

}

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
        ast_module_declaration * module = ast_list_get(tree -> modules,m);
        walk_module_declaration(graph, root, module);
    }
}

