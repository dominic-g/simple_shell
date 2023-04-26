#include "shell.h"
/**
 * handle_exit - Handles exit of execute function
 *
 * Return: The the exit command.
 */
int handle_exit(char **args)
{
if (args[1] != NULL){
	printf("%d\n", _atoi(args[1]));
	exit(_atoi(args[1]));
}
else
exit(0);
}

/**
 * handle_env - Env.
 *
 * Return: 1, 0 if it should exit.
 */
int handle_env()
{
char **env = environ;
while (*env)
{
printf("%s\n", *env);
env++;
}
return 1;
}

/**
 * search_command - Execute a command.
 * @args: An array of arguments.
 *
 * Return: 1 if 0 if it should exit.
 */
int search_command(char **args)
{
int found = 0;
char *path = getenv("PATH");
char *curr_dir, *path_copy;
char command[MAX_CMD_LEN];

if (path == NULL)
{
    fprintf(stderr, "Could not get PATH environment variable\n");
    return 0;
}

path_copy = _strdup(path);
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
return 0;

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
char command[MAX_CMD_LEN];

if (_strcmp(args[0], "exit") == 0)
    return handle_exit(args);

if (_strcmp(args[0], "env") == 0)
    return handle_env(args);

if (search_command(args) != 0)
    return 1;

pid = fork();
if (pid == -1)
{
    perror("fork");
    exit(1);
}
else if (pid == 0)
{
    if (execve(command, args, environ) == -1)
    {
        perror(args[0]);
        exit(126);
    }
}
else
{
    if (wait(&status) == -1)
    {
        perror("wait");
        exit(1);
    }
    if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
        return 1;
}
return 1;
}