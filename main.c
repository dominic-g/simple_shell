#include "shell.h"

/**
 * free_data - frees data structure
 *
 * @data_st: data structure
 * Return: no return
 */
void free_data(custom_struct *data_st)
{
	unsigned int i;

	for (i = 0; data_st->_environ[i]; i++)
	{
		free(data_st->_environ[i]);
	}

	free(data_st->_environ);
	free(data_st->pid);
}

/**
 * set_data - Initialize data structure
 *
 * @data_st: data structure
 * @av: argument vector
 * Return: no return
 */
void set_data(custom_struct *data_st, char **av)
{
	unsigned int i;

	data_st->av = av;
	data_st->input = NULL;
	data_st->args = NULL;
	data_st->status = 0;
	data_st->counter = 1;

	for (i = 0; environ[i]; i++)
		;

	data_st->_environ = malloc(sizeof(char *) * (i + 1));

	for (i = 0; environ[i]; i++)
	{
		data_st->_environ[i] = _strdup(environ[i]);
	}

	data_st->_environ[i] = NULL;
	data_st->pid = int_to_char(getpid());
}

/**
 * _removecomments - removes comments from the string
 *
 * @input: the command string to check for comment
 * Return: string without the comments
 */

char *_removecomments(char *input)
{
	int i, term;

	term = 0;
	for (i = 0; input[i]; i++)
	{
		if (input[i] == '#')
		{
			if (i == 0)
			{
				free(input);
				return (NULL);
			}

			if (input[i - 1] == ' ' || input[i - 1] == '\t' || input[i - 1] == ';')
				term = i;
		}
	}

	if (term != 0)
	{
		input = _memallocate(input, i, term + 1);
		input[term] = '\0';
	}

	return (input);
}

/**
 * _mainrotater - The rotater loop for the program to check command
 * @data: custom structure with all arguments
 *
 * Return: void.
 */

void _mainrotater(custom_struct *data)
{
	int loop, mk_eof;
	char *input;

	loop = 1;
	while (loop == 1)
	{
		write(STDIN_FILENO, "$ ", 2);
		input = _getcommand(&mk_eof);
		if (mk_eof != -1)
		{
			input = _removecomments(input);
			if (input == NULL)
				continue;

			if (_lookforsynerror(data, input) == 1)
			{
				data->status = 2;
				free(input);
				continue;
			}
			input = rep_var(input, data);
			loop = _cutthecommands(data, input);
			data->counter += 1;
			free(input);
		}
		else
		{
			loop = 0;
			free(input);
		}
	}
}

/**
 * main - Entry point
 *
 * @argc: number of the arguments
 * @argv: command message of the argument
 *
 * Return: 0 on success.
 */
int main(int argc, char **argv)
{
	custom_struct cust_data;
	(void) argc;

	signal(SIGINT, get_sigint);
	set_data(&cust_data, argv);
	_mainrotater(&cust_data);
	free_data(&cust_data);
	if (cust_data.status < 0)
		return (255);
	return (cust_data.status);
}
