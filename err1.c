#include "shell.h"
/**
 * get_error_bultin - calls the error according the builtin, syntax or permission
 * @data_st: data structure that contains arguments
 * @error_val: error value
 * Return: error
 */
int get_error_builtin(custom_struct *data_st, int error_val)
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
/**
 * strcat_cd_message - function that concatenates the message for cd errors
 *
 * @ss_data: data's relevant (directory)
 * @msg: messages to print
 * @error: output messages
 * @ss_str: counter lines
 *
 * Return: error message(S)
 */
char *strcat_cd_message(custom_struct *ss_data, char *msg, char *error, char *ss_str)
{
	char *illegal_flag;

	_strcpy(error, ss_data->av[0]);
	_strcat(error, ": ");
	_strcat(error, ss_str);
	_strcat(error, ": ");
	_strcat(error, ss_data->args[0]);
	_strcat(error, msg);
	if (ss_data->args[1][0] == '-')
	{
		illegal_flag = malloc(3);
		illegal_flag[0] = '-';
		illegal_flag[1] = ss_data->args[1][1];
		illegal_flag[2] = '\0';
		_strcat(error, illegal_flag);
		free(illegal_flag);
	}
	else
	{
		_strcat(error, ss_data->args[1]);
	}

	_strcat(error, "\n");
	_strcat(error, "\0");
	return (error);
}

/**
 * error_get_cd_message - error message(s) for cd command(s) in get_cd function
 * @ss_data: data relevant (directory)
 * Return: Error message
 */
char *error_get_cd_message(custom_struct *ss_data)
{
	int length, len_id;
	char *error, *ss_str, *msg;

	ss_str = int_to_char(ss_data->counter);
	if (ss_data->args[1][0] == '-')
	{
		msg = ": Illegal option ";
		len_id = 2;
	}
	else
	{
		msg = ": can't cd to ";
		len_id = _strlen(ss_data->args[1]);
	}

	length = _strlen(ss_data->av[0]) + _strlen(ss_data->args[0]);
	length += _strlen(ss_str) + _strlen(msg) + len_id + 5;
	error = malloc(sizeof(char) * (length + 1));

	if (error == 0)
	{
		free(ss_str);
		return (NULL);
	}

	error = strcat_cd(ss_data, msg, error, ss_str);

	free(ss_str);

	return (error);
}

/**
 * error_not_found_message - generic error message(s) for command not found
 * @ss_data: data relevant (counter, arguments)
 * Return: Error message
 */
char *error_not_found_message(custom_struct *ss_data)
{
	int length;
	char *error;
	char *ss_str;

	ss_str = int_to_char(ss_data->counter);
	length = _strlen(ss_data->av[0]) + _strlen(ss_str);
	length += _strlen(ss_data->args[0]) + 16;
	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(error);
		free(ss_str);
		return (NULL);
	}
	_strcpy(error, ss_data->av[0]);
	_strcat(error, ": ");
	_strcat(error, ss_str);
	_strcat(error, ": ");
	_strcat(error, ss_data->args[0]);
	_strcat(error, ": not found\n");
	_strcat(error, "\0");
	free(ss_str);
	return (error);
}

/**
 * error_exit_shell_message - generic error message for exit in get_exit
 * @ss_data: data relevant (counter, arguments)
 *
 * Return: Error message
 */
char *error_exit_shell_message(custom_struct *ss_data)
{
	int length;
	char *error;
	char *ss_str;

	ss_str = int_to_char(ss_data->counter);
	length = _strlen(ss_data->av[0]) + _strlen(ss_str);
	length += _strlen(ss_data->args[0]) + _strlen(ss_data->args[1]) + 23;
	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(ss_str);
		return (NULL);
	}
	_strcpy(error, ss_data->av[0]);
	_strcat(error, ": ");
	_strcat(error, ss_str);
	_strcat(error, ": ");
	_strcat(error, ss_data->args[0]);
	_strcat(error, ": Illegal number: ");
	_strcat(error, ss_data->args[1]);
	_strcat(error, "\n\0");
	free(ss_str);

	return (error);
}
