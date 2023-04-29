#include "shell.h"

/**
 * _getcommand - Function to get the user command
 *
 * @checkend: get the command string
 * Return: the string
 */

char *_getcommand(int *checkend)
{
	char *input = NULL;
	size_t bufsize = 0;

	*checkend = getline(&input, &bufsize, stdin);

	return (input);
}


/**
 * get_sigint - Handle the (ctrl + c) call in prompt
 * @signal: Signal handler
 */
void get_sigint(int signal)
{
	(void)signal;
	write(STDOUT_FILENO, "\n$ ", 2);
}

/**
 * _inclinevrnod - adds a variable at the end
 * of a line_var list.
 * @head: head of the linked list.
 * @var_len: length of the variable.
 * @val: value of the variable.
 * @loval: length of the value.
 * Return: address of the head.
 */
line_var *_inclinevrnod(line_var **head, int var_len, char *val, int loval)
{
	line_var *currt;
	line_var *holding;

	currt = malloc(sizeof(line_var));
	if (currt == NULL)
		return (NULL);

	currt->len_var = var_len;
	currt->val = val;
	currt->len_val = loval;

	currt->next = NULL;
	holding = *head;

	if (holding == NULL)
	{
		*head = currt;
	}
	else
	{
		while (holding->next != NULL)
			holding = holding->next;
		holding->next = currt;
	}

	return (*head);
}

/**
 * _removelinevr - frees a line_var list
 * @head: head of the linked list.
 * Return: no return.
 */
void _removelinevr(line_var **head)
{
	line_var *tmp;
	line_var *prv;

	if (head != NULL)
	{
		prv = *head;
		while ((tmp = prv) != NULL)
		{
			prv = prv->next;
			free(tmp);
		}
		*head = NULL;
	}
}

