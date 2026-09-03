#include "shell.h"

/**
 * main - entry point for the simple shell
 * @ac: argument count (unused)
 * @av: argument vector; av[0] used in error messages
 *
 * Return: Always 0.
 */
int main(int ac, char **av)
{
	char *line;

	(void)ac;
	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "$ ", 2);

		line = read_line();
		if (line == NULL)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			break;
		}

		strip_line(line);

		if (line[0] != '\0')
			execute_command(line, av[0]);
		
		free(line);
	}

	return (0);
}
