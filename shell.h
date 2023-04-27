#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <limits.h>

#define MAX_CMD_LEN 1024

extern char **environ;

/**
 * struct data - struct that contains all relevant data on runtime
 * @av: argument vector
 * @input: command line written by the user
 * @args: tokens of the command line
 * @status: last status of the shell
 * @counter: lines counter
 * @_environ: environment variable
 * @pid: process ID of the shell
 */
typedef struct data
{
	char **av;
	char *input;
	char **args;
	int status;
	int counter;
	char **_environ;
	char *pid;
} data_shell;

/*functions declarations*/
void prompt(void);
void parse_command(char *cmd, char **args);
int main(int argc, char *argv[]);
void _printfi(int text);
void _printfc(char *text);

/* int.c */
int get_len(int n);
char *int_to_char(int n);
int char_to_int(char *s);

/*Extra File */
char *my_getline_(int *_eof);
void free_data(data_shell *data_st);
void set_data(data_shell *data_st, char **av);
char *_itoa(int n);

/*Handle File */
char *remove_comment(char *cmd);

/* syntax.c */
int repeated_char(char *input, int i);
int error_sep_op(char *input, int i, char last);
int first_char(char *input, int *i);
void syntax_error(data_shell *datash, char *input, int i, int bol);
int check_syntax_error(data_shell *datash, char *input);

/*Strings*/
size_t _strcspn(const char *str, const char *search);
char *_strtok(char *str, const char *delim);
int _strcmp(char *s1, char *s2);
size_t _strspn(const char *str1, const char *str2);
char *_strdup(const char *str);
char *_strcpy(char *dest, char *src);
char *_strncpy(char *dest, const char *src, size_t n);
char *_strcat(char *dest, const char *src);
char *_strchr(char *s, char c);
int _strlen(const char *s);
int cmp_chars(char str[], const char *delim);
int _isdigit(const char *s);

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
