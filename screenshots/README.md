# Screenshots (Alpine Linux VM in UTM)

| File | What it shows |
| --- | --- |
| `01_boot_into_game.png` | The VM boots straight into the game, no login |
| `02_moves_and_box.png` | Moves on the board; B closes a box, scores and plays again |
| `03_invalid_moves.png` | Out of range, not adjacent, already drawn and non-numeric input are rejected |
| `04_alpine_version.png` | `cat /etc/os-release` and `uname -m`: Alpine 3.24.4, aarch64 |
| `05_compile.png` | `make clean` and `make` with `-Wall -Wextra -Werror`, no warnings |
| `06_full_game_winner.png` | A full game from `tests/win_game.txt`, A wins 13 to 7 |
| `07_valgrind_win_game.png` | Valgrind on a full game: 17 allocs, 17 frees, 0 errors |
| `08_valgrind_bad_input.png` | Valgrind on bad input ending mid-game: no leaks, 0 errors |
| `09_gdb_breakpoint.png` | GDB: breakpoint in `drawLine`, `info args`, `print *board`, `backtrace` |
| `10_gdb_box_claimed.png` | GDB: conditional breakpoint where box (0,0) is awarded, `finish` returns 1 |
| `11_autostart_inittab.png` | `/etc/inittab`: tty1 runs the game instead of a login prompt |
