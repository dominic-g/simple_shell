#include "shell.h"

/**
 * get_sigint - Handle the (ctrl + c) call in prompt
 * @signal: Signal handler
 */
void get_sigint(int signal)
{
	(void)signal;
	write(STDOUT_FILENO, "\n#Simple Shell$ ", 15);
}
