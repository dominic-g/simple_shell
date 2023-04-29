#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include <signal.h>


extern char **environ;

typedef struct data
{
char **av;
char *input;
char **args;
int status;
int counter;
char **_environ;
char *pid;
} custom_struct;


typedef struct sep_list_s
{
char separator;
struct sep_list_s *next;
} custom_sep_ls;

typedef struct line_list_s
{
char *line;
struct line_list_s *next;
} custom_line_ls;

typedef struct r_var_list
{
int len_var;
char *val;
int len_val;
struct r_var_list *next;
} line_var;

typedef struct checking
{
char *name;
int (*f)(custom_struct *datash);
} custom_inbuilt;

/* lists.c */
custom_sep_ls *_asneend(custom_sep_ls **head, char separator);
void _freeseparatorls(custom_sep_ls **head);
custom_line_ls *_addendnode(custom_line_ls **head, char *line);
void _liberatelinelist(custom_line_ls **head);

line_var *_inclinevrnod(line_var **head, int lvar, char *var, int lval);
void _removelinevr(line_var **head);

int cmp_chars(char str[], const char *delim);
char *_strtok(char str[], const char *delim);
char *_strchr(char *s, char c);
int _strspn(char *s, char *accept);
int _isdigit(const char *s);
void rev_string(char *s);
int _strlen(const char *s);
char *_strcat(char *dest, const char *src);
int _strcmp(char *s1, char *s2);
char *_strdup(const char *s);
char *_strcpy(char *dest, char *src);


/* memory */
void _custommemorycopy(void *newptr, const void *ptr, unsigned int size);
void *_memallocate(void *ptr, unsigned int old_size,
unsigned int new_size);
char **_memallocatedouble(char **ptr, unsigned int old_size,
unsigned int new_size);


int _dup_char(char *input, int i);
int _find_syntax_error(char *input, int i, char last);
int _indexchar(char *input, int *i);
void syntax_error(custom_struct *datash, char *input, int i, int bool);
int _lookforsynerror(custom_struct *datash, char *input);

/* _mainrotater.c */
char *_removecomments(char *in);
void _mainrotater(custom_struct *datash);

/* _getcommand.c */
char *_getcommand(int *checkline);


/* _readline.c */
void _storecmd(char **lineptr, size_t *n, char *buffer, size_t j);
ssize_t _readline(char **lineptr, size_t *n, FILE *stream);

/* split.c */
char *_interchangechar(char *input, int bool);
void _addseparator(custom_sep_ls **head_s,
custom_line_ls **head_l, char *input);
void _movetonextline(custom_sep_ls **list_s, custom_line_ls **list_l,
custom_struct *datash);
int _cutthecommands(custom_struct *datash, char *input);
char **_tokenizeline(char *input);

/* rep_var.c */
void _promptenv(line_var **h, char *in, custom_struct *data);
int _promptdouble(line_var **h, char *in, char *st, custom_struct *data);
char *replaced_input(line_var **head, char *input, char *new_input, int nlen);
char *rep_var(char *input, custom_struct *datash);


/* exec_line */
int exec_line(custom_struct *datash);

/* cmd_exec.c */
int is_cdir(char *path, int *i);
char *_which(char *cmd, char **_environ);
int check_executable(custom_struct *datash);
int check_error_cmd(char *dir, custom_struct *datash);
int cmd_exec(custom_struct *datash);

/* env1.c */
char *_getenv(const char *name, char **_environ);
int _env(custom_struct *datash);

/* env2.c */
char *copy_info(char *name, char *value);
void set_env(char *name, char *value, custom_struct *datash);
int _setenv(custom_struct *datash);
int _unsetenv(custom_struct *datash);

/* cd.c */
void change_directory_dot(custom_struct *data);
void change_directory_to(custom_struct *data);
void change_directory_to_previous(custom_struct *data);
void home_dir(custom_struct *data);

/* cd_shell.c */
int cd_shell(custom_struct *datash);

/* get_builtin */
int (*get_builtin(char *cmd))(custom_struct *datash);

/* _exit.c */
int exit_shell(custom_struct *datash);

/* _stdlib.c */
int get_len(int n);
char *int_to_char(int n);
int char_to_int(char *s);

/* _error.c */
char *strcat_cd(custom_struct *, char *, char *, char *);
char *error_get_cd(custom_struct *datash);
char *error_not_found(custom_struct *datash);
char *error_exit_shell(custom_struct *datash);
char *error_get_alias(char **args);
char *error_env(custom_struct *datash);
char *error_env_message(custom_struct *ss_data);
char *error_syntax(char **args);
char *error_permission(char **args);
char *error_path_126(custom_struct *datash);
char *error_path_126_message(custom_struct *ss_data);

/* get_error.c */
int get_error(custom_struct *datash, int eval);
int get_error_builtin(custom_struct *data_st, int error_val);

/*err1.c file*/
char *strcat_cd_message(custom_struct *ss_data,
char *msg, char *error, char *ss_str);
char *error_get_cd_message(custom_struct *ss_data);
char *error_not_found_message(custom_struct *ss_data);
char *error_exit_shell_message(custom_struct *ss_data);

/* get_sigint.c */
void get_sigint(int sig);

/* _help.c */
void help_env_info(void);
void help_setenv_info(void);
void help_unsetenv_info(void);
void general_help_info(void);
void help_exit_info(void);
void help_info(void);
void help_alias_info(void);
void help_cd_info(void);

/* get_help.c */
int get_help(custom_struct *datash);
int get_help_message(custom_struct *data_st);

#endif
