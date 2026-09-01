#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

/**
 * main - prints a prompt, reads a line, and echoes it back
 * @ac: argument count (unused)
 * @av: argument vector (unused)
 *
 * Return: Always 0 (Success).
 */
int main(int ac, char **av)
{
	char *line = NULL;
	size_t len = 0;
	size_t cmd_len;
	ssize_t nread;
	pid_t pid;
	int status;

	(void)ac;
	(void)av;

	while (1)
	{
		/* print prompt only if running in an interactive terminal */
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "$ ", 2);

		/* read input from stdin */
		nread = getline(&line, &len, stdin);

		/* check for EOF (Ctrl+D) or read error */
		if (nread == -1)
		{
			/* print newline on interactive EOF for clean shell exit */
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			free(line);
			break;
		}
		cmd_len = strlen(line);

		/* strip trailing newline */
		if (cmd_len > 0 && line[cmd_len - 1] == '\n')
		{
			line[cmd_len - 1] = '\0';
		}
		if (line[0] == '\0')
			continue;

		/* fork time*/
		fflush(stdout);
		pid = fork();
		
		if (pid == -1)
		{
			perror("fork failed");
			free(line);
			continue;
		}
		if (pid == 0)//add execve
		{	
			printf("I'm the child, my pid is %d\n", getpid());
			free(line);
			exit(0);
		}
		else // add waitpid
		{
			printf("I'm the parent, my child's pid is %d\n", pid);
			wait(&status);
		}	
	}

	return (0);
}
