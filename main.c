#include <stdio.h>
#include "game.h"

int main(void)
{
    Game game;

    if (!initGame(&game)) {
        printf("Error: could not create the board.\n");
        return 1;
    }

    runGame(&game);
    endGame(&game);
    return 0;
}
