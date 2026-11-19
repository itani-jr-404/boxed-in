#include <stdio.h>
#include <string.h>
#include "input.h"

#define LINE_SIZE 100

int readMove(int *r1, int *c1, int *r2, int *c2)
{
    char line[LINE_SIZE] = "";
    char extra[2];
    int ch;

    if (fgets(line, LINE_SIZE, stdin) == NULL) {
        return INPUT_END;
    }

    /* drop the rest of a line that was too long for the buffer */
    if (strchr(line, '\n') == NULL) {
        ch = getchar();
        while (ch != '\n' && ch != EOF) {
            ch = getchar();
        }
        return INPUT_BAD;
    }

    if (sscanf(line, "%d %d %d %d %1s", r1, c1, r2, c2, extra) != 4) {
        return INPUT_BAD;
    }
    return INPUT_OK;
}
