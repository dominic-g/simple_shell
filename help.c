#include "shell.h"

/**
 * get_help - retrieves help messages according builtin
 * @data_st: data structure (args and input)
 * Return: Return 0
*/
int get_help(custom_struct *data_st)
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
/**
 * help_env - Help information for the builtin env
 * Return: no return
 */
void help_env(void)
{
	char *help = "env: env [option] [name=value] [command [args]]\n\t";

	write(STDOUT_FILENO, help, _strlen(help));
	help = "Print the enviroment of the shell.\n";
	write(STDOUT_FILENO, help, _strlen(help));

}

/**
 * help_setenv - Help information for the builtin setenv
 * Return: no return
 */
void help_setenv(void)
{

	char *help = "setenv: setenv (const char *name, const char *value,";

	write(STDOUT_FILENO, help, _strlen(help));
	help = "int replace)\n\t";
	write(STDOUT_FILENO, help, _strlen(help));
	help = "Add a new definition to the environment\n";
	write(STDOUT_FILENO, help, _strlen(help));
}
/**
 * help_unsetenv - Help information for the builtin unsetenv
 * Return: no return
 */
void help_unsetenv(void)
{
	char *help = "unsetenv: unsetenv (const char *name)\n\t";

	write(STDOUT_FILENO, help, _strlen(help));
	help = "Remove an entry completely from the environment\n";
	write(STDOUT_FILENO, help, _strlen(help));
}


/**
 * general_help - Entry point for help information for the help builtin
 * Return: no return
 */
void general_help(void)
{
	char *help = "^-^ bash, version 1.0(1)-release\n";

	write(STDOUT_FILENO, help, _strlen(help));
	help = "These commands are defined internally.Type 'help' to see the list";
	write(STDOUT_FILENO, help, _strlen(help));
	help = "Type 'help name' to find out more about the function 'name'.\n\n ";
	write(STDOUT_FILENO, help, _strlen(help));
	help = " alias: alias [name=['string']]\n cd: cd [-L|[-P [-e]] [-@]] ";
	write(STDOUT_FILENO, help, _strlen(help));
	help = "[dir]\nexit: exit [n]\n  env: env [option] [name=value] [command ";
	write(STDOUT_FILENO, help, _strlen(help));
	help = "[args]]\n  setenv: setenv [variable] [value]\n  unsetenv: ";
	write(STDOUT_FILENO, help, _strlen(help));
	help = "unsetenv [variable]\n";
	write(STDOUT_FILENO, help, _strlen(help));
}

