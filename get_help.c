#include "shell.h"

/**
 * get_help - retrieves help messages according builtin
 * @data_st: data structure (args and input)
 * Return: Return 0
*/
int get_help(data_shell *data_st)
{

	if (data_st->args[1] == 0)
		general_help();
	else if (_strcmp(data_st->args[1], "setenv") == 0)
		help_setenv();
	else if (_strcmp(data_st->args[1], "env") == 0)
		help_env();
	else if (_strcmp(data_st->args[1], "unsetenv") == 0)
		help_unsetenv();
	else if (_strcmp(data_st->args[1], "help") == 0)
		help();
	else if (_strcmp(data_st->args[1], "exit") == 0)
		help_exit();
	else if (_strcmp(data_st->args[1], "cd") == 0)
		help_cd();
	else if (_strcmp(data_st->args[1], "alias") == 0)
		help_alias();
	else
		write(STDERR_FILENO, data_st->args[0],
		      _strlen(data_st->args[0]));

	data_st->status = 0;
	return (1);
}
