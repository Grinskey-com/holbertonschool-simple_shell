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