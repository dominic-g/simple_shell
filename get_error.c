#include "shell.h"

/**
 * get_error - calls the error according the builtin, syntax or permission
 * @data_st: data structure that contains arguments
 * @error_val: error value
 * Return: error
 */
int get_error(data_shell *data_st, int error_val)
{
	char *error;

	switch (error_val)
	{
	case -1:
		error = error_env(data_st);
		break;
	case 126:
		error = error_path_126(data_st);
		break;
	case 127:
		error = error_not_found(data_st);
		break;
	case 2:
		if (_strcmp("exit", data_st->args[0]) == 0)
			error = error_exit_shell(data_st);
		else if (_strcmp("cd", data_st->args[0]) == 0)
			error = error_get_cd(data_st);
		break;
	}

	if (error)
	{
		write(STDERR_FILENO, error, _strlen(error));
		free(error);
	}

	data_st->status = error_val;
	return (error_val);
}
