# Dots and Boxes

CMPS 241 course project (Fall 2026/27), Team 5: Ali Al Itani and Mohamad Alame.

A console version of Dots and Boxes written in C. The board has 4 x 5 boxes
(5 rows and 6 columns of dots).

Sprint 1: two-player game (Player A vs Player B).

## Build and run

    make
    ./dotsandboxes

`make clean` removes the object files and the executable.

## How to play

On your turn, type the row and column of two dots next to each other, for
example `0 0 0 1` draws the line between dot (0,0) and dot (0,1).
If your line closes a box, the box gets your letter and you play again.
The game ends when all 20 boxes are taken; the player with more boxes wins.

Wrong input (letters, dots that are not next to each other, out of range or
an existing line) is rejected and the same player is asked again.

## Files

| File | Contents |
| --- | --- |
| `main.c` | starts a game, asks to play again at the end |
| `game.c/h` | turns, scores, winner |
| `board.c/h` | board memory, printing, move checks, box completion |
| `input.c/h` | reads one move from the keyboard |
| `tests/` | input files used for testing and Valgrind |
| `debug/` | GDB commands, Valgrind and GDB output, debugging notes |
| `alpine/setup.sh` | sets up the Alpine VM to start the game on boot |

## Debugging

    make valgrind   # runs the game under Valgrind on the files in tests/
    make gdb        # opens gdb with the breakpoints in debug/commands.gdb

See `debug/notes.md`.

## Alpine VM

Install Alpine Linux in the VM (`setup-alpine`, then install to disk). Copy
this folder into the VM, then as root:

    sh alpine/setup.sh
    reboot

The script installs gcc, make, gdb and valgrind, builds the game, copies it to
`/usr/local/bin`, and replaces the login prompt on tty1 with the game in
`/etc/inittab`. After a reboot the game opens directly without a login. When
it exits, init starts it again. A normal login is still available on tty2
(Alt+F2).

If the VM window is a serial console instead of a normal screen, run
`sh alpine/setup.sh ttyAMA0` so the game starts there.

## Complexity

Let the board have R x C boxes (here 4 x 5).

- Checking a move (`checkMove`): O(1), only the two dots and one line are read.
- Checking if a move completes a box (`drawLine`, `claimBox`): O(1). A line
  touches at most two boxes and each box needs 4 lookups.
- Checking if the game is over (`isBoardFull`): O(1), we keep a count of
  claimed boxes instead of scanning the board.
- Printing the board: O(R x C).
- Creating and freeing the board: O(R x C) time and memory.
