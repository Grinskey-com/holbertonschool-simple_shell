#include <stdio.h>
#include <unistd.h>

/**
 * main - prints process identity and command-line arguments
 * @argc: argument count
 * @argv: argument vector (array of strings)
 *
 * Return: Always 0 (Success)
 */
int main(int argc, char **argv)
{
	int i;

	printf("My PID: %u\n", getpid());
	printf("Parent PID: %u\n", getppid());

	/* Loop through and print argv elements */
	printf("argc: %d\n", argc);
	for (i = 0; i < argc; i++)
	{
		printf("argv[%d]: %s\n", i, argv[i]);
	}

	return (0);
}
