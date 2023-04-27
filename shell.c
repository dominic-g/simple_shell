#include "shell.h"

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

/**
 * main - Entry point
 *
 * @ac: argument count
 * @av: argument vector
 *
 * Return: 0 on success.
 */
int main(int ac, char **av)
{
	data_shell data_st;
	(void) ac;

	signal(SIGINT, get_sigint);
	set_data(&data_st, av);
	shell_loop(&data_st);
	free_data(&data_st);
	if (data_st.status < 0)
		return (255);
	return (data_st.status);
}
