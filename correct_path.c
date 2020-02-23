/**************************************************************************************************
 *
 * Find the correct path
 * Start in the top left cell (A1). End in the bottom right (E5)
 *
 *       A     B     C     D     E
 *    ______________________________
 *  1 |     |     |     |     |     |
 *    |__V__|_____|_____|_____|_____|
 *  2 |     |     |     |     |     |
 *    |__V__|_____|_____|_____|_____|
 *  3 |     |     |     |     |     |
 *    |__V__|_____|_____|_____|_____|
 *  4 |     |     |     |     |     |
 *    |__V__|_____|_____|_____|_____|
 *  5 |  >  |  >  |  >  |  >  |     |
 *    |_____|_____|____ |_____|_____|
 *
 *
 *************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "correct_path.h"

#define TARGET  4
#define GRID_SIZE   5

struct position {
    int row;
    int column;
};

/******************************************************************************
 * Move left or right
 *****************************************************************************/
static void move_column(char *sequence, struct position *pos, int index)
{
    int size = strlen(sequence);

    if (sequence[index] == '?') {
        if (pos->column < TARGET) {
            if ((index == 0) ||
                (index > 0 && sequence[index - 1] != 'l') ||
                (index < size && sequence[index + 1] != 'l') ) {
                sequence[index] = 'r';
                pos->column++;
            }
        }
        else if (pos->column > TARGET) {
            if ((index == 0) ||
                (index > 0 && sequence[index - 1] != 'r') ||
                (index < size && sequence[index + 1] != 'r')) {
                sequence[index] = 'l';
                pos->column--;
            }
        }
        else {
            if ((index > 0 && sequence[index - 1] != 'l') ||
                (index < size && sequence[index + 1] != 'l')) {
                sequence[index] = 'r';
                pos->column++;
            }
        }
    }
}

/******************************************************************************
 * Move up or down
 *****************************************************************************/
static void move_row(char *sequence, struct position *pos, int index)
{
    int size = strlen(sequence);

    if (sequence[index] == '?') {
        if (pos->row < TARGET) {
            if ((index == 0) ||
                (index > 0 && sequence[index - 1] != 'u') ||
                (index < size && sequence[index + 1] != 'u')) {
                sequence[index] = 'd';
                pos->row++;
            }
        }
        else if (pos->row > TARGET) {
            if ((index == 0) ||
                (index > 0 && sequence[index - 1] != 'd') ||
                (index < size && sequence[index + 1] != 'd')) {
                sequence[index] = 'u';
                pos->row--;
            }
        }
        else {
            if ((index > 0 && sequence[index - 1] != 'u') ||
                (index < size && sequence[index + 1] != 'u')) {
                sequence[index] = 'd';
                pos->row++;
            }
        }
    }
}

/******************************************************************************
 * Find the correct path
 *****************************************************************************/
char * correct_path(const char *input)
{
    int size = strlen(input);
    struct position pos = {.row = 0, .column = 0};

    /* copy the input to a local variable */
    char *sequence = malloc(size);
    for (int i = 0; i < size; i++) {
        sequence[i] = input[i];

        switch (sequence[i]) {
            case 'r':
                pos.column++;
            break;
            case 'd':
                pos.row++;
            break;
            case 'l':
                pos.column--;
            break;
            case 'u':
                pos.row--;
            break;
            case '?':
            default:
            break;
        }
    }

    //printf("Start... column: %d, row: %d\n", pos.column, pos.row);

    for (int j = 0; j < size; j++) {
        move_column(sequence, &pos, j);
        move_row(sequence, &pos, j);
    }

    //printf("End... column %d, row %d\n", pos.column, pos.row);

    return sequence;
}
