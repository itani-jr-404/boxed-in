#include <stdio.h>
#include "game.h"

int main(void)
{
    Game game;
    int finished;
    int ch;

    do {
        /* clear the screen so the game is the first thing shown on the VM */
        printf("\033[H\033[J");

        if (!initGame(&game)) {
            printf("Error: could not create the board.\n");
            return 1;
        }
        finished = runGame(&game);
        endGame(&game);

        if (finished) {
            printf("Press Enter to play again.\n");
            ch = getchar();
            while (ch != '\n' && ch != EOF) {
                ch = getchar();
            }
            finished = ch != EOF;
        }
    } while (finished);

    return 0;
}
