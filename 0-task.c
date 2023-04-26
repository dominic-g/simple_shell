#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "shell.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "shell.h"

#define MAX_CMD_LEN 1024

/**
 * prompt - Displays the prompt symbol to indicate
 * that the shell is ready to receive input.
 */
void prompt(void)
{
    printf("$ ");
}

/**
 * read_command - Reads a command from the user's input using fgets() function
 * and returns it as a string. If fgets() returns NULL,
 * it means that the end of the input has been reached
 * and the program should exit.
 *
 * Return: The command string entered by the user.
 */
char *read_command(void)
{
    char cmd[MAX_CMD_LEN];
    if (fgets(cmd, MAX_CMD_LEN, stdin) == NULL)
    {
        printf("\n");
        exit(0);
    }
    cmd[strcspn(cmd, "\n")] = '\0';
    return (strdup(cmd));
}

/**
 * parse_command - Takes a command string as input
 * and splits it into individual words
 * using the first word as the command and the
 * remaining words as its arguments.
 * @cmd: The command string to be parsed.
 * @args: An array to store the parsed words.
 */
void parse_command(char *cmd, char **args)
{
    char *arg;
    int i = 0;
    arg = strtok(cmd, " \t\n");
    while (arg != NULL)
    {
        args[i++] = arg;
        arg = strtok(NULL, " \t\n");
    }
    args[i] = NULL;
}

/**
 * execute_command - Execute a command.
 * @args: An array of arguments.
 *
 * Return: 1 if the shell should continue running, 0 if it should exit.
 */
void execute_command(char **args)
{
    int status;
    pid_t pid = fork();
    if (pid == -1)
    {
        perror("fork");
        exit(1);
    }
    else if (pid == 0)
    {
        /* Child process */
        char *path;
        char *dir;
        char command[MAX_CMD_LEN];
        int found = 0;
        path = getenv("PATH");
        while ((dir = strtok(path, ":")) != NULL)
        {
            path = NULL;
            sprintf(command, "%s/%s", dir, args[0]);
            if (access(command, F_OK) == 0)
            {
                found = 1;
                break;
            }
        }
        if (!found)
        {
            fprintf(stderr, "%s: %s: command not found\n", args[0], args[0]);
            exit(127);
        }
        if (execve(command, args, environ) == -1)
        {
            perror(args[0]);
            exit(126);
        }
    }
    else
    {
        /* Parent process */
        if (wait(&status) == -1)
        {
            perror("wait");
            exit(1);
        }
        if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
            return;
        else if (WIFEXITED(status))
            fprintf(stderr, "%s: %s: exit status %d\n", args[0], args[0], WEXITSTATUS(status));
        else if (WIFSIGNALED(status))
            fprintf(stderr, "%s: %s: terminated by signal %d\n", args[0], args[0], WTERMSIG(status));
    }
}


/**
 * main - Entry point of the simple shell
 *
 * Return: Always 0 on success
 */
int main(void)
{
    char *cmd;
    char *args[MAX_CMD_LEN];

    while (1)
    {
        prompt();
        cmd = read_command();
        parse_command(cmd, args);
        execute_command(args);
        free(cmd);
    }

    return (0);
}