#include "shell.h"
/**
 * remove_comment - delete comments from the input
 *
 * @cmd: command string
 * Return: command without comments
 */
char *remove_comment(char *cmd)
{
int i = 0;
int term = 0;
while (cmd[i] != '\0')
{
if (cmd[i] == '#')
{
if (i == 0)
{
free(cmd);
return (NULL);
}
else if (cmd[i - 1] == ' ' || cmd[i - 1] == '\t' || cmd[i - 1] == ';')
{
term = i;
break;
}
}
i++;
}

if (term != 0)
{
cmd = _realloc(cmd, i, term + 1);
cmd[term] = '\0';
}

return (cmd);

}
