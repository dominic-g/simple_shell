#include "shell.h"
/**
 * read_input - reads input from the user
 *
 * Description:
 * This function reads a line of input from the user and stores it
 * in a dynamically allocated buffer. The buffer is resized as
 * needed to accommodate the input.
 *
 * Return: a pointer to the input buffer, or NULL on error or
 * end-of-file condition (Ctrl-D)
 */
char *read_input(void)
{
char *input;
size_t input_length = 0;
ssize_t read;

printf("$ "); /* Print the prompt*/

read = getline(&input, &input_length, stdin);

if (read == -1)
{
if (feof(stdin))
{
/* End of file was reached, so print a new line and exit*/
printf("\n");
exit(EXIT_SUCCESS);
}
else
{
/* There was an error, so print an error message and exit*/
perror("read_input");
exit(EXIT_FAILURE);
}
}

/* Remove the newline character from the end of the input string*/
input[strcspn(input, "\n")] = '\0';

return (input);
}
