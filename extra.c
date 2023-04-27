#include "shell.h"

#define BUFFER_SIZE 1024

/**
* my_getline_ - Uses static variables to keep track of
* the current position in the buffer,
* the length of the buffer, and the characters that
* have already been read from standard input
*  @_eof: - buffer size
*
* Return: The command string entered by the user.
*/
char *my_getline_(int *_eof)
{
	char *inp = NULL;
	size_t buf = 0;

	*_eof = getline(&inp, &buf, stdin);

	return (inp);
}
