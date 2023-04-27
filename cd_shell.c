#include "shell.h"

/**
 * cd_shell - changes current directory
 *
 * @dss: data relevant
 * Return: 1 on success
 */
int cd_shell(data_shell *dss)
{
	char *dir;
	int ishome, ishome2, isddash;

	dir = dss->args[1];

	if (dir != NULL)
	{
		ishome = _strcmp("$HOME", dir);
		ishome2 = _strcmp("~", dir);
		isddash = _strcmp("--", dir);
	}

	if (dir == NULL || !ishome || !ishome2 || !isddash)
	{
		home_directory(dss);
		return (1);
	}

	if (_strcmp("-", dir) == 0)
	{
		change_dir_to_previous(dss);
		return (1);
	}

	if (_strcmp(".", dir) == 0 || _strcmp("..", dir) == 0)
	{
		change_dir_dot(dss);
		return (1);
	}

	change_dir_to(dss);

	return (1);
}
