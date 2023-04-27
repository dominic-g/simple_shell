#include "shell.h"

/**
 * cmp_env_name - compares env variables names
 * with the name passed.
 * @ss_alias: name of the environment variable
 * @p_name: name passed
 *
 * Return: 0 if they are not equal. Another value if they are.
 */
int cmp_env_name(const char *ss_alias, const char *p_name)
{
int i;

for (i = 0; ss_alias[i] != '='; i++)
{
if (ss_alias[i] != p_name[i])
{
return (0);
}
}

return (i + 1);
}

/**
 * _getenv - get an environment variable
 * @name: name of the environment variable
 *
 * Return: value of the environment variable if it is found.
 * Otherwise, returns NULL.
 */
char *_getenv(const char *name)
{
char *ptr_env;
int i, mov;

/* Initialize ptr_env value */
ptr_env = NULL;
mov = 0;
/* Compare all environment variables */
/* environ is declared in the header file */
for (i = 0; environ[i]; i++)
{
/* If name and env are equal */
mov = cmp_env_name(environ[i], name);
if (mov)
{
ptr_env = environ[i];
break;
}
}

return (ptr_env + mov);
}

/**
 * _env - prints the environment variables
 *
 * Return: 1 on success.
 */
int _env(void)
{

int i, j;

for (i = 0; environ[i]; i++)
{

for (j = 0; environ[i][j]; j++)
;

write(STDOUT_FILENO, environ[i], j);
write(STDOUT_FILENO, "\n", 1);
}

return (1);
}

