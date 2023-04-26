#include "shell.h"

#define BUFFER_SIZE 1024

/**
 * my_getline_ - Uses static variables to keep track of the current position in the buffer,
 * the length of the buffer, and the characters that
 * have already been read from standard input
 *
 * Return: The command string entered by the user.
 */
char *my_getline_(void)
{
    char cmd[MAX_CMD_LEN];
    if (fgets(cmd, MAX_CMD_LEN, stdin) == NULL)
    {
        printf("\n");
        exit(0);
    }
    if (cmd[0] == '\n')
    {
        return NULL;
    }
    cmd[_strcspn(cmd, "\n")] = '\0';
    return _strdup(cmd);
}
