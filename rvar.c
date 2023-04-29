#include "shell.h"

/**
 * _promptenv - confirm if in evn
 *
 * @h: linked list head
 * @in: name to check
 * @data: custom struct with environ
 * Return: void
 */

void _promptenv(line_var **h, char *in, custom_struct *data)
{
	int row, chr, j, lval;
	char **_envr;

	_envr = data->_environ;
	for (row = 0; _envr[row]; row++)
	{
		for (j = 1, chr = 0; _envr[row][chr]; chr++)
		{
			if (_envr[row][chr] == '=')
			{
				lval = _strlen(_envr[row] + chr + 1);
				_inclinevrnod(h, j, _envr[row] + chr + 1, lval);
				return;
			}

			if (in[j] == _envr[row][chr])
				j++;
			else
				break;
		}
	}

	for (j = 0; in[j]; j++)
	{
		if (in[j] == ' ' || in[j] == '\t' || in[j] == ';' || in[j] == '\n')
			break;
	}

	_inclinevrnod(h, j, NULL, 0);
}

/**
 * _promptdouble - confirm if given command has single or double dollr
 *
 * @h: linked list head
 * @in: string to check
 * @st: the program status
 * @data: custom data struct
 * Return: void
 */
int _promptdouble(line_var **h, char *in, char *st, custom_struct *data)
{
	int i, lst, lpd;

	lst = _strlen(st);
	lpd = _strlen(data->pid);

	for (i = 0; in[i]; i++)
	{
		if (in[i] == '$')
		{
			if (in[i + 1] == '?')
				_inclinevrnod(h, 2, st, lst), i++;
			else if (in[i + 1] == '$')
				_inclinevrnod(h, 2, data->pid, lpd), i++;
			else if (in[i + 1] == '\n')
				_inclinevrnod(h, 0, NULL, 0);
			else if (in[i + 1] == '\0')
				_inclinevrnod(h, 0, NULL, 0);
			else if (in[i + 1] == ' ')
				_inclinevrnod(h, 0, NULL, 0);
			else if (in[i + 1] == '\t')
				_inclinevrnod(h, 0, NULL, 0);
			else if (in[i + 1] == ';')
				_inclinevrnod(h, 0, NULL, 0);
			else
				_promptenv(h, in + i, data);
		}
	}

	return (i);
}

/**
 * replaced_input - replaces string into variables
 *
 * @head: head of the linked list
 * @input: input string
 * @new_input: new input string (replaced)
 * @mk_len: new length
 * Return: replaced string
 */
char *replaced_input(line_var **head, char *input, char *new_input, int mk_len)
{
	line_var *indx;
	int i, j, k;

	indx = *head;
	for (j = i = 0; i < mk_len; i++)
	{
		if (input[j] == '$')
		{
			if (!(indx->len_var) && !(indx->len_val))
			{
				new_input[i] = input[j];
				j++;
			}
			else if (indx->len_var && !(indx->len_val))
			{
				for (k = 0; k < indx->len_var; k++)
					j++;
				i--;
			}
			else
			{
				for (k = 0; k < indx->len_val; k++)
				{
					new_input[i] = indx->val[k];
					i++;
				}
				j += (indx->len_var);
				i--;
			}
			indx = indx->next;
		}
		else
		{
			new_input[i] = input[j];
			j++;
		}
	}

	return (new_input);
}

/**
 * rep_var - calls functions to replace string into vars
 *
 * @input: input string
 * @data_st: data structure
 * Return: replaced string
 */
char *rep_var(char *input, custom_struct *data_st)
{
	line_var *head, *indx;
	char *status, *new_input;
	int ss_len, mk_len;

	status = int_to_char(data_st->status);
	head = NULL;

	ss_len = _promptdouble(&head, input, status, data_st);

	if (head == NULL)
	{
		free(status);
		return (input);
	}

	indx = head;
	mk_len = 0;

	while (indx != NULL)
	{
		mk_len += (indx->len_val - indx->len_var);
		indx = indx->next;
	}

	mk_len += ss_len;

	new_input = malloc(sizeof(char) * (mk_len + 1));
	new_input[mk_len] = '\0';

	new_input = replaced_input(&head, input, new_input, mk_len);

	free(input);
	free(status);
	_removelinevr(&head);

	return (new_input);
}
