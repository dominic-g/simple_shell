#ifndef SHELL_H
#define SHELL_H

extern char **environ;

/*functions declarations*/
void prompt(void);
char *read_command(void);
void parse_command(char *cmd, char **args);
void execute_command(char** args);
int main(void);

#endif
