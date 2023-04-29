#include "shell.h"

/**
 * *_strcpy - copies the string with \0 to the buffer to dest
 * @dest: pointer of copied str
 * @src: pointer the source
 * Return: the pointer destination.
 */
char *_strcpy(char *dest, char *src)
{
int i;

i = 0;
while (*(src + i) != '\0')
{
*(dest + i) = *(src + i);
i++;
}
*(dest + i) = '\0';
return (dest);
}

/**
 * _isdigit - checks if the given string is number
 *
 * @s: provided string
 * Return: true or false.
 */
int _isdigit(const char *s)
{
unsigned int i;

i = 0;
while (s[i] != '\0')
{
if (!(s[i] >= '0' && s[i] <= '9'))
{
return (0);
}
i++;
}
return (1);
}
/**
 * _strdup - returns a pointer to a newly allocated space in memory.
 * @str: String to copy
 * Return: returns a pointer to a newly allocated space in memory
 */
char *_strdup(const char *str)
{
int i, len;
char *new_str;

if (str == NULL)
return (NULL);
len = _strlen(str);
new_str = malloc(sizeof(char) * (len + 1));
if (new_str == NULL)
return (NULL);
for (i = 0; i < len; i++)
new_str[i] = str[i];
new_str[len] = '\0';
return (new_str);
}
/**
 * _strcmp - Function to check and compare strings.
 * @s1: type pointer to string 1
 * @s2: type pointer to string 2
 * Return: difference in value of first char that's different
 */
int _strcmp(char *s1, char *s2)
{
int i, dif;

i = 0;
while (s1[i] != '\0' || s2[i] != '\0')
{
if (s1[i] != s2[i])
{
dif = s1[i] - s2[i];
return (dif);
}
i++;
}
if (s1[i] == s2[i] && s1[i] == '\0')
dif = 0;
return (dif);
}
/**
 * _strlen - Returns the lenght of a string.
 * @s: pointer to the string
 * Return: length or 0
 */
int _strlen(const char *s)
{
int len;

for (len = 0; s[len] != 0; len++)
{
}
return (len);
}

