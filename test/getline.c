#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * main - prompt loop that reads and echoes input
 * @ac: argument count (unused)
 * @av: argument vector (unused)
 *
 * Return: Always 0 (Success)
 */
int getline(int ac, char **av)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;

	(void)ac;
	(void)av;

	printf("$ ");
	nread = getline(&line, &len, stdin);
	if (nread == -1)          /* EOF (Ctrl+D) or error */
	{
		printf("\n");
		free(line);
		return (0);
	}
	printf("You typed: %s", line); /* line still has its \n */
	free(line);

	return (0);
}
