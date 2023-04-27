#include "shell.h"
#include <string.h>

/**
 * set_env - sets an environment variable
 *
 * @alias: name of the environment variable
 * @a_value: value of the environment variable
 *
 * Return: no return
 */
void set_env(char *alias, char *a_value)
{
int result;
char *env_var = malloc(strlen(alias) + strlen(a_value) + 2);
sprintf(env_var, "%s=%s", alias, a_value);
result = putenv(env_var);
if (result != 0)
printf("Error setting environment variable\n");
}


/**
 * _setenv - compares env variables names
 * with the name passed.
 * @args: arguments array (env name and env value)
 *
 * Return: 1 on success.
 */
int _setenv(char **args)
{
if (args[1] == NULL || args[2] == NULL)
{
return (1);
}

set_env(args[1], args[2]);

return (1);
}

/**
 * _unsetenv - deletes an environment variable
 *
 * @args: arguments array (env name)
 *
 * Return: 1 on success.
 */
int _unsetenv(char **args)
{
char **realloc_env;
char *var_env, *name_env;
int i, j, k;

if (args[1] == NULL)
{
return (1);
}

k = -1;
for (i = 0; environ[i]; i++)
{
var_env = _strdup(environ[i]);
name_env = _strtok(var_env, "=");
if (_strcmp(name_env, args[1]) == 0)
{
k = i;
}
free(var_env);
}
if (k == -1)
{
return (1);
}

realloc_env = malloc(sizeof(char *) * (i));
for (i = j = 0; environ[i]; i++)
{
if (i != k)
{
realloc_env[j] = environ[i];
j++;
}
}
realloc_env[j] = NULL;
free(environ[k]);
free(environ);
environ = realloc_env;

return (1);
}

/**
 * copy_info - copies info to create
 * a new env or alias
 * @alias: name of environment variable (env or alias)
 * @a_value: value (env or alias)
 *
 * Return: new env or alias.
 */
char *copy_info(char *alias, char *a_value)
{
char *new;
int len_alias, len_a_value, len;

len_alias = _strlen(alias);
len_a_value = _strlen(a_value);
len = len_alias + len_a_value + 2;
new = malloc(sizeof(char) * (len));
_strcpy(new, alias);
_strcat(new, "=");
_strcat(new, a_value);
_strcat(new, "\0");

return (new);
}
