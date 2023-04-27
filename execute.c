#include "shell.h"
/**
* handle_exit - Handles exit of execute function
* @args: handle_exit function argument
* Return: The the exit command.
*/
int handle_exit(char **args)
{
if (args[1] != NULL)
{
_printfi(_atoi(args[1]));
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
int handle_env(void)
{
char **env = environ;
while (*env)
{
_printfc(*env);
_printfc("\n");
env++;
}
return (1);
}
/**
* check_path - Env.
*
* @path_copy: The command string to be parsed.
* Return: void.
*/
void check_path(char *path_copy)
{
if (path_copy == NULL)
{
perror("strdup");
exit(1);
}
}

/**
* search_command - Execute a command.
* @args: An array of arguments.
* @command: The command string to be parsed.
* @name: The command named called.
*
* Return: 1 if 0 if it should exit.
*/
int search_command(char **args, char *command, char *name)
{
int found = 0;
if (args[0][0] == '/')
{
if (access(args[0], F_OK) == 0)
{
found = 1;
_strncpy(command, args[0], MAX_CMD_LEN);
}
}
else
{
char *path = getenv("PATH");
char *curr_dir, *path_copy;
if (path == NULL)
{
fprintf(stderr, "Could not get PATH environment variable\n");
return (0);
}
path_copy = _strdup(path);
check_path(path_copy);
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
}
if (!found)
{
perror(name);
return (1);
}
return (0);
}


/**
* execute_command - Execute a command.
* @args: An array of arguments.
* @interactive_mode: The command string to be parsed.
* @name: The command named called.
*
* Return: 1 if the shell should continue running, 0 if it should exit.
*/
int execute_command(char **args, int interactive_mode, char *name)
{
int status;
pid_t pid;
char command[MAX_CMD_LEN];
if (_strcmp(args[0], "exit") == 0)
return (handle_exit(args));
if (_strcmp(args[0], "env") == 0)
return (handle_env());
if (_strcmp(args[0], "cd") == 0)
return (handle_cd(args[1]));
if (search_command(args, command, name) != 0)
return (1);
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
return (1);
}
if (interactive_mode && false)
prompt();
return (0);
}
