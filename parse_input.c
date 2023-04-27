#include "shell.h"
/**
 * parse_input - parses input into tokens
 * @input: pointer to input buffer
 *
 * Description:
 * This function parses the input buffer into tokens, splitting
 * on whitespace. The tokens are stored in a dynamically allocated
 * array of strings.
 *
 * Return: a pointer to the array of tokens, or NULL on error
 */
char **parse_input(char *input)
{
char *token;
char **tokens = malloc(sizeof(char *) * 2);

if (!tokens)
{
perror("malloc failed");
exit(EXIT_FAILURE);
}
token = strtok(input, " \n");
if (!token)
{
free(tokens);
return (NULL);
}
tokens[0] = token;
tokens[1] = NULL;
return (tokens);
}
