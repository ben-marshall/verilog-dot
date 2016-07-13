/*!
@file main.c
@brief Contains the main entry point of the program.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "verilog-dot.h"
#include "verilog-parser/src/verilog_parser.h"

/*!
@brief Prints the help text and exists, depending on the parameters.
*/
void print_help(boolean and_exit)
{
    printf("Usage: ./verilog-dot [args] [input file]\n");
    printf("Options:\n");
    printf("-h, --help    - Print this message and quit.\n");
    printf("-v, --verbose - Print verbose information messages.\n");
    printf("[-o | --output] <FILE PATH> \n");
    printf("              - Specifiy the output file path. By default, \n");
    printf("                is the input path, with .dot appended.\n");
    printf("\n");
    printf("Example:\n");
    printf("    ./verilog-dot -v -o module-graph.dot my_module.v\n");
    printf("\n");

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
    if(argc == 1)
    {
        print_help(BOOL_TRUE);
    }

    shell_args * tr = calloc(1,sizeof(shell_args));

    int i;
    for(i = 1; i < argc; i++)
    {
        if(strcmp(argv[i], "-v")        == 0 ||
                 strcmp(argv[i], "--verbose") == 0)
        {
            tr -> verbose = BOOL_TRUE;
        }
        else if(strcmp(argv[i], "-h")     == 0 ||
                strcmp(argv[i], "--help") == 0)
        {
            free(tr);
            print_help(BOOL_TRUE);
        }
        else if(strcmp(argv[i], "-o")       == 0 ||
                strcmp(argv[i], "--output") == 0)
        {
            if(i < argc - 2)
            {
                i++;
                tr -> output_file_path = argv[i];
            }
        }
        else if(i == argc - 1)
        {
            tr -> input_file_path = argv[i];
        }
        else
        {
            free(tr);
            printf("Unrecognised argument: '%s'\n", argv[i]);
            print_help(BOOL_TRUE);
        }
    }

    if(tr -> input_file_path == NULL ||
        tr -> output_file_path == NULL)
    {
        free(tr);
        print_help(BOOL_TRUE);
    }

    return tr;
}

int main(int argc, char ** argv)
{
    shell_args * args = parse_args(argc,argv);
    
    if(args -> verbose)
    {
        printf("Input File:  %s\n", args -> input_file_path);
        printf("Output File: %s\n", args -> output_file_path);
    }

    return 0;
}
