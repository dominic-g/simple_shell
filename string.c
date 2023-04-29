#include "shell.h"

/**
 * _strtok - splits a string by some delimiter.
 * @str: input string.
 * @delim: delimiter.
 *
 * Return: string splited.
 */
char *_strtok(char str[], const char *delim)
{
static char *splitted, *str_end;
char *str_start;
unsigned int i, bool;

if (str != NULL)
{
if (cmp_chars(str, delim))
return (NULL);
splitted = str;
i = _strlen(str);
str_end = &str[i];
}
str_start = splitted;
if (str_start == str_end)
return (NULL);

for (bool = 0; *splitted; splitted++)
{
if (splitted != str_start)
if (*splitted && *(splitted - 1) == '\0')
break;
for (i = 0; delim[i]; i++)
{
if (*splitted == delim[i])
{
*splitted = '\0';
if (splitted == str_start)
str_start++;
break;
}
}
if (bool == 0 && *splitted)
bool = 1;
}
if (bool == 0)
return (NULL);
return (str_start);
}
