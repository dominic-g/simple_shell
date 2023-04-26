#include "shell.h"


size_t _strspn(const char* str1, const char* str2) {
    const char* p = str1;
    size_t count = 0;

    while (*p != '\0') {
        const char* q = str2;
        bool found = false;

        while (*q != '\0') {
            if (*p == *q) {
                found = true;
                break;
            }
            q++;
        }

        if (!found) {
            return count;
        }

        count++;
        p++;
    }

    return count;
}

size_t _strcspn(const char* str, const char* search) {
    const char* p = str;
    size_t count = 0;
    while (*p != '\0') {
        const char* q = search;
        while (*q != '\0') {
            if (*p == *q) {
                return count;
            }
            q++;
        }
        p++;
        count++;
    }
    return count;
}


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
    tok = last_str + _strspn(last_str, delim);
    if (*tok == '\0') {
        /* No more tokens to be found */
        last_str = NULL;
        return NULL;
    }

    /* Find the end of the current token */
    last_str = tok + _strcspn(tok, delim);
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

char* _strdup(const char* str) {
	char* copy;
	size_t i;
    size_t len = 0;
    while (str[len] != '\0') {
        len++;
    }

    copy = (char*) malloc(sizeof(char) * (len + 1));
    if (copy == NULL) {
        return NULL;
    }

    for (i = 0; i < len; i++) {
        copy[i] = str[i];
    }
    copy[len] = '\0';

    return copy;
}

