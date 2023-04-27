#include "shell.h"


/**
* prompt - Displays the prompt symbol to indicate
* that the shell is ready to receive input.
*/
void prompt(void)
{
	write(STDOUT_FILENO, "#Simple Shell$ ", 15);
}

/**
* _printfi - Output content
* that the shell is ready to receive input.
* @text: just a btw for this comment in the code
*/
void _printfi(int text)
{
	write(STDOUT_FILENO, &text, _strlen(_itoa(text)));
}
/**
* _printfc - Output content
* that the shell is ready to receive input.
* @text: the same as the sister up there
*/
void _printfc(char *text)
{
	write(STDOUT_FILENO, text, _strlen(text));
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
int main(int argc, char **argv)
{
char *cmd;
char *name;
data_shell data_st;
char *args[MAX_CMD_LEN];
int run, interactive_mode, _eof;
(void) argc;

interactive_mode = isatty(STDIN_FILENO);
run = 1;
name = argv[0];

set_data(&data_st, argv);
while (run)
{
if (interactive_mode)
	prompt();
cmd = my_getline_(&_eof);
if (_eof != -1)
cmd = remove_comment(cmd);
if (check_syntax_error(&data_st, cmd) == 1)
{
	free(cmd);
	continue;
}

if (cmd != NULL)
{
parse_command(cmd, args);
run = execute_command(args, interactive_mode, name) && interactive_mode;
}
free(cmd);
}

free_data(&data_st);
return (0);
}


