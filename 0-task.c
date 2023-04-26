#include "shell.h"


/**
* prompt - Displays the prompt symbol to indicate
* that the shell is ready to receive input.
*/
void prompt(void)
{
printf("$ ");
}
/**
* read_command - Reads a command from the user's input using fgets() function
* and returns it as a string. If fgets() returns NULL,
* it means that the end of the input has been reached
*  and the program should exit.
*
*  Return: The command string entered by the user.
*/
char *read_command(void)
{
char cmd[MAX_CMD_LEN];
if (fgets(cmd, MAX_CMD_LEN, stdin) == NULL)
{
printf("\n");
exit(0);
}
cmd[strcspn(cmd, "\n")] = '\0';
return (strdup(cmd));
}
/**
* parse_command - Takes a command string as input
* and splits it into individual words
* using the first word as the command and the
* remaining words as its arguments.
* @cmd: The command string to be parsed.
* @args: An array to store the parsed words.
*/
void parse_command(char *cmd, char **args)
{
char *arg;
int i = 0;
arg = _strtok(cmd, " \t\n");
while (arg != NULL)
{
args[i++] = arg;
arg = _strtok(NULL, " \t\n");
}
args[i] = NULL;
}


/**
* main - Entry point of the simple shell
*
* Return: Always 0 on success
*/
int main(void)
{
char *cmd;
char *args[MAX_CMD_LEN];
int run;
run = 1;

while (run)
{
prompt();
cmd = my_getline_();
if (cmd != NULL)
{
parse_command(cmd, args);

run = execute_command(args);
}
free(cmd);
}

return (0);
}

