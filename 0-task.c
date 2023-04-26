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
* @argc: The command string to be parsed.
* @argv: An array to store the parsed words.
* Return: Always 0 on success
*/
int main(int argc, char **argv)
{
char *cmd;
char *args[MAX_CMD_LEN];
int run, interactive_mode;

if (argc > 1)
interactive_mode = 0;
else
interactive_mode = 1;

run = 1;

while (run)
{
if (interactive_mode)
prompt();
cmd = argv[1];
cmd = my_getline_();
if (cmd != NULL)
{
parse_command(cmd, args);

run = execute_command(args, interactive_mode);
}
free(cmd);
}

return (0);
}
