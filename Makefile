CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11 -g
OUTPUT = dotsandboxes
SOURCES = main.c game.c board.c input.c
OBJECTS = $(SOURCES:.c=.o)

$(OUTPUT): $(OBJECTS)
	$(CC) -o $@ $^

main.o: main.c game.h board.h
	$(CC) $(CFLAGS) -c -o $@ $<

game.o: game.c game.h board.h input.h
	$(CC) $(CFLAGS) -c -o $@ $<

board.o: board.c board.h
	$(CC) $(CFLAGS) -c -o $@ $<

input.o: input.c input.h
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: clean
clean:
	rm -f *.o $(OUTPUT)
