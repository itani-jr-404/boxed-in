#include <stdio.h>
#include <stdlib.h>
#include "board.h"

static char **createGrid(int rows, int cols, char fill)
{
    char **grid;
    int i, j;

    grid = malloc(rows * sizeof(char *));
    if (grid == NULL) {
        return NULL;
    }

    for (i = 0; i < rows; i++) {
        grid[i] = malloc(cols * sizeof(char));
        if (grid[i] == NULL) {
            for (j = 0; j < i; j++) {
                free(grid[j]);
            }
            free(grid);
            return NULL;
        }
        for (j = 0; j < cols; j++) {
            grid[i][j] = fill;
        }
    }
    return grid;
}

static void freeGrid(char **grid, int rows)
{
    int i;

    if (grid == NULL) {
        return;
    }
    for (i = 0; i < rows; i++) {
        free(grid[i]);
    }
    free(grid);
}

Board *createBoard(int rows, int cols)
{
    Board *board;

    board = malloc(sizeof(Board));
    if (board == NULL) {
        return NULL;
    }

    board->rows = rows;
    board->cols = cols;
    board->claimed = 0;
    board->hLines = createGrid(rows + 1, cols, 0);
    board->vLines = createGrid(rows, cols + 1, 0);
    board->owners = createGrid(rows, cols, ' ');

    if (board->hLines == NULL || board->vLines == NULL
        || board->owners == NULL) {
        freeBoard(board);
        return NULL;
    }
    return board;
}

void freeBoard(Board *board)
{
    if (board == NULL) {
        return;
    }
    freeGrid(board->hLines, board->rows + 1);
    freeGrid(board->vLines, board->rows);
    freeGrid(board->owners, board->rows);
    free(board);
}

void printBoard(const Board *board)
{
    int i, j;

    printf(" ");
    for (j = 0; j <= board->cols; j++) {
        printf(" %d", j);
    }
    printf("\n");

    for (i = 0; i <= board->rows; i++) {
        printf("%d ", i);
        for (j = 0; j <= board->cols; j++) {
            printf(".");
            if (j < board->cols) {
                printf("%c", board->hLines[i][j] ? '-' : ' ');
            }
        }
        printf("\n");

        if (i < board->rows) {
            printf("  ");
            for (j = 0; j <= board->cols; j++) {
                printf("%c", board->vLines[i][j] ? '|' : ' ');
                if (j < board->cols) {
                    printf("%c", board->owners[i][j]);
                }
            }
            printf("\n");
        }
    }
}
