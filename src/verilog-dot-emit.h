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

/*!
@brief Finishes off the output file, writing any extra syntax.
@post The output file is closed, and is a valid .dot file, ready to be
viewed.
*/
void dot_file_finish(dot_file * graph);

/*!
@brief Generates a new node ID for the graph and returns it.
*/
dot_node dot_new_node(dot_file * graph);

/*!
@brief Emits a simple node to the graph, with a given ID and label.
*/
void dot_emit_node(dot_file * graph, dot_node id, char * label);

/*!
@brief Emits a record node to the graph, with a given ID, label and set of
characteristics.
*/
void dot_emit_record_node(
    dot_file * graph, 
    dot_node id, 
    char * label,
    char ** parameters, 
    char ** values, 
    int num_params
);

/*!
@brief Emits an edge between two pre-defined nodes.
*/
void dot_emit_edge(dot_file * graph, dot_node id1, dot_node id2);

#endif
