#include <stdio.h>
#include "game.h"
#include "input.h"

#define STARS "*********************************************************************"

static char playerName(int player)
{
    return player == 0 ? 'A' : 'B';
}

static void printScores(const Game *game)
{
    printf("%s\n", STARS);
    printf("Player A score: %d\n", game->scores[0]);
    printf("Player B score: %d\n", game->scores[1]);
    printf("%s\n", STARS);
}

static void printMoveError(int error)
{
    if (error == MOVE_OUT_OF_RANGE) {
        printf("Invalid move: rows go from 0 to %d and columns from 0 to %d.\n",
               BOX_ROWS, BOX_COLS);
    } else if (error == MOVE_NOT_ADJACENT) {
        printf("Invalid move: the two dots must be next to each other.\n");
    } else if (error == MOVE_TAKEN) {
        printf("Invalid move: that line is already drawn.\n");
    }
}

static void printWinner(const Game *game)
{
    printf("Game over!\n");
    if (game->scores[0] > game->scores[1]) {
        printf("Player A wins with %d boxes.\n", game->scores[0]);
    } else if (game->scores[1] > game->scores[0]) {
        printf("Player B wins with %d boxes.\n", game->scores[1]);
    } else {
        printf("It's a tie, %d boxes each.\n", game->scores[0]);
    }
}

int initGame(Game *game)
{
    game->board = createBoard(BOX_ROWS, BOX_COLS);
    game->scores[0] = 0;
    game->scores[1] = 0;
    game->current = 0;
    return game->board != NULL;
}

void runGame(Game *game)
{
    int r1, c1, r2, c2;
    int status, gained;

    printBoard(game->board);
    while (!isBoardFull(game->board)) {
        printf("Player %c's turn. Enter the row and column of the first dot "
               "(e.g., A0 -> 0 0) and second dot:\n",
               playerName(game->current));

        status = readMove(&r1, &c1, &r2, &c2);
        if (status == INPUT_END) {
            printf("\nNo more input, the game was stopped.\n");
            return;
        }
        if (status == INPUT_BAD) {
            printf("Invalid input: enter 4 numbers, for example 0 0 0 1\n");
            continue;
        }

        status = checkMove(game->board, r1, c1, r2, c2);
        if (status != MOVE_OK) {
            printMoveError(status);
            continue;
        }

        gained = drawLine(game->board, r1, c1, r2, c2,
                          playerName(game->current));
        game->scores[game->current] += gained;

        /* a player who completes a box plays again */
        if (gained == 0) {
            game->current = 1 - game->current;
        }

        printScores(game);
        printBoard(game->board);
    }
    printWinner(game);
}

void endGame(Game *game)
{
    freeBoard(game->board);
    game->board = NULL;
}
