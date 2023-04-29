#include "shell.h"

/**
 * _freeseparatorls - frees a custom_sep_ls
 * @hed_list: head of the linked list.
 * Return: no return.
 */
void _freeseparatorls(custom_sep_ls **hed_list)
{
	custom_sep_ls *tmp;
	custom_sep_ls *curr;

	if (hed_list != NULL)
	{
		curr = *hed_list;
		while ((tmp = curr) != NULL)
		{
			curr = curr->next;
			free(tmp);
		}
		*hed_list = NULL;
	}
}


/**
 * _asneend - adds a separator found at the end
 * of a custom_sep_ls.
 * @hed_list: head of the linked list.
 * @separator: separator found (; | &).
 * Return: address of the head.
 */
custom_sep_ls *_asneend(custom_sep_ls **hed_list, char separator)
{
custom_sep_ls *new_node;
custom_sep_ls *tmp;

new_node = malloc(sizeof(custom_sep_ls));
if (new_node == NULL)
return (NULL);

new_node->separator = separator;
new_node->next = NULL;
tmp = *hed_list;

if (tmp == NULL)
{
*hed_list = new_node;
}
else
{
while (tmp->next != NULL)
tmp = tmp->next;
tmp->next = new_node;
}

return (*hed_list);
}

/**
 * _liberatelinelist - frees a custom_line_ls
 * @hed_list: head of the linked list.
 * Return: no return.
 */
void _liberatelinelist(custom_line_ls **hed_list)
{
	custom_line_ls *tmp;
	custom_line_ls *curr;

	if (hed_list != NULL)
	{
		curr = *hed_list;
		while ((tmp = curr) != NULL)
		{
			curr = curr->next;
			free(tmp);
		}
		*hed_list = NULL;
	}
}


/**
 * _addendnode - adds a command line at the end
 * of a custom_line_ls.
 * @hed_list: head of the linked list.
 * @line: command line.
 * Return: address of the hed_list.
 */
custom_line_ls *_addendnode(custom_line_ls **hed_list, char *line)
{
	custom_line_ls *new;
	custom_line_ls *tmp;

	new = malloc(sizeof(custom_line_ls));
	if (new == NULL)
		return (NULL);

	new->line = line;
	new->next = NULL;
	tmp = *hed_list;

	if (tmp == NULL)
	{
		*hed_list = new;
	}
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}

	return (*hed_list);
}
