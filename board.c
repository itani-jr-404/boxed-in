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

static int isDot(const Board *board, int r, int c)
{
    return r >= 0 && r <= board->rows && c >= 0 && c <= board->cols;
}

int checkMove(const Board *board, int r1, int c1, int r2, int c2)
{
    if (!isDot(board, r1, c1) || !isDot(board, r2, c2)) {
        return MOVE_OUT_OF_RANGE;
    }

    if (r1 == r2 && abs(c1 - c2) == 1) {
        if (board->hLines[r1][c1 < c2 ? c1 : c2]) {
            return MOVE_TAKEN;
        }
        return MOVE_OK;
    }
    if (c1 == c2 && abs(r1 - r2) == 1) {
        if (board->vLines[r1 < r2 ? r1 : r2][c1]) {
            return MOVE_TAKEN;
        }
        return MOVE_OK;
    }
    return MOVE_NOT_ADJACENT;
}

/* Gives box (r, c) to player if all four sides are drawn. */
static int claimBox(Board *board, int r, int c, char player)
{
    if (r < 0 || r >= board->rows || c < 0 || c >= board->cols) {
        return 0;
    }
    if (!board->hLines[r][c] || !board->hLines[r + 1][c]
        || !board->vLines[r][c] || !board->vLines[r][c + 1]) {
        return 0;
    }
    board->owners[r][c] = player;
    board->claimed++;
    return 1;
}

/* Draws a line that already passed checkMove and returns the number of
   boxes it completed (0, 1 or 2). */
int drawLine(Board *board, int r1, int c1, int r2, int c2, char player)
{
    int r, c;
    int completed = 0;

    if (r1 == r2) {
        c = c1 < c2 ? c1 : c2;
        board->hLines[r1][c] = 1;
        completed += claimBox(board, r1 - 1, c, player);
        completed += claimBox(board, r1, c, player);
    } else {
        r = r1 < r2 ? r1 : r2;
        board->vLines[r][c1] = 1;
        completed += claimBox(board, r, c1 - 1, player);
        completed += claimBox(board, r, c1, player);
    }
    return completed;
}

int isBoardFull(const Board *board)
{
    return board->claimed == board->rows * board->cols;
}
