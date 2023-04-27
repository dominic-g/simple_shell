#include "shell.h"

/**
 * swap_char - swaps '|' and '&' for non-printed chars
 *
 * @input: input string
 * @bool: type of swap
 * Return: swapped string
 */

char *swap_char(char *input, int bool)
{
	int i;

	if (bool == 0)
	{
		for (i = 0; input[i]; i++)
		{
			if (input[i] == '|')
			{
				if (input[i + 1] != '|')
					input[i] = 16;
				else
					i++;
			}

			if (input[i] == '&')
			{
				if (input[i + 1] != '&')
					input[i] = 12;
				else
					i++;
			}
		}
	}
	else
	{
		for (i = 0; input[i]; i++)
		{
			input[i] = (input[i] == 16 ? '|' : input[i]);
			input[i] = (input[i] == 12 ? '&' : input[i]);
		}
	}
	return (input);
}

/**
 * add_nodes - add separators and command lines in the lists
 *
 * @hd_sep: head of separator list
 * @hd_line: head of command lines list
 * @input_str: input string
 * Return: no return
 */
void add_nodes(sep_list **hd_sep, line_list **hd_line, char *input_str)
{
	int i;
	char *line;

	input_str = swap_char(input_str, 0);

	for (i = 0; input_str[i]; i++)
	{
		if (input_str[i] == ';')
			add_sep_node_end(hd_sep, input_str[i]);

		if (input_str[i] == '|' || input_str[i] == '&')
		{
			add_sep_node_end(hd_sep, input_str[i]);
			i++;
		}
	}

	line = _strtok(input_str, ";|&");
	do {
		line = swap_char(line, 1);
		add_line_node_end(hd_line, line);
		line = _strtok(NULL, ";|&");
	} while (line != NULL);

}

/**
 * go_next - go to the next command line stored
 *
 * @list_s: separator list
 * @list_l: command line list
 * @datash: data structure
 * Return: no return
 */
void go_next(sep_list **list_s, line_list **list_l, data_shell *datash)
{
	int loop_sep;
	sep_list *ls_s;
	line_list *ls_l;

	loop_sep = 1;
	ls_s = *list_s;
	ls_l = *list_l;

	while (ls_s != NULL && loop_sep)
	{
		if (datash->status == 0)
		{
			if (ls_s->separator == '&' || ls_s->separator == ';')
				loop_sep = 0;
			if (ls_s->separator == '|')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		else
		{
			if (ls_s->separator == '|' || ls_s->separator == ';')
				loop_sep = 0;
			if (ls_s->separator == '&')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		if (ls_s != NULL && !loop_sep)
			ls_s = ls_s->next;
	}

	*list_s = ls_s;
	*list_l = ls_l;
}

/**
 * split_commands - splits command lines according to
 * the separators ;, | and &, and executes them
 *
 * @data_st: data structure
 * @input: input string
 * Return: 0 to exit, 1 to continue
 */
int split_commands(data_shell *data_st, char *input)
{

	sep_list *hd_sep, *list_s;
	line_list *hd_line, *list_l;
	int loop;

	hd_sep = NULL;
	hd_line = NULL;

	add_nodes(&hd_sep, &hd_line, input);

	list_s = hd_sep;
	list_l = hd_line;

	while (list_l != NULL)
	{
		data_st->input = list_l->line;
		data_st->args = split_line(data_st->input);
		loop = exec_line(data_st);
		free(data_st->args);

		if (loop == 0)
			break;

		go_next(&list_s, &list_l, data_st);

		if (list_l != NULL)
			list_l = list_l->next;
	}

	free_sep_list(&hd_sep);
	free_line_list(&hd_line);

	if (loop == 0)
		return (0);
	return (1);
}

/**
 * split_line - tokenizes the input string
 *
 * @input: input string.
 * Return: string splitted.
 */
char **split_line(char *input)
{
	size_t token_size;
	size_t i;
	char **tokens;
	char *token;

	token_size = TOK_BUFSIZE;
	tokens = malloc(sizeof(char *) * (token_size));
	if (tokens == NULL)
	{
		write(STDERR_FILENO, ": allocation error\n", 18);
		exit(EXIT_FAILURE);
	}

	token = _strtok(input, TOK_DELIM);
	tokens[0] = token;

	for (i = 1; token != NULL; i++)
	{
		if (i == token_size)
		{
			token_size += TOK_BUFSIZE;
			tokens = _reallocdp(tokens, i, sizeof(char *) * token_size);
			if (tokens == NULL)
			{
				write(STDERR_FILENO, ": allocation error\n", 18);
				exit(EXIT_FAILURE);
			}
		}
		token = _strtok(NULL, TOK_DELIM);
		tokens[i] = token;
	}

	return (tokens);
}
