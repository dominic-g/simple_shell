# simple_shell
Alx C Project

preserve for cd.c lines 12 - 38 lines 
```
/**
 * change_dir_to_previous - changes to the previous directory
 *
 * @data: data relevant (environ)
 * Return: no return
 */

```
```
/**
 * void change_dir_to_previous(char *args)
 * {
 * char pwd[PATH_MAX];
 * char *p_pwd, *p_oldpwd, *cp_pwd, *cp_oldpwd;
 * getcwd(pwd, sizeof(pwd));
 * cp_pwd = _strdup(pwd);
 * p_oldpwd = _getenv("OLDPWD");
 * if (p_oldpwd == NULL)
 * cp_oldpwd = cp_pwd;
 * else
 * cp_oldpwd = _strdup(p_oldpwd);
 * set_env("OLDPWD", cp_pwd);
 * if (chdir(cp_oldpwd) == -1)
 * set_env("PWD", cp_pwd);
 * else
 * set_env("PWD", cp_oldpwd);
 * p_pwd = _getenv("PWD");
 * write(STDOUT_FILENO, p_pwd, _strlen(p_pwd));
 * write(STDOUT_FILENO, "\n", 1);
 * free(cp_pwd);
 * if (p_oldpwd)
 * free(cp_oldpwd);
 * dir = args[1];
 * chdir(p_pwd);
 * }
 */
```
