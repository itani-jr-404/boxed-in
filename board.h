#ifndef BOARD_H
#define BOARD_H

#define BOX_ROWS 4
#define BOX_COLS 5

typedef struct {
    int rows;
    int cols;
    char **hLines; /* (rows + 1) x cols, 1 if the line is drawn */
    char **vLines; /* rows x (cols + 1) */
    char **owners; /* rows x cols, ' ' if nobody owns the box yet */
    int claimed;
} Board;

Board *createBoard(int rows, int cols);
void freeBoard(Board *board);
void printBoard(const Board *board);

#endif
