/**************************************************************************************************
 *
 * Main Program.
 *
 *************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
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
            char *solution = malloc(strlen(argv[1]));
            correct_path(argv[1], solution);
            printf("solution: %s\n", solution);

            if (argc > 2) {
                char * display = argv[2];
                if ((display[0] == '-') && (display[1] == 'd')) {
                    correct_path_display();
                }
            }
        }
    }
    else {
        printf("provide a string\n");
    }

    return 0;
}
