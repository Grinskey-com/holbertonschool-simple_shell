#include "shell.h"

/**
 * cmd_count - counts the number of tokens in a line, separated by
 * any of the given delimiter characters
 * @line: the string to scan
 * @delimiter: the set of delimiter characters
 *
 * Return: the number of tokens found
 */
int cmd_count(char *line, char *delimiter)
{
	int count; 
	int inside_token;
	int i; 

	count = 0;
	inside_token = 0;
	i = 0;

	while (line[i] != '\0')
	{
		/* current character of line is a delimiter, so we've left the word (if inside one) */
		if (strchr(delimiter, line[i]) != NULL)
		{
			inside_token = 0;
		}
		/* character is not a delimiter; werent inside a word - start of a new word; count increase*/
		else if (inside_token == 0)
		{
			inside_token = 1;
			count++;
		}
		i++;
	}
	return (count);
}

/**
 * cmd_tokens - splits a line into a NULL-terminated array of tokens
 * @line: the string to split (modified in place by strtok)
 * @delimiter: the set of delimiter characters
 *
 * Return: array of pointers to each token, or NULL on failure
 */
char **cmd_tokens(char *line, char *delimiter)
{
	char **argv; 
	char *token; 
	int count; 
	int i; 

	/* how many tokens becomes count */
	count = cmd_count(line, delimiter);
	
	/* allocate array of token pointers, plus one slot for the NULL terminator */
	argv = malloc(sizeof(char *) * (count + 1));
	if (argv == NULL)
	{
		return (NULL);
	}
	i = 0;
	token = strtok(line, delimiter);
	/* store each token strtok finds until there are none left */
	while (token != NULL)
	{
		argv[i] = token;
		i++;
		token = strtok(NULL, delimiter);
	}
	/* terminate the array so execve knows where it ends */
	argv[i] = NULL;

	return (argv);
}