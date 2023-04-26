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
int main(void);

/*Extra File */
char *my_getline_(void);

/*Strings*/
size_t _strcspn(const char *str, const char *search);
char *_strtok(char *str, const char *delim);
int _strcmp(char *s1, char *s2);
size_t _strspn(const char *str1, const char *str2);
char *_strdup(const char *str);

/*Tools*/
int _atoi(char *c);

/*Execute*/
int search_command(char **args, char *command);
int execute_command(char **args, int interactive_mode);
void check_path(char *path_copy);
int handle_env(void);
int handle_exit(char **args);

#endif
