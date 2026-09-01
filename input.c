#include "shell.h"

/**
 * read_line - reads one line of input from stdin
 *
 * Return: malloc'd string containing the line, or NULL on EOF/error
 */
char *read_line(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;

	nread = getline(&line, &len, stdin);
	if (nread == -1)
	{
		free(line);
		return (NULL);
	}
	return (line);
}

/**
 * strip_line - removes trailing \n, spaces, and tabs
 * @line: the string to modify in place
 */
void strip_line(char *line)
{
	size_t cmd_len;

	cmd_len = strlen(line);
	while (cmd_len > 0 && (line[cmd_len - 1] == '\n' ||
	       line[cmd_len - 1] == ' ' || line[cmd_len - 1] == '\t'))
	{
		line[cmd_len - 1] = '\0';
		cmd_len--;
	}
}
