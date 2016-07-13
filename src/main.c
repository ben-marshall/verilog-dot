/*!
@file main.c
@brief Contains the main entry point of the program.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "verilog-dot.h"
#include "verilog-dot-emit.h"
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

    if(tr -> input_file_path == NULL)
    {
        free(tr);
        print_help(BOOL_TRUE);
    }
    if(tr -> output_file_path == NULL)
    {
        size_t inleng = strlen(tr -> input_file_path);
        tr -> output_file_path = calloc(inleng+4,sizeof(char));
        strcat(tr -> output_file_path, tr -> input_file_path);
        strcat(tr -> output_file_path, ".dot");
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

    // Open and validate the input file.
    args -> input_file = fopen(args -> input_file_path, "r");
    if(args -> input_file == NULL)
    {
        printf("ERROR: Unable to open input file for reading:\n");
        printf("\t%s\n",args -> input_file_path);
        free(args);
        return 1;
    }

    // Open and validate the output file.
    args -> output_file = fopen(args -> output_file_path, "w");
    if(args -> output_file == NULL)
    {
        printf("ERROR: Unable to open output file for writing:\n");
        printf("\t%s\n",args -> output_file_path);
        free(args);
        return 1;
    }


    // Initialise the parser.
    verilog_parser_init();

    // Parse our input file.
    int result = verilog_parse_file(args -> input_file);

    // If the parse didn't work, then print an error message and quit.
    if(result != 0)
    {
        printf("ERROR: Failed to parse input file.\n");
        printf("\t%s\n",args -> input_file_path);
        free(args);
        return 1;
    }
    else if(args -> verbose)
    {
        printf("Parsing of input file successful.\n");
    }

    // This is how we access the parsed source tree.
    verilog_source_tree * ast = yy_verilog_source_tree;
    
    // Create a dot file we will dump the AST into.
    dot_file * graph = dot_file_new(args -> output_file);

    // Clean up the output file and close it.
    dot_file_finish(graph);

    if(args -> verbose)
    {
        printf("Dot file writing complete!\n");
    }

    return 0;
}
