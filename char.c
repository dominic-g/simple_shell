#include "shell.h"

/**
 * _interchangechar - interchange character for non prited
 *
 * @input: string to check
 * @bool: tpye of the
 * Return: string with interchanged
 */

char *_interchangechar(char *input, int bool)
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
 * _addseparator - adding the sep to the list
 *
 * @hd_sep: head of list in separators
 * @hd_line: head of list in command
 * @input_str: string to check
 * Return: void
 */
void _addseparator(custom_sep_ls **hd_sep,
custom_line_ls **hd_line, char *input_str)
{
	int i;
	char *line;

	input_str = _interchangechar(input_str, 0);

	for (i = 0; input_str[i]; i++)
	{
		if (input_str[i] == ';')
			_asneend(hd_sep, input_str[i]);

		if (input_str[i] == '|' || input_str[i] == '&')
		{
			_asneend(hd_sep, input_str[i]);
			i++;
		}
	}

	line = _strtok(input_str, ";|&");
	do {
		line = _interchangechar(line, 1);
		_addendnode(hd_line, line);
		line = _strtok(NULL, ";|&");
	} while (line != NULL);

}

/**
 * _movetonextline - move to the next line list
 *
 * @list_s: list of custom
 * @list_l: line cmd list custom
 * @datash: the struct data
 * Return: void
 */
void _movetonextline(custom_sep_ls **list_s,
custom_line_ls **list_l, custom_struct *datash)
{
	int loop_sep;
	custom_sep_ls *ls_s;
	custom_line_ls *ls_l;

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
 * _cutthecommands - cut the commnds using the separators and executing them
 *
 * @data_st: custom struct
 * @input: command string
 * Return: true if shell to continue false if failed
 */
int _cutthecommands(custom_struct *data_st, char *input)
{

	custom_sep_ls *hd_sep, *list_s;
	custom_line_ls *hd_line, *list_l;
	int loop;

	hd_sep = NULL;
	hd_line = NULL;

	_addseparator(&hd_sep, &hd_line, input);

	list_s = hd_sep;
	list_l = hd_line;

	while (list_l != NULL)
	{
		data_st->input = list_l->line;
		data_st->args = _tokenizeline(data_st->input);
		loop = exec_line(data_st);
		free(data_st->args);

		if (loop == 0)
			break;

		_movetonextline(&list_s, &list_l, data_st);

		if (list_l != NULL)
			list_l = list_l->next;
	}

	_freeseparatorls(&hd_sep);
	_liberatelinelist(&hd_line);

	if (loop == 0)
		return (0);
	return (1);
}

/**
 * _tokenizeline - split the string command given
 *
 * @input: command string to tokenize
 * Return: the string parts
 */
char **_tokenizeline(char *input)
{
	size_t token_size;
	size_t i;
	char **tokens;
	char *token;

	token_size = 128;
	tokens = malloc(sizeof(char *) * (token_size));
	if (tokens == NULL)
	{
		write(STDERR_FILENO, ": allocation error\n", 18);
		exit(EXIT_FAILURE);
	}

	token = _strtok(input, " \t\r\n\a");
	tokens[0] = token;

	for (i = 1; token != NULL; i++)
	{
		if (i == token_size)
		{
			token_size += 128;
			tokens = _memallocatedouble(tokens, i, sizeof(char *) * token_size);
			if (tokens == NULL)
			{
				write(STDERR_FILENO, ": allocation error\n", 18);
				exit(EXIT_FAILURE);
			}
		}
		token = _strtok(NULL, " \t\r\n\a");
		tokens[i] = token;
	}

	return (tokens);
}
