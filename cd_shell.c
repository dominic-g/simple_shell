#include "shell.h"

/**
 * handle_cd - changes current directory
 * @args: this is just that argument
 *
 * Return: 1 on success
 */
int handle_cd(char *args)
{
	char *dir;
	int ishome, ishome2, isddash;

	dir = args;

	if (dir != NULL)
	{
		ishome = _strcmp("$HOME", dir);
		ishome2 = _strcmp("~", dir);
		isddash = _strcmp("--", dir);
	}

	if (dir == NULL || !ishome || !ishome2 || !isddash)
	{
		home_directory();
		return (1);
	}

	if (_strcmp("-", dir) == 0)
	{
		change_dir_to_previous();
		return (1);
	}

	if (_strcmp(".", dir) == 0 || _strcmp("..", dir) == 0)
	{
	change_dir_dot(dir);
	return (1);
	}
	change_dir_to(dir);

	return (1);
}
