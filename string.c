#include "shell.h"
/**
 * _strspn - Returns the length of the initial segment of str1
 * consisting only of characters that appear in str2.
 * @str1: The string to be searched.
 * @str2: The string containing the characters to match.
 *
 * Return: The length of the segment that matches.
 */
size_t _strspn(const char *str1, const char *str2)
{
const char *p = str1;
size_t count = 0;

while (*p != '\0')
{
const char *q = str2;
bool found = false;

while (*q != '\0')
{
if (*p == *q)
{
found = true;
break;
}
q++;
}

if (!found)
{
return (count);
}

count++;
p++;
}

return (count);
}
/**
 * _strcspn - Returns the length of the initial segment of str
 * consisting only of characters that do not appear in search.
 * @str: The string to be searched.
 * @search: The string containing the characters to avoid.
 *
 * Return: The length of the segment that does not match.
 */
size_t _strcspn(const char *str, const char *search)
{
const char *p = str;
size_t count = 0;
while (*p != '\0')
{
const char *q = search;
while (*q != '\0')
{
if (*p == *q)
{
return (count);
}
q++;
}
p++;
count++;
}
return (count);
}
/**
 * _strtok - A function that breaks string str into a series of
 * tokens using the delimiter delim.
 * @str: The string to be tokenized.
 * @delim: The delimiter used to split the string.
 *
 * Return: A pointer to the next token.
 */
char *_strtok(char *str, const char *delim)
{
static char *last_str;  /* Pointer to the last token */
char *tok = NULL;              /* Pointer to the current token */

if (str != NULL)
{
/* Start at the beginning of the string */
last_str = str;
}
else if (last_str == NULL)
{
/* No more tokens to be found */
return (NULL);
}

/* Find the start of the next token */
tok = last_str + _strspn(last_str, delim);
if (*tok == '\0')
{
/* No more tokens to be found */
last_str = NULL;
return (NULL);
}

/* Find the end of the current token */
last_str = tok + _strcspn(tok, delim);
if (*last_str != '\0')
{
*last_str++ = '\0';
}

return (tok);
}
/**
 * _strcmp - Compares two strings and returns the difference
 * between the ASCII values of the first non-matching characters.
 * @s1: The first string to be compared.
 * @s2: The second string to be compared.
 *
 * Return: The difference between the ASCII values of the first
 * non-matching characters.
 */
int _strcmp(char *s1, char *s2)
{
int cmp = 0, i;

if (s1 == NULL || s2 == NULL)
return (1);
for (i = 0; s1[i]; i++)
{
if (s1[i] != s2[i])
{
cmp = s1[i] - s2[i];
break;
}
else
continue;
}
return (cmp);
}
/**
* _strdup - duplicates a string in memory
* @str: string to duplicate
* Return: pointer to newly allocated memory containing the duplicated string,
* or NULL if insufficient memory was available
*/
char *_strdup(const char *str)
{
char *copy;
size_t i;
size_t len = 0;
while (str[len] != '\0')
{
len++;
}

copy = (char *) malloc(sizeof(char) * (len + 1));
if (copy == NULL)
{
return (NULL);
}

for (i = 0; i < len; i++)
{
copy[i] = str[i];
}
copy[len] = '\0';

return (copy);
}

