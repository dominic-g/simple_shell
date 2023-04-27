#include "shell.h"

/**
 * add_sep_node_end - adds a separator found at the end
 * of a sep_list.
 * @hd_linked: head of the linked list.
 * @sep: separator found (; | &).
 * Return: address of the head.
 */
sep_list *add_sep_node_end(sep_list **hd_linked, char sep)
{
	sep_list *new, *temp;

	new = malloc(sizeof(sep_list));
	if (new == NULL)
		return (NULL);

	new->separator = sep;
	new->next = NULL;
	temp = *hd_linked;

	if (temp == NULL)
	{
		*hd_linked = new;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}

	return (*hd_linked);
}

/**
 * free_sep_list - frees a sep_list
 * @hd_linked: head of the linked list.
 * Return: no return.
 */
void free_sep_list(sep_list **hd_linked)
{
	sep_list *temp;
	sep_list *curr;

	if (hd_linked != NULL)
	{
		curr = *hd_linked;
		while ((temp = curr) != NULL)
		{
			curr = curr->next;
			free(temp);
		}
		*hd_linked = NULL;
	}
}

/**
 * add_line_node_end - adds a command line at the end
 * of a line_list.
 * @hd_linked: head of the linked list.
 * @line: command line.
 * Return: address of the hd_linked.
 */
line_list *add_line_node_end(line_list **hd_linked, char *line)
{
	line_list *new, *temp;

	new = malloc(sizeof(line_list));
	if (new == NULL)
		return (NULL);

	new->line = line;
	new->next = NULL;
	temp = *hd_linked;

	if (temp == NULL)
	{
		*hd_linked = new;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}

	return (*hd_linked);
}

/**
 * free_line_list - frees a line_list
 * @hd_linked: head of the linked list.
 * Return: no return.
 */
void free_line_list(line_list **hd_linked)
{
	line_list *temp;
	line_list *curr;

	if (hd_linked != NULL)
	{
		curr = *hd_linked;
		while ((temp = curr) != NULL)
		{
			curr = curr->next;
			free(temp);
		}
		*hd_linked = NULL;
	}
}
