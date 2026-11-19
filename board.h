#ifndef BOARD_H
#define BOARD_H

#define BOX_ROWS 4
#define BOX_COLS 5

#define MOVE_OK 0
#define MOVE_OUT_OF_RANGE 1
#define MOVE_NOT_ADJACENT 2
#define MOVE_TAKEN 3

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
int checkMove(const Board *board, int r1, int c1, int r2, int c2);
int drawLine(Board *board, int r1, int c1, int r2, int c2, char player);
int isBoardFull(const Board *board);

#endif
