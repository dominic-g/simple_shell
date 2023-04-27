#ifndef _SHELL_
#define _SHELL_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>

#define BUFFER_SIZE 1024
#define MAX_COMMAND_LENGTH 100

int main(void);
void execute_command(char **args);
char *read_input(void);
char **parse_input(char *input);

#endif