#include "shell.h"

/**
 * _strcat - appends the src string to the dest string
 * @dest: pointer of the copied str
 * @src: pointer of the source
 * Return: pointer to resulting string dest
 */
char *_strcat(char *dest, const char *src)
{
	int i, length;

	length = _strlen(dest);

	for (i = 0 ; src[i] != '\0' ; i++)
		dest[length + i] = src[i];
	dest[length + i] = '\0';

	return (dest);
}
/**
 * _strspn - get the length of sbstring.
 * @s: prefix segment.
 * @acc: bytes to the function.
 * Return: bytes accepted.
 */
int _strspn(char *s, char *acc)
{
	int i, j, bol;

	for (i = 0; *(s + i) != '\0'; i++)
	{
		bol = 1;
		for (j = 0; *(acc + j) != '\0'; j++)
		{
			if (*(s + i) == *(acc + j))
			{
				bol = 0;
				break;
			}
		}
		if (bol == 1)
			break;
	}
	return (i);
}

/**
 * cmp_chars - compare chars of strings
 * @str: input string.
 * @del: delimiter.
 *
 * Return: 1 if are equals, 0 if not.
 */
int cmp_chars(char str[], const char *del)
{
	unsigned int i, j, k;

	for (i = 0, k = 0; str[i]; i++)
	{
		for (j = 0; del[j]; j++)
		{
			if (str[i] == del[j])
			{
				k++;
				break;
			}
		}
	}
	if (i == k)
		return (1);
	return (0);
}


/**
 * rev_string - reverses a string.
 * @s: string to reverse.
 * Return: void
 */
void rev_string(char *s)
{
int len, i;
len = 0;
while (s[len] != '\0')
{
len++;
}
for (i = 0; i < len / 2; i++)
{
char temp = s[i];
s[i] = s[len - i - 1];
s[len - i - 1] = temp;
}
}


/**
 * _strchr - Function to locates char in a string,
 * @str: the haystack.
 * @c: the needle char.
 * Return: pointer to found character.
 */
char *_strchr(char *str, char c)
{
	int i;

	for (i = 0; str[i] != '\0'; i++)
	{
		if (str[i] == c)
			return ((char *)(str + i));
	}
	return (NULL);
}
