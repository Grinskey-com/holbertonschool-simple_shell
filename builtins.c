#include "shell.h"

/**
 * print_env - prints the current environment, one variable per line
 */
void print_env(void)
{
	int i;

	if (environ == NULL)
		return;

	i = 0;
	while (environ[i] != NULL)
	{
		printf("%s\n", environ[i]);
		i++;
	}
}

char *_getenv(const char *name)
{
	int i, len;

	len = strlen(name);
	for (i = 0; environ[i] != NULL; i ++)
	{
		if (strncmp(environ[i], name, len) == 0 && (environ[i][len] == '='))
		return (environ[i] + len + 1);
	}
	return (NULL);
}

/**
 * is_shell_number - checks whether a string is a valid integer literal
 * @s: the string to check (optionally signed digits only)
 *
 * Return: 1 if valid, 0 otherwise
 */
static int is_shell_number(char *s)
{
	int i;

	i = 0;
	if (s[0] == '+' || s[0] == '-')
		i++;
	if (s[i] == '\0')
		return (0);
	for (; s[i] != '\0'; i++)
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
	}
	return (1);
}

/**
 * shell_atol - converts a validated numeric string to a long
 * @s: the string to convert (already checked by is_shell_number)
 *
 * Return: the converted value
 */
static long shell_atol(char *s)
{
	int i, sign;
	long result;

	i = 0;
	sign = 1;
	result = 0;

	if (s[0] == '+' || s[0] == '-')
	{
		if (s[0] == '-')
			sign = -1;
		i++;
	}
	for (; s[i] != '\0'; i++)
		result = (result * 10) + (s[i] - '0');

	return (result * sign);
}

/**
 * builtin_exit - handles the "exit" builtin, with or without an argument
 * @argv: tokenized command, argv[0] is "exit"
 * @line: the current input line, freed here since exit() does not return
 *
 * Return: 1 if execution should continue (bad argument, did not exit);
 * otherwise this function calls exit() and does not return
 */
int builtin_exit(char **argv, char *line)
{
	long code;

	if (argv[1] == NULL)
	{
		code = g_status;
	}
	else
	{
		if (!is_shell_number(argv[1]))
		{
			fprintf(stderr, "exit: Illegal number: %s\n", argv[1]);
			return (1);
		}
		code = shell_atol(argv[1]);
	}

	free(line);
	free(argv);
	exit(((unsigned long)code) % 256);
}

/**
 * handle_builtin - checks argv[0] against known builtins and runs it
 * @argv: tokenized command
 * @line: the current input line (passed through for cleanup on exit)
 *
 * Return: 1 if argv[0] was a builtin (handled), 0 otherwise
 */
int handle_builtin(char **argv, char *line)
{
	if (strcmp(argv[0], "env") == 0)
	{
		print_env();
		return (1);
	}
	if (strcmp(argv[0], "exit") == 0)
	{
		builtin_exit(argv, line);
		/* only reached if the argument was invalid */
		return (1);
	}
	return (0);
}
