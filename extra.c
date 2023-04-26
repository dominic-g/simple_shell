#include "shell.h"

#define BUFFER_SIZE 1024

/**
 * my_getline - Uses static variables to keep track of the current position in the buffer,
 * the length of the buffer, and the characters that
 * have already been read from standard input
 *
 * Return: The command string entered by the user.
 */
char *my_getline(void)
{
    static char buffer[BUFFER_SIZE];
    static int pos = 0;
    static int len = 0;

    char *line = malloc(BUFFER_SIZE);
    int line_pos = 0;
    char c;

    while (1) {
        if (pos >= len) {
            len = read(STDIN_FILENO, buffer, BUFFER_SIZE);
            pos = 0;
        }

        if (len == 0) {
            free(line);
            return NULL;
        }

        c = buffer[pos++];

        if (c == '\n') {
            line[line_pos] = '\0';
            return line;
        }

        line[line_pos++] = c;

        if (line_pos >= BUFFER_SIZE) {
            line = realloc(line, BUFFER_SIZE * 2);
            if (!line) {
                fprintf(stderr, "Error: memory allocation failed\n");
                exit(1);
            }
        }
    }
}
