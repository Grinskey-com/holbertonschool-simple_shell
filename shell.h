#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>      /* printf, getline, perror */
#include <stdlib.h>     /* free */
#include <unistd.h>     /* fork, execve, isatty */
#include <string.h>     /* strlen */
#include <sys/types.h>  /* pid_t */
#include <sys/wait.h>   /* waitpid */

extern char **environ;

extern int g_status;

/* input.c */
char *read_line(void);
void strip_line(char *line);

/* execute.c */
void execute_command(char *line, char *av0);

/* token.c */
int cmd_count(char *line, char *delimiter);
char **cmd_tokens(char *line, char *delimiter);

/* global: exit status of the last command that ran (0 at startup) */
extern int g_status;

/* builtins.c */
void print_env(void);
char *_getenv(const char *name);
int builtin_exit(char **argv, char *line);
int handle_builtin(char **argv, char *line);

/* find_path.c */
char *find_path(char *cmd);


#endif /* SHELL_H */
