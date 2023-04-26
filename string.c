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

