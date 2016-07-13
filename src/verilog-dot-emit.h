/*!
@file verilog-dot-emit.h
@brief Contains declarations of functions and structures used to emit dot file
data.
*/

#include <stdio.h>
#include <stdlib.h>

#ifndef VERILOG_DOT_EMIT_H
#define VERILOG_DOT_EMIT_H

/*!
@brief A container for all information on a single dot file being emitted.
*/
typedef struct dot_file_t{
    FILE         * file;        //!< Output file handle.
    unsigned int   node_count;  //!< Internal node counter.
} dot_file;

//! Represents the unique ID of a node.
typedef unsigned int dot_node;

/*!
@brief Creates and returns a new dot file object which can be written to.
@param [in] writable - The opened and writiable output file.
@returns A pointer to a new dot_file instance, which can be passed to
the various output functions to write data to the output file.
*/
dot_file * dot_file_new(FILE * writable);


#endif
