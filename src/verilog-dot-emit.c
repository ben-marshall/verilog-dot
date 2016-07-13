/*!
@file verilog-dot-emit.c
@brief Contains definitions of functions and structures used to emit dot file
data.
*/

#include "verilog-dot-emit.h"

/*!
@details
Creates and returns a new dot file object which can be written to.
This function also writes the preamble to the graph. After calling dot_file_new
one must also call dot_file_close, which writes the postamble, and finishes
the file.
*/
dot_file * dot_file_new(FILE * writable)
{
    dot_file * tr = calloc(1,sizeof(dot_file));

    tr -> node_count = 0;
    tr -> file       = writable;

    fprintf(tr -> file, "\ngraph verilog_dot_graph{\n");

    return  tr;
}

/*!
@brief Finishes off the output file, writing any extra syntax.
@post The output file is closed, and is a valid .dot file, ready to be
viewed.
*/
void dot_file_finish(dot_file * graph)
{
    fprintf(graph -> file, "}\n");
    fclose(graph -> file);
}

/*!
@brief Emits a simple node to the graph, with a given ID and label.
*/
void dot_emit_node(dot_file * graph, dot_node id, char * label)
{
    fprintf(graph -> file,"\t%d [label=\"%s\"];\n",id,label);
}

/*!
@brief Emits an edge between two pre-defined nodes.
*/
void dot_emit_edge(dot_file * graph, dot_node id1, dot_node id2)
{
    fprintf(graph -> file, "\t %d -- %d\n", id1,id2);
}

/*!
@brief Generates a new node ID for the graph and returns it.
*/
dot_node dot_new_node(dot_file * graph)
{
    graph -> node_count ++;
    return graph -> node_count;
}
