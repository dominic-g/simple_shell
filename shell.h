#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#ifndef SHELL_H
#define SHELL_H

extern char **environ;

/*functions declarations*/
void prompt(void);
void parse_command(char *cmd, char **args);
int execute_command(char** args);
int main(void);

/*Extra File */
char *my_getline(void);

#endif
