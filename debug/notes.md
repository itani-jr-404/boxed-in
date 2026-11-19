# Debugging notes (Sprint 1)

We followed the approach from Lecture 7: compile with warnings first, then
Valgrind, then GDB for anything that still looks wrong.

## 1. Compiler warnings

The Makefile builds with `-Wall -Wextra -Werror -g`, so any warning stops the
build. We also built with `-O0`, `-O1`, `-O2` and `-O3` (gcc on Alpine and
clang on macOS):

    make clean && make CFLAGS="-Wall -Wextra -Werror -std=c11 -g -O3"

At `-O3`, gcc on Alpine gave:

    input.c:13: error: 'line' may be used uninitialized [-Werror=maybe-uninitialized]

`fgets` fills the buffer, so it was not a real read of garbage, but Alpine's
fortified `fgets` is declared as reading its buffer too. With `-Werror` this
stopped the build, so we initialize the buffer (`char line[LINE_SIZE] = "";`).
All levels build cleanly after that (commit "Fix -O3 build error").

## 2. Valgrind

The board is allocated with `malloc` (one array of row pointers per grid), so
Valgrind can check every access and every `free`. `make valgrind` runs the
game on three input files in `tests/`:

- `win_game.txt` full game where player A wins 13 to 7
- `tie_game.txt` full game that ends 10 to 10
- `bad_input.txt` letters, missing numbers, diagonal and out of range moves,
  a line drawn twice, then the input ends in the middle of the game

Result for all three, at every optimization level: 0 errors, 17 allocs and
17 frees, no leaks. Full logs: `valgrind_win_game.txt`, `valgrind_bad_input.txt`.

## 3. GDB

`make gdb` loads `commands.gdb`, which breaks in `drawLine` and in `claimBox`
only for box (0, 0), then runs the win game. We used it to check that:

- a horizontal line from (0,0) to (0,1) checks the box above (r = -1, skipped)
  and the box below (0,0)
- `print *board` shows the right sizes (rows = 4, cols = 5) and `claimed`
- with `break claimBox if r == 3 && c == 4` and `finish`, the box is only
  given once all four sides are set

Transcript: `gdb_session.txt`. Useful commands: `break`, `run < file`,
`next`, `step`, `print`, `backtrace`, `finish`, `watch board->claimed`.
