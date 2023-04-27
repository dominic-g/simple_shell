#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/wait.h>

#define MAX_CMD_LEN 1024

extern char **environ;

/*functions declarations*/
void prompt(void);
void parse_command(char *cmd, char **args);
int main(int argc, char *argv[]);

/*Extra File */
char *my_getline_(int *_eof);

/*Handle File */
char *remove_comment(char *cmd);

/*Strings*/
size_t _strcspn(const char *str, const char *search);
char *_strtok(char *str, const char *delim);
int _strcmp(char *s1, char *s2);
size_t _strspn(const char *str1, const char *str2);
char *_strdup(const char *str);

/*Tools*/
int _atoi(char *c);

/*Execute*/
int search_command(char **args, char *command, char *name);
int execute_command(char **args, int interactive_mode, char *name);
void check_path(char *path_copy);
int handle_env(void);
int handle_exit(char **args);

/* mem.c */
void _memcpy(void *newptr, const void *ptr, unsigned int size);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char **_reallocdp(char **ptr, unsigned int old_size, unsigned int new_size);

#endif
