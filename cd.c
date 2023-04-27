#include "shell.h"



/**
 * change_dir_to_previous - changes to the previous directory
 *
 * @data: data relevant (environ)
 * Return: no return
 */
/*void change_dir_to_previous(char *args)
{
	char pwd[PATH_MAX];
	char *p_pwd, *p_oldpwd, *cp_pwd, *cp_oldpwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = _strdup(pwd);

	p_oldpwd = _getenv("OLDPWD");

	if (p_oldpwd == NULL)
		cp_oldpwd = cp_pwd;
	else
		cp_oldpwd = _strdup(p_oldpwd);

	set_env("OLDPWD", cp_pwd);

	if (chdir(cp_oldpwd) == -1)
		set_env("PWD", cp_pwd);
	else
		set_env("PWD", cp_oldpwd);

	p_pwd = _getenv("PWD");

	write(STDOUT_FILENO, p_pwd, _strlen(p_pwd));
	write(STDOUT_FILENO, "\n", 1);

	free(cp_pwd);
	if (p_oldpwd)
		free(cp_oldpwd);

	dir = args[1];

	chdir(p_pwd);
}*/

/**
 * home_directory - changes to home directory
 *
 * @data: data relevant (environ)
 * Return: no return
 */
void home_directory()
{
	char *p_pwd, *home;
	char pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	p_pwd = _strdup(pwd);

	home = _getenv("HOME");
	printf("%s\n", home);
	if (home == NULL)
	{
		set_env("OLDPWD", p_pwd);
		free(p_pwd);
		return;
	}

	if (chdir(home) == -1)
	{
		/*get_error(data, 2);*/
		free(p_pwd);
		return;
	}


	printf("%s\n", p_pwd);
	set_env("OLDPWD", p_pwd);
	set_env("PWD", home);
	
	printf("%s\n", home);
	free(p_pwd);
	/*data->status = 0;*/
}
