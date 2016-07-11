/*!
@file main.c
@brief Contains the main entry point of the program.
*/

#include <stdlib.h>
#include <stdio.h>

#include "verilog-parser/src/verilog_parser.h"

int main(int argc, char ** argv)
{
    int i;
    
    for(i = 0; i < argc; i++)
    {
        printf("%s ", argv[i]);
    }
    printf("\n");

    return 0;
}
