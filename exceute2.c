#include "shell.h"

/**
 * exec_line - finds builtins and commands
 *
 * @data: data relevant (args)
 * Return: 1 on success.
 */
int exec_line(custom_struct *data)
{
	int (*builtin)(custom_struct *data);

	if (data->args[0] == NULL)
		return (1);

	builtin = get_builtin(data->args[0]);

	if (builtin != NULL)
		return (builtin(data));

	return (cmd_exec(data));
}

/**
 * get_builtin - builtin that parse the command in the arg
 * @ss_cmd: command
 * Return: function pointer of the builtin command
 */
int (*get_builtin(char *ss_cmd))(custom_struct *)
{
	custom_inbuilt builtin[] = {
		{ "env", _env },
		{ "exit", exit_shell },
		{ "setenv", _setenv },
		{ "unsetenv", _unsetenv },
		{ "cd", cd_shell },
		{ "help", get_help },
		{ NULL, NULL }
	};
	int i;

	for (i = 0; builtin[i].name; i++)
	{
		if (_strcmp(builtin[i].name, ss_cmd) == 0)
			break;
	}

	return (builtin[i].f);
}

/**
 * exit_shell - exits the shell
 *
 * @datash: data relevant (status and args)
 * Return: 0 on success.
 */
int exit_shell(custom_struct *datash)
{
	unsigned int ustatus;
	int is_digit;
	int str_len;
	int big_number;

	if (datash->args[1] != NULL)
	{
		ustatus = char_to_int(datash->args[1]);
		is_digit = _isdigit(datash->args[1]);
		str_len = _strlen(datash->args[1]);
		big_number = ustatus > (unsigned int)INT_MAX;
		if (!is_digit || str_len > 10 || big_number)
		{
			get_error(datash, 2);
			datash->status = 2;
			return (1);
		}
		datash->status = (ustatus % 256);
	}
	return (0);
}


/**
 * _readline - Get the use input
 * @line_pointer: store of the string
 * @n: line pointer size
 * @stream: method to get from
 * Return: bytes of type ssize_t struct
 */

ssize_t _readline(char **line_pointer, size_t *n, FILE *stream)
{
	int i;
	static ssize_t input;
	ssize_t retval;
	char *buffer;
	char t = 'z';

	if (input == 0)
		fflush(stream);
	else
		return (-1);
	input = 0;

	buffer = malloc(sizeof(char) * 1024);
	if (buffer == 0)
		return (-1);
	while (t != '\n')
	{
		i = read(STDIN_FILENO, &t, 1);
		if (i == -1 || (i == 0 && input == 0))
		{
			free(buffer);
			return (-1);
		}
		if (i == 0 && input != 0)
		{
			input++;
			break;
		}
		if (input >= 1024)
			buffer = _memallocate(buffer, input, input + 1);
		buffer[input] = t;
		input++;
	}
	buffer[input] = '\0';
	_storecmd(line_pointer, n, buffer, input);
	retval = input;
	if (i != 0)
		input = 0;
	return (retval);
}




/**
 * _storecmd - keep the command to the lind var
 * @line_pointer: the buffer size to store
 * @n: the lentgh of the command
 * @buffer: the stirng commnd to store
 * @j: length of cmd
 */

void _storecmd(char **line_pointer, size_t *n, char *buffer, size_t j)
{

	if (*line_pointer == NULL)
	{
		if  (j > 1024)
			*n = j;

		else
			*n = 1024;
		*line_pointer = buffer;
	}
	else if (*n < j)
	{
		if (j > 1024)
			*n = j;
		else
			*n = 1024;
		*line_pointer = buffer;
	}
	else
	{
		_strcpy(*line_pointer, buffer);
		free(buffer);
	}
}

