#include "shell.h"

/**
 * print_env - prints the current environment, one variable per line
 */
void print_env(void)
{
	int i;

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

//void _exit()

