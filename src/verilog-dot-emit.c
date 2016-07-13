/*!
@file verilog-dot-emit.c
@brief Contains definitions of functions and structures used to emit dot file
data.
*/

#include "verilog-dot-emit.h"

/*!
@brief Creates and returns a new dot file object which can be written to.
@param [in] writable - The opened and writiable output file.
@returns A pointer to a new dot_file instance, which can be passed to
the various output functions to write data to the output file.
*/
dot_file * dot_file_new(FILE * writable)
{
    dot_file * tr = calloc(1,sizeof(dot_file));

    tr -> node_count = 0;
    tr -> file       = writable;

    return  tr;
}
