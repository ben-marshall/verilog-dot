/*!
@file main.c
@brief Contains the main entry point of the program.
*/

#include <stdlib.h>
#include <stdio.h>

#include "verilog-dot.h"
#include "verilog-parser/src/verilog_parser.h"

/*!
@brief Prints the help text and exists, depending on the parameters.
*/
void print_help(boolean and_exit)
{
    
    if(and_exit){
        exit(0);
    }
}

/*!
@brief Responsible for parsing all of the command line arguments.
@returns A shell_args pointer
*/
shell_args * parse_args(int argc, char ** argv)
{
    int i;
    
    for(i = 0; i < argc; i++)
    {
        printf("%s ", argv[i]);
    }
}

int main(int argc, char ** argv)
{
    parse_args(argc,argv);
    printf("\n");

    return 0;
}
