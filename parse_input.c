#include "shell.h"
#define MAX_TOKENS 100
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
    char **tokens = malloc(MAX_TOKENS * sizeof(char *));
    int i = 0;

    if (!tokens)
    {
        perror("malloc error");
        exit(EXIT_FAILURE);
    }

    token = strtok(input, " ");

    while (token != NULL)
    {
        tokens[i] = token;
        i++;

        token = strtok(NULL, " ");
    }

    tokens[i] = NULL;

    return tokens;
}
