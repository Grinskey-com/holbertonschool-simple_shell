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
	char *path;
	
	/* split the line into an array of argument tokens */
	argv = cmd_tokens(line, " \t");
	if (argv == NULL || argv[0] == NULL)
	{
		free(argv);
		return;
	}

	/* dispatch to a builtin (env, exit, ...) if argv[0] matches one */
	if (handle_builtin(argv, line))
	{
		free(argv);
		return;
	}

	path = find_path(argv[0]);
	if (path == NULL)
	{
		fprintf(stderr, "%s: 1: %s: not found\n", av0, argv[0]);
		g_status = 127;
		free(argv);
		return;
	}

	fflush(stdout);
	pid = fork();
	if (pid == -1)
	{
		perror("fork failed");
		free(path);
		free(argv);
		return;
	}
	if (pid == 0)
	{
		execve(path, argv, environ);
		perror(av0);
		_exit(127);
	}
	else
	{
		wait(&status);
		if (WIFEXITED(status))
			g_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_status = 128 + WTERMSIG(status);
		free(path);
		free(argv);
	}
}
