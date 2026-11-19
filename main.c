#include <stdio.h>
#include "board.h"

int main(void)
{
    Board *board;

    board = createBoard(BOX_ROWS, BOX_COLS);
    if (board == NULL) {
        printf("Error: could not create the board.\n");
        return 1;
    }

    printBoard(board);
    freeBoard(board);
    return 0;
}
