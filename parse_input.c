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
char **tokens = NULL;
char *token = NULL;
int i = 0;
int token_count = 0;

token = strtok(input, " \t\n");
while (token)
{
token_count++;
token = strtok(NULL, " \t\n");
}

tokens = malloc(sizeof(char *) * (token_count + 1));
if (!tokens)
{
perror("malloc");
exit(EXIT_FAILURE);
}

token = strtok(input, " \t\n");
while (token)
{
tokens[i] = token;
i++;
token = strtok(NULL, " \t\n");
}
tokens[i] = NULL;

return (tokens);
}
