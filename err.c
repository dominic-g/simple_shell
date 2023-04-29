#include "shell.h"

/**
 * error_env_message - error message for env in get_env.
 * @ss_data: data relevant (counter, arguments)
 * Return: error message.
 */
char *error_env_message(custom_struct *ss_data)
{
	int length;
	char *error;
	char *mk_str;
	char *msg;

	mk_str = int_to_char(ss_data->counter);
	msg = ": Unable to add/remove from environment\n";
	length = _strlen(ss_data->av[0]) + _strlen(mk_str);
	length += _strlen(ss_data->args[0]) + _strlen(msg) + 4;
	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(error);
		free(mk_str);
		return (NULL);
	}

	_strcpy(error, ss_data->av[0]);
	_strcat(error, ": ");
	_strcat(error, mk_str);
	_strcat(error, ": ");
	_strcat(error, ss_data->args[0]);
	_strcat(error, msg);
	_strcat(error, "\0");
	free(mk_str);

	return (error);
}
/**
 * error_path_126_message - error message for
 * path and failure denied permission.
 * @ss_data: data relevant (counter, arguments).
 *
 * Return: The error string.
 */
char *error_path_126_message(custom_struct *ss_data)
{
	int length;
	char *mk_str;
	char *error;

	mk_str = int_to_char(ss_data->counter);
	length = _strlen(ss_data->av[0]) + _strlen(mk_str);
	length += _strlen(ss_data->args[0]) + 24;
	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(error);
		free(mk_str);
		return (NULL);
	}
	_strcpy(error, ss_data->av[0]);
	_strcat(error, ": ");
	_strcat(error, mk_str);
	_strcat(error, ": ");
	_strcat(error, ss_data->args[0]);
	_strcat(error, ": Permission denied\n");
	_strcat(error, "\0");
	free(mk_str);
	return (error);
}
