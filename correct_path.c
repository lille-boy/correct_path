/**************************************************************************************************
 *
 * Find the correct path
 * Start in the top left cell (R0, C0). End in the bottom right (R4, C4)
 *
 *       C0     C1    C2    C3    C4
 *     ______________________________
 *  R0 |  X  |     |     |     |     |
 *     |_____|_____|_____|_____|_____|
 *  R1 |     |     |     |     |     |
 *     |__V__|_____|_____|_____|_____|
 *  R2 |     |     |     |     |     |
 *     |__V__|_____|_____|_____|_____|
 *  R3 |     |     |     |     |     |
 *     |__V__|_____|_____|_____|_____|
 *  R4 |  >  |  >  |  >  |  >  |  X  |
 *     |_____|_____|____ |_____|_____|
 *
 * Note: 4 times right + 4 times down get us to the target cell (R4, C4)
 *
 *************************************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "correct_path.h"

#define MATRIX_SIZE   5
#define TARGET      (MATRIX_SIZE - 1)

unsigned int mov_right;
unsigned int mov_down;

/* matrix to traverse: 0 is 'not visited', 1 is 'visited' */
unsigned int matrix[MATRIX_SIZE][MATRIX_SIZE] =
 { {0, 0, 0, 0, 0},
   {0, 0, 0, 0, 0},
   {0, 0, 0, 0, 0},
   {0, 0, 0, 0, 0},
   {0, 0, 0, 0, 0},
 };

struct position {
    int row;
    int column;
};

/******************************************************************************
 * Initialize matrix
 * Set starting cell (R0, C0) to 1 'visited'
 *****************************************************************************/
static void init_matrix(void)
{
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            matrix[i][j] = 0;
        }
    }
    matrix[0][0] = 1;
}

/******************************************************************************
 * Update the path on the matrix until the first '?'
 *****************************************************************************/
static void update_matrix(char *sequence)
{
    int row = 0;
    int column = 0;

    for (int i = 0; i < strlen(sequence); i++) {
        switch(sequence[i]) {
            case 'r':
                matrix[row][++column] = 1;
            break;
            case 'd':
                matrix[++row][column] = 1;
            break;
            case 'l':
                matrix[row][--column] = 1;
            break;
            case 'u':
                matrix[--row][column] = 1;
            break;
            case '?':
            default:
                goto exit;
            break;
        }
    }

    exit: return;
}

/******************************************************************************
 * Check if it's possible to move right
 * - moving right is within the matrix
 * - cell to move to has not been visited
 *****************************************************************************/
static bool condition_right(struct position *pos)
{
    if ((pos->column < TARGET) && (matrix[pos->row][pos->column + 1] == 0)) {
        return true;
    }
    else {
        return false;
    }
}

/******************************************************************************
 * Check if it's possible to move left
 * - moving left is within the matrix
 * - cell to move to has not been visited
 *****************************************************************************/
static bool condition_left(struct position *pos)
{
    if ((pos->column > 0) && (matrix[pos->row][pos->column - 1] == 0)) {
        return true;
    }
    else {
        return false;
    }
}

/******************************************************************************
 * Move left or right
 *****************************************************************************/
static void move_column(char *sequence, struct position *pos, int index)
{
    if (sequence[index] == 'r') {
        pos->column++;
    }
    else if (sequence[index] == 'l') {
        pos->column--;
    }
    else if (sequence[index] == '?') {
        if (mov_right < TARGET) {
            if (condition_right(pos) == true) {
                sequence[index] = 'r';
                pos->column++;
                mov_right++;
            }
        }
        else if (mov_right > TARGET) {
            if (condition_left(pos) == true) {
                sequence[index] = 'l';
                pos->column--;
                mov_right--;
            }
        }
        else if ((mov_right == TARGET) && (mov_down == TARGET)) {
            if (condition_right(pos) == true) {
                sequence[index] = 'r';
                pos->column++;
                mov_right++;
            }
            else if (condition_left(pos) == true) {
                sequence[index] = 'l';
                pos->column--;
                mov_right--;
            }
        }
    }
    update_matrix(sequence);
}

/******************************************************************************
 * Check if it's possible to move up
 * - moving up is within the matrix
 * - cell to move to has not been visited
 *****************************************************************************/
static bool condition_up(struct position *pos)
{
    if ((pos->row > 0) && (matrix[pos->row - 1][pos->column] == 0)) {
        return true;
    }
    else {
        return false;
    }
}

/******************************************************************************
 * Check if it's possible to move down
 * - moving down is within the matrix
 * - cell to move to has not been visited
 *****************************************************************************/
static bool condition_down(struct position *pos)
{
    if ((pos->row < TARGET) && (matrix[pos->row + 1][pos->column] == 0)) {
        return true;
    }
    else {
        return false;
    }
}

/******************************************************************************
 * Move up or down
 *****************************************************************************/
static void move_row(char *sequence, struct position *pos, int index)
{
    if (sequence[index] == 'd') {
        pos->row++;
    }
    else if (sequence[index] == 'u') {
        pos->row--;
    }
    else if (sequence[index] == '?') {
        if (mov_down < TARGET) {
            if (condition_down(pos) == true) {
                sequence[index] = 'd';
                pos->row++;
                mov_down++;
            }
        }
        else if (mov_down > TARGET) {
            if (condition_up(pos) == true) {
                sequence[index] = 'u';
                pos->row--;
                mov_down--;
            }
        }
        else if ((mov_right == TARGET) && (mov_down == TARGET)) {
            if (condition_up(pos) == true) {
                sequence[index] = 'u';
                pos->row--;
                mov_down--;
            }
            else if (condition_down(pos) == true) {
                sequence[index] = 'd';
                pos->row++;
                mov_down++;
            }
        }
    }
    update_matrix(sequence);
}

/******************************************************************************
 * Find the correct path moving row first
 *****************************************************************************/
static void path_row_first(char *sequence, struct position *pos, int size)
{
    for (int i = 0; i < size; i++) {
        move_row(sequence, pos, i);
        move_column(sequence, pos, i);
    }
}

/******************************************************************************
 * Find the correct path moving columns first
 *****************************************************************************/
static void path_column_first(char *sequence, struct position *pos, int size)
{
    for (int i = 0; i < size; i++) {
        move_column(sequence, pos, i);
        move_row(sequence, pos, i);
    }
}

/******************************************************************************
 * Initialize
 *****************************************************************************/
void init_path(const char *input, char *output)
{
    mov_right = 0;
    mov_down = 0;
    init_matrix();

    for (int i = 0; i < strlen(input); i++) {
        output[i] = input[i];

        switch (output[i]) {
            case 'r':
                mov_right++;
            break;
            case 'd':
                mov_down++;
            break;
            case 'l':
                mov_right--;
            break;
            case 'u':
                mov_down--;
            break;
            default:
            break;
        }
    }
}

/******************************************************************************
 * Find the correct path
 *****************************************************************************/
void correct_path(const char *input, char *output)
{
    int size = strlen(input);
    struct position pos = {.row = 0, .column = 0};

    /* first attempt: move rows first */
    init_path(input, output);
    path_row_first(output, &pos, size);

    if ((pos.row != TARGET) || (pos.column != TARGET)) {
        /* didn't end in (R4, C4), try again and move columns first */
        pos.row = 0;
        pos.column = 0;
        init_path(input, output);
        path_column_first(output, &pos, size);
    }
}

/******************************************************************************
 * Display the path on the matrix
 *****************************************************************************/
void correct_path_display(void)
{
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j ++) {
            printf("%d ", matrix[i][j]);
            if (j == (MATRIX_SIZE - 1)) {
                printf("\n");
            }
        }
    }
}
