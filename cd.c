#include "shell.h"

/**
 * home_directory - changes to home directory
 * Return: no return
 */

void home_directory(void)
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
