#include "shell.h"


/**
* my_getline_ - Uses static variables to keep track of
* the current position in the buffer,
* the length of the buffer, and the characters that
* have already been read from standard input
*  @_eof: - buffer size
*
* Return: The command string entered by the user.
*/
char *my_getline_(int *_eof)
{
	char *inp = NULL;
	size_t buf = 0;

	*_eof = getline(&inp, &buf, stdin);

	return (inp);
}

/**
 * free_data - frees data structure
 *
 * @data_st: data structure
 * Return: no return
 */
void free_data(data_shell *data_st)
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
void set_data(data_shell *data_st, char **av)
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
