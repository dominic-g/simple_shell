#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_CMD_LEN 1024

#ifndef SHELL_H
#define SHELL_H

extern char **environ;

/*functions declarations*/
void prompt(void);
void parse_command(char *cmd, char **args);
int execute_command(char** args);
int main(void);

/*Extra File */
char *my_getline_(void);

/*Strings*/
char *_strtok(char *str, const char *delim);
int _strcmp(char *s1, char *s2);

#endif
