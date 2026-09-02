#include "shell.h"

/**
 * execute_command - forks, execves, and waits for a single command
 * @line: the command to run (no trailing newline/whitespace)
 * @av0: the shell's own argv[0], used in error messages
 */
void execute_command(char *line, char *av0)
{
	pid_t pid;
	int status;
	char **argv;
	
	/* split the line into an array of argument tokens */
	argv = cmd_tokens(line, " \t");

	/* if argv[0] is 'env', skip the rest of the function */
	if (strcmp(argv[0], "env") == 0)
	{
		print_env();
		free(argv);
		return;
	}

	fflush(stdout);
	pid = fork();
	if (pid == -1)
	{
		perror("fork failed");
		return;
	}
	if (pid == 0)
	{
		execve(line, argv, environ);
		perror(av0);
		_exit(127);
	}
	else
	{
		wait(&status);
		free(argv);
	}
}
