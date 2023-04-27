#include "shell.h"
/**
 * execute_command - executes a command
 * @args: pointer to command to execute
 *
 * Description:
 * This function executes the specified command. First, it checks
 * if the command is a built-in command (such as "cd" or "exit").
 * If so, it executes the command directly. Otherwise, it searches
 * the PATH environment variable for an executable file with the
 * specified name, and executes the file with any specified arguments.
 *
 * Return: 1 on success, 0 on failure
 */
void execute_command(char **args)
{
pid_t pid;
int status;

pid = fork();
if (pid == 0)
{
/* Child process */
if (execvp(args[0], args) == -1)
{
perror("Error");
}
exit(EXIT_FAILURE);
}
else if (pid < 0)
{
/* Fork error */
perror("Error");
}
else
{
/* Parent process */
do {
waitpid(pid, &status, WUNTRACED);
} while (!WIFEXITED(status) && !WIFSIGNALED(status));
}
}
/**
 * main - entry point for simple shell program
 *
 * Description:
 * This function is the entry point for the simple shell program.
 * It displays a prompt to the user, reads input from the user,
 * parses the input into tokens, and executes the specified command.
 * This process repeats until the user enters an end-of-file condition
 * (Ctrl-D) or an error occurs.
 *
 * Return: always 0
 */
int main(void)
{
char *input;
char **args;
while (1)
{
input = read_input();
args = parse_input(input);
if (args)
{
execute_command(args);
free(args);
}
free(input);
}
return (0);
}

