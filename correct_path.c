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
#include <string.h>
#include <stdbool.h>
#include "correct_path.h"

#define GRID_SIZE   5
#define TARGET      (GRID_SIZE - 1)

/* Note: 4 times right + 4 times down get us to the target cell E5 */
unsigned int mov_right;
unsigned int mov_down;

unsigned int grid[GRID_SIZE][GRID_SIZE];

struct position {
    int row;
    int column;
};

/******************************************************************************
 * Initialize grid
 *****************************************************************************/
static void init_grid(void)
{
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            grid[i][j] = 0;
        }
    }
    grid[0][0] = 1;
}

/******************************************************************************
 * Update the path on the grid until the first '?'
 *****************************************************************************/
static void update_grid(char *sequence)
{
    int row = 0;
    int column = 0;

    for (int i = 0; i < strlen(sequence); i++) {
        switch(sequence[i]) {
            case 'r':
                grid[row][++column] = 1;
            break;
            case 'd':
                grid[++row][column] = 1;
            break;
            case 'l':
                grid[row][--column] = 1;
            break;
            case 'u':
                grid[--row][column] = 1;
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
 *****************************************************************************/
static bool condition_right(struct position *pos)
{
    if ((pos->column < TARGET) && (grid[pos->row][pos->column + 1] == 0)) {
        return true;
    }
    else {
        return false;
    }
}

/******************************************************************************
 * Check if it's possible to move left
 *****************************************************************************/
static bool condition_left(struct position *pos)
{
    if ((pos->column > 0) && (grid[pos->row][pos->column - 1] == 0)) {
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
    int size = strlen(sequence);

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
    update_grid(sequence);
}

/******************************************************************************
 * Check if it's possible to move up
 *****************************************************************************/
static bool condition_up(struct position *pos)
{
    if ((pos->row > 0) && (grid[pos->row - 1][pos->column] == 0)) {
        return true;
    }
    else {
        return false;
    }
}

/******************************************************************************
 * Check if it's possible to move down
 *****************************************************************************/
static bool condition_down(struct position *pos)
{
    if ((pos->row < TARGET) && (grid[pos->row + 1][pos->column] == 0)) {
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
    int size = strlen(sequence);

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
    update_grid(sequence);
}



/******************************************************************************
 * Find the correct path
 *****************************************************************************/
void correct_path(const char *input, char *output)
{
    int size = strlen(input);
    struct position pos = {.row = 0, .column = 0};

    mov_right = 0;
    mov_down = 0;
    init_grid();

    /* copy the input to a local variable */
    for (int i = 0; i < size; i++) {
        output[i] = input[i];

        switch (output[i]) {
            case 'r':
                mov_right++;
                //pos.column++;
            break;
            case 'd':
                mov_down++;
                //pos.row++;
            break;
            case 'l':
                mov_right--;
                //pos.column--;
            break;
            case 'u':
                mov_down--;
                //pos.row--;
            break;
            case '?':
            default:
            break;
        }
    }

    for (int j = 0; j < size; j++) {
        move_column(output, &pos, j);
        move_row(output, &pos, j);
    }

    //correct_path_display();

    if ((pos.row != TARGET) || (pos.column != TARGET)) {
        printf("end in cell: {row %d, column %d}\n", pos.row, pos.column);
    }
}

/******************************************************************************
 * Display the path on the grid
 *****************************************************************************/
void correct_path_display(void)
{
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j ++) {
            printf("%d ", grid[i][j]);
            if (j == (GRID_SIZE - 1)) {
                printf("\n");
            }
        }
    }
}
