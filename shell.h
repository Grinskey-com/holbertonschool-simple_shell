#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>      /* printf, getline, perror */
#include <stdlib.h>     /* free */
#include <unistd.h>     /* fork, execve, isatty */
#include <string.h>     /* strlen */
#include <sys/types.h>  /* pid_t */
#include <sys/wait.h>   /* waitpid */

extern char **environ;

/* input.c */
char *read_line(void);
void strip_newline(char *line);

/* execute.c */
void execute_line(char *line, char *prog_name);

#endif /* SHELL_H */
