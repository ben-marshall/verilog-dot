/*!
@file main.c
@brief Contains the main entry point of the program.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "verilog-dot.h"
#include "verilog-ast-walk.h"
#include "verilog-dot-emit.h"
#include "verilog-module-inherit.h"
#include "verilog-parser/src/verilog_parser.h"
#include "verilog-parser/src/verilog_ast_util.h"

/*!
@brief Prints the help text and exists, depending on the parameters.
*/
void print_help(boolean and_exit)
{
    printf("Usage: ./verilog-dot [args] [input files]\n");
    printf("Options:\n");
    printf("--ast         - Draw the abstract syntax tree.\n");
    printf("--hierarchy   - Draw the module instance hierarchy.\n");
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
        else if(strcmp(argv[i], "--ast")     == 0)
        {
            tr -> draw_ast = BOOL_TRUE;
        }
        else if(strcmp(argv[i], "--hierarchy")     == 0)
        {
            tr -> module_hierarchy = BOOL_TRUE;
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
        else
        {
            tr -> input_files_start = i;
            break;
        }
    }

    if(tr -> output_file_path == NULL)
    {
        tr -> output_file_path = "graph.dot";
    }

    return tr;
}

int main(int argc, char ** argv)
{
    shell_args * args = parse_args(argc,argv);
    if(args -> draw_ast == BOOL_FALSE && 
       args -> module_hierarchy == BOOL_FALSE){
        free(args);
        print_help(BOOL_TRUE);
    }
    
    if(args -> verbose)
    {
        printf("Output File: %s\n", args -> output_file_path);
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

    int F;
    for(F = args -> input_files_start; F < argc; F++)
    {
        FILE * input_file = fopen(argv[F],"r");
        if(input_file)
        {
            // Parse our input file.
            int result = verilog_parse_file(input_file);

            // If the parse didn't work, print an error message and quit.
            if(result != 0)
            {
                printf("ERROR: Failed to parse input file:");
                printf("\t%s\n",argv[F]);
            }
            else if(args -> verbose)
            {
                printf("%s\n", argv[F]);
            }
        }
        else
        {
            printf("ERROR Could not open file for reading: %s\n", argv[F]);
            free(args);
            return 1;
        }
    }

    // This is how we access the parsed source tree.
    verilog_source_tree * ast = yy_verilog_source_tree;

    // Resolve all of the names in the syntax tree.
    verilog_resolve_modules(ast);
    
    // Create a dot file we will dump the AST into.
    dot_file * graph = dot_file_new(args -> output_file);

    if(args -> draw_ast == BOOL_TRUE){
        // Walk the syntax tree, generating the graph
        walk_syntax_tree(graph, ast);
    }

    if(args -> module_hierarchy == BOOL_TRUE){
        //! Draw the module inheritance hierarchy.
        dot_draw_module_hierarchy(ast,graph);
    }

    // Clean up the output file and close it.
    dot_file_finish(graph);

    if(args -> verbose)
    {
        printf("Dot file writing complete!\n");
    }

    return 0;
}
