#ifndef GAME_H
#define GAME_H

#include "board.h"

typedef struct {
    Board *board;
    int scores[2];
    int current; /* 0 for player A, 1 for player B */
} Game;

int initGame(Game *game);
int runGame(Game *game);
void endGame(Game *game);

#endif
