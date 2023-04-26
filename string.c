#include "shell.h"


char *_strtok(char *str, const char *delim)
{
    static char *last_str = NULL;  /* Pointer to the last token */
    char *tok = NULL;              /* Pointer to the current token */

    if (str != NULL) {
        /* Start at the beginning of the string */
        last_str = str;
    } else if (last_str == NULL) {
        /* No more tokens to be found */
        return NULL;
    }

    /* Find the start of the next token */
    tok = last_str + strspn(last_str, delim);
    if (*tok == '\0') {
        /* No more tokens to be found */
        last_str = NULL;
        return NULL;
    }

    /* Find the end of the current token */
    last_str = tok + strcspn(tok, delim);
    if (*last_str != '\0') {
        *last_str++ = '\0';
    }

    return tok;
}

int _strcmp(char *s1, char *s2)
{
	int cmp = 0, i;

	if (s1 == NULL || s2 == NULL)
		return (1);
	for (i = 0; s1[i]; i++)
	{
		if (s1[i] != s2[i])
		{
			cmp = s1[i] - s2[i];
			break;
		}
		else
			continue;
	}
	return (cmp);
}
