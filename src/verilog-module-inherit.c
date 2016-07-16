/*!
@file verilog-module-inherit.c
@brief Contains definitions of functions and structures used to draw the
module inheritance hierarchy of a set of files
*/

#include "verilog-module-inherit.h"
#include "verilog-dot-emit.h"

void dot_module_hierarchy_visit_module(
    dot_file            * graph,
    dot_node              parent,
    ast_module_declaration * module
)
{
    dot_node moduleID = dot_new_node(graph);
    dot_emit_node(graph, moduleID, 
        ast_identifier_tostring(module -> identifier));
    dot_emit_edge(graph, moduleID, parent);

    int sub;
    for(sub = 0; sub < module -> module_instantiations -> items; sub++)
    {
        ast_module_instantiation * submod = ast_list_get(
            module->module_instantiations,sub);
        
        if(submod -> resolved)
        {
            dot_module_hierarchy_visit_module(graph, moduleID,
                submod -> declaration);
        }
    }
}

/*!
@brief Draws the module inheritance hierarchy of a source tree.
*/
void dot_draw_module_hierarchy(
    verilog_source_tree * source,
    dot_file            * graph
){
    
    int m;
    for(m = 0; m < source -> modules -> items ; m++)
    {
        ast_module_declaration * module = ast_list_get(source -> modules, m);

        dot_node moduleID = dot_new_node(graph);
        dot_emit_node(graph, moduleID, 
            ast_identifier_tostring(module->identifier));

        int sub;
        for(sub = 0; sub < module -> module_instantiations -> items; sub++)
        {
            ast_module_instantiation * submod = ast_list_get(
                module->module_instantiations,sub);
            
            if(submod -> resolved)
            {
                dot_module_hierarchy_visit_module(graph, moduleID,
                    submod -> declaration);
            }
        }
    }
}
