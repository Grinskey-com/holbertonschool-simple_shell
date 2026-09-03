	int main(void)
{
	char *path;

	/* Test 1: Bare command in PATH */
	path = find_path("ls");
	printf("ls  -> %s\n", path ? path : "NOT FOUND");
	free(path);

	/* Test 2: Direct absolute path */
	path = find_path("/bin/pwd");
	printf("/bin/pwd -> %s\n", path ? path : "NOT FOUND");
	free(path);

	/* Test 3: Non-existent command */
	path = find_path("fake_command_123");
	printf("fake_command_123 -> %s\n", path ? path : "NOT FOUND");
	free(path);

	return (0);
}

