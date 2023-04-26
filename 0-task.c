#include "shell.h"


/**
 * prompt - Displays the prompt symbol to indicate
 * that the shell is ready to receive input.
 */
void prompt(void)
{
    printf("$ ");
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
    arg = _strtok(cmd, " \t\n");
    while (arg != NULL)
    {
        args[i++] = arg;
        arg = _strtok(NULL, " \t\n");
    }
    args[i] = NULL;
}

/**
 * execute_command - Execute a command.
 * @args: An array of arguments.
 *
 * Return: 1 if the shell should continue running, 0 if it should exit.
 */
int execute_command(char **args)
{
    int status;
    pid_t pid;
    char *path = getenv("PATH");
    char *curr_dir, *path_copy;
    char command[MAX_CMD_LEN];
    int found = 0;

    if (_strcmp(args[0], "exit") == 0)
        return 0;

    if (path == NULL)
    {
        fprintf(stderr, "Could not get PATH environment variable\n");
        return 0;
    }

    if (_strcmp(args[0], "env") == 0)
    {
        char **env = environ;
        while (*env)
        {
            printf("%s\n", *env);
            env++;
        }
        return 1;
    }

    path_copy = strdup(path);
    if (path_copy == NULL)
    {
        perror("strdup");
        exit(1);
    }

    while ((curr_dir = _strtok(path_copy, ":")) != NULL)
    {
        snprintf(command, MAX_CMD_LEN, "%s/%s", curr_dir, args[0]);
        if (access(command, F_OK) == 0)
        {
            found = 1;
            break;
        }
        path_copy = NULL;
    }

    free(path_copy);

    if (!found)
    {
        perror(args[0]);
        return 1;
    }

    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        exit(1);
    }
    else if (pid == 0)
    {
        /* Child process */
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
            return 1;
        /*else if (WIFEXITED(status))
            fprintf(stderr, "%s: exit status %d\n", args[0], WEXITSTATUS(status));
        else if (WIFSIGNALED(status))
            fprintf(stderr, "%s: terminated by signal %d\n", args[0], WTERMSIG(status));*/
    }
    return 1;
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
    int run;
    run = 1;

    while (run)
    {
        prompt();
        cmd = my_getline_();
        if (cmd != NULL) {
            parse_command(cmd, args);

            run = execute_command(args);
        }
        free(cmd);
    }

    return (0);
}

