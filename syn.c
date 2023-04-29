#include "shell.h"

/**
 * _dup_char - duplications character in a string
 *
 * @input: string to check
 * @j: start index
 * Return: duplicates
 */
int _dup_char(char *input, int j)
{
	if (*(input - 1) == *input)
		return (_dup_char(input - 1, j + 1));

	return (j);
}

/**
 * _find_syntax_error - looking for syntax error
 *
 * @input: string to check error
 * @i: index
 * @last: end character to end
 * Return: 0 if no error and index if error
 */
int _find_syntax_error(char *input, int i, char last)
{
	int count;

	count = 0;
	if (*input == '\0')
		return (0);

	if (*input == ' ' || *input == '\t')
		return (_find_syntax_error(input + 1, i + 1, last));

	if (*input == ';')
		if (last == '|' || last == '&' || last == ';')
			return (i);

	if (*input == '|')
	{
		if (last == ';' || last == '&')
			return (i);

		if (last == '|')
		{
			count = _dup_char(input, 0);
			if (count == 0 || count > 1)
				return (i);
		}
	}

	if (*input == '&')
	{
		if (last == ';' || last == '|')
			return (i);

		if (last == '&')
		{
			count = _dup_char(input, 0);
			if (count == 0 || count > 1)
				return (i);
		}
	}

	return (_find_syntax_error(input + 1, i + 1, *input));
}

/**
 * _indexchar - get the character index of first in string
 *
 * @input: the string to check
 * @i: where to start
 * Return: index of char.
 */
int _indexchar(char *input, int *i)
{
	*i = 0;
    while (input[*i])
    {
        if (input[*i] == ' ' || input[*i] == '\t')
        {
            *i += 1;
            continue;
        }

        if (input[*i] == ';' || input[*i] == '|' || input[*i] == '&')
            return (-1);

        break;
    }

    return (0);
}

/**
 * syntax_error - prints when a syntax error is found
 *
 * @datash: custom structure
 * @input: string to print error
 * @i: the position of error
 * @bool: message error checker
 * Return: void prints
 */
void syntax_error(custom_struct *datash, char *input, int i, int bool)
{
	char *msg, *msg2, *msg3, *error, *counter;
	int length;

	if (input[i] == ';')
	{
		if (bool == 0)
			msg = (input[i + 1] == ';' ? ";;" : ";");
		else
			msg = (input[i - 1] == ';' ? ";;" : ";");
	}

	if (input[i] == '|')
		msg = (input[i + 1] == '|' ? "||" : "|");

	if (input[i] == '&')
		msg = (input[i + 1] == '&' ? "&&" : "&");

	msg2 = ": Syntax error: \"";
	msg3 = "\" unexpected\n";
	counter = int_to_char(datash->counter);
	length = _strlen(datash->av[0]) + _strlen(counter);
	length += _strlen(msg) + _strlen(msg2) + _strlen(msg3) + 2;

	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(counter);
		return;
	}
	_strcpy(error, datash->av[0]);
	_strcat(error, ": ");
	_strcat(error, counter);
	_strcat(error, msg2);
	_strcat(error, msg);
	_strcat(error, msg3);
	_strcat(error, "\0");

	write(STDERR_FILENO, error, length);
	free(error);
	free(counter);
}

/**
 * _lookforsynerror - checking the command if there is error
 *
 * @datash: custom structure
 * @input: command string to check error
 * Return: boolean true or flse
 */
int _lookforsynerror(custom_struct *datash, char *input)
{
	int begin = 0;
	int f_char = 0;
	int i = 0;

	f_char = _indexchar(input, &begin);
	if (f_char == -1)
	{
		syntax_error(datash, input, begin, 0);
		return (1);
	}

	i = _find_syntax_error(input + begin, 0, *(input + begin));
	if (i != 0)
	{
		syntax_error(datash, input, begin + i, 1);
		return (1);
	}

	return (0);
}
