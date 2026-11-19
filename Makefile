CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11 -g
OUTPUT = dotsandboxes
SOURCES = main.c board.c
OBJECTS = $(SOURCES:.c=.o)

$(OUTPUT): $(OBJECTS)
	$(CC) -o $@ $^

main.o: main.c board.h
	$(CC) $(CFLAGS) -c -o $@ $<

board.o: board.c board.h
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: clean
clean:
	rm -f *.o $(OUTPUT)
