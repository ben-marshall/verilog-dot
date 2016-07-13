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
