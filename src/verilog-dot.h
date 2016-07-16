/*!
@file verilog-dot.h
@brief Contains common data structures and functions used by the program
*/

#include <stdio.h>

#ifndef VERILOG_DOT_H
#define VERILOG_DOT_H

//! A simple boolean type.
typedef enum boolean_e{
    BOOL_TRUE  = 1,
    BOOL_FALSE = 0
} boolean;

/*!
@brief Stores all of the command line arguments to the program
@see parse_args
*/
typedef struct shell_args_t{
    int       input_files_start;    //!< From which command line argument do input files start.
    char    * output_file_path;  //!< Where to put the output.
    FILE    * output_file;      //!< Output file handle.
    boolean   verbose;      //!< Be verbose in printing information messages.
    boolean   draw_ast;         //!< Whether to draw the AST.
    boolean   module_hierarchy; //!< Whether to draw the module heirarchy.
} shell_args;

/*!
@brief Responsible for parsing all of the command line arguments.
@returns A shell_args pointer
*/
shell_args * parse_args(int argc, char ** argv);


#endif
