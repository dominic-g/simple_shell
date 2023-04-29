#include "shell.h"

/**
 * cd_shell - changes current directory
 *
 * @dss: data relevant
 * Return: 1 on success
 */
int cd_shell(custom_struct *dss)
{
	char *dir;
	int ishome, ishome2, isddash;

	dir = dss->args[1];

	if (dir != NULL)
	{
		ishome = _strcmp("$HOME", dir);
		ishome2 = _strcmp("~", dir);
		isddash = _strcmp("--", dir);
	}

	if (dir == NULL || !ishome || !ishome2 || !isddash)
	{
		home_directory(dss);
		return (1);
	}

	if (_strcmp("-", dir) == 0)
	{
		change_dir_to_previous(dss);
		return (1);
	}

	if (_strcmp(".", dir) == 0 || _strcmp("..", dir) == 0)
	{
		change_dir_dot(dss);
		return (1);
	}

	change_dir_to(dss);

	return (1);
}
/**
 * change_dir_dot - changes to the parent directory
 *
 * @data: data relevant (environ)
 *
 * Return: no return
 */
void change_dir_dot(custom_struct *data)
{
	char pwd[PATH_MAX];
	char *dir, *cp_pwd, *cp_strtok_pwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = _strdup(pwd);
	set_env("OLDPWD", cp_pwd, data);
	dir = data->args[1];
	if (_strcmp(".", dir) == 0)
	{
		set_env("PWD", cp_pwd, data);
		free(cp_pwd);
		return;
	}
	if (_strcmp("/", cp_pwd) == 0)
	{
		free(cp_pwd);
		return;
	}
	cp_strtok_pwd = cp_pwd;
	rev_string(cp_strtok_pwd);
	cp_strtok_pwd = _strtok(cp_strtok_pwd, "/");
	if (cp_strtok_pwd != NULL)
	{
		cp_strtok_pwd = _strtok(NULL, "\0");

		if (cp_strtok_pwd != NULL)
			rev_string(cp_strtok_pwd);
	}
	if (cp_strtok_pwd != NULL)
	{
		chdir(cp_strtok_pwd);
		set_env("PWD", cp_strtok_pwd, data);
	}
	else
	{
		chdir("/");
		set_env("PWD", "/", data);
	}
	data->status = 0;
	free(cp_pwd);
}

/**
 * change_dir_to - changes to a directory given
 * by the user
 *
 * @data: data relevant (directories)
 * Return: no return
 */
void change_dir_to(custom_struct *data)
{
	char pwd[PATH_MAX];
	char *dir, *cp_pwd, *cp_dir;

	getcwd(pwd, sizeof(pwd));

	dir = data->args[1];
	if (chdir(dir) == -1)
	{
		get_error(data, 2);
		return;
	}

	cp_pwd = _strdup(pwd);
	set_env("OLDPWD", cp_pwd, data);

	cp_dir = _strdup(dir);
	set_env("PWD", cp_dir, data);

	free(cp_pwd);
	free(cp_dir);

	data->status = 0;

	chdir(dir);
}

/**
 * change_dir_to_previous - changes to the previous directory
 *
 * @data: data relevant (environ)
 * Return: no return
 */
void change_dir_to_previous(custom_struct *data)
{
	char pwd[PATH_MAX];
	char *p_pwd, *p_oldpwd, *cp_pwd, *cp_oldpwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = _strdup(pwd);

	p_oldpwd = _getenv("OLDPWD", data->_environ);

	if (p_oldpwd == NULL)
		cp_oldpwd = cp_pwd;
	else
		cp_oldpwd = _strdup(p_oldpwd);

	set_env("OLDPWD", cp_pwd, data);

	if (chdir(cp_oldpwd) == -1)
		set_env("PWD", cp_pwd, data);
	else
		set_env("PWD", cp_oldpwd, data);

	p_pwd = _getenv("PWD", data->_environ);

	write(STDOUT_FILENO, p_pwd, _strlen(p_pwd));
	write(STDOUT_FILENO, "\n", 1);

	free(cp_pwd);
	if (p_oldpwd)
		free(cp_oldpwd);

	data->status = 0;

	chdir(p_pwd);
}

/**
 * home_directory - changes to home directory
 *
 * @data: data relevant (environ)
 * Return: no return
 */
void home_directory(custom_struct *data)
{
	char *p_pwd, *home;
	char pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	p_pwd = _strdup(pwd);

	home = _getenv("HOME", data->_environ);

	if (home == NULL)
	{
		set_env("OLDPWD", p_pwd, data);
		free(p_pwd);
		return;
	}

	if (chdir(home) == -1)
	{
		get_error(data, 2);
		free(p_pwd);
		return;
	}

	set_env("OLDPWD", p_pwd, data);
	set_env("PWD", home, data);
	free(p_pwd);
	data->status = 0;
}
