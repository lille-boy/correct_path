/**************************************************************************************************
 *
 * Main Program.
 *
 *************************************************************************************************/
#include <stdio.h>
#include <string.h>
#include "correct_path.h"
#include "tests.h"

/******************************************************************************
 * Main
 *****************************************************************************/
int main(int argc, char *argv[])
{
    if (argc > 1) {
        char *instruction = argv[1];
        if ((instruction[0] == '-') && (instruction[1] == 't')) {
            tests_run_all();
        }
        else {
            char *sequence = correct_path(argv[1]);
            printf("solution: %s\n", sequence);
        }
    }
    else {
        printf("provide a string\n");
    }

    return 0;
}
