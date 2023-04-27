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
* main - Entry point of the simple shell
*
* @argc: The commands number.
* @argv: An array to store the parsed words.
*
* Return: Always 0 on success
*/
int main(int argc, char *argv[])
{
char *cmd;
char *name;
char *args[MAX_CMD_LEN];
int run, interactive_mode;
interactive_mode = argc;

interactive_mode = isatty(STDIN_FILENO);
run = 1;
name = argv[0];
while (run)
{
if (interactive_mode)
prompt();
cmd = my_getline_();
if (cmd != NULL)
{
parse_command(cmd, args);
run = execute_command(args, interactive_mode, name) && interactive_mode;
}
free(cmd);
}

return (0);
}

