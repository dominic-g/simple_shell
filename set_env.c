#include "shell.h"

/**
 * set_env - sets an environment variable
 *
 * @alias: name of the environment variable
 * @a_value: value of the environment variable
 * @d_st: data structure (environ)
 * Return: no return
 */

void set_env(char *alias, char *a_value, custom_struct *d_st)
{
	int i;
	char *var_env, *alias_env;

	for (i = 0; d_st->_environ[i]; i++)
	{
		var_env = _strdup(d_st->_environ[i]);
		alias_env = _strtok(var_env, "=");
		if (_strcmp(alias_env, alias) == 0)
		{
			free(d_st->_environ[i]);
			d_st->_environ[i] = copy_info(alias_env, a_value);
			free(var_env);
			return;
		}
		free(var_env);
	}

	d_st->_environ = _memallocatedouble(d_st->_environ, i, sizeof(char *) * (i + 2));
	d_st->_environ[i] = copy_info(alias, a_value);
	d_st->_environ[i + 1] = NULL;
}

/**
 * _setenv - compares env variables names
 * with the name passed.
 * @data_st: data relevant (env name and env value)
 *
 * Return: 1 on success.
 */
int _setenv(custom_struct *data_st)
{

	if (data_st->args[1] == NULL || data_st->args[2] == NULL)
	{
		get_error(data_st, -1);
		return (1);
	}

	set_env(data_st->args[1], data_st->args[2], data_st);

	return (1);
}

/**
 * _unsetenv - deletes a environment variable
 *
 * @data_st: data relevant (env name)
 *
 * Return: 1 on success.
 */
int _unsetenv(custom_struct *data_st)
{
	char **realloc_env;
	char *var_env, *name_env;
	int i, j, k;

	if (data_st->args[1] == NULL)
	{
		get_error(data_st, -1);
		return (1);
	}
	k = -1;
	for (i = 0; data_st->_environ[i]; i++)
	{
		var_env = _strdup(data_st->_environ[i]);
		name_env = _strtok(var_env, "=");
		if (_strcmp(name_env, data_st->args[1]) == 0)
		{
			k = i;
		}
		free(var_env);
	}
	if (k == -1)
	{
		get_error(data_st, -1);
		return (1);
	}
	realloc_env = malloc(sizeof(char *) * (i));
	for (i = j = 0; data_st->_environ[i]; i++)
	{
		if (i != k)
		{
			realloc_env[j] = data_st->_environ[i];
			j++;
		}
	}
	realloc_env[j] = NULL;
	free(data_st->_environ[k]);
	free(data_st->_environ);
	data_st->_environ = realloc_env;
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

