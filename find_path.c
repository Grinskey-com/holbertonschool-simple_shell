#include "shell.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

extern char **environ;

/**
 * find_path - Resolves a command string into an absolute executable path
 * @cmd: User typed command (e.g., "ls", "/bin/ls", or "./hsh")
 *
 * Return: Malloc'd string of full path if found/executable, NULL otherwise.
 */
char *find_path(char *cmd)
{
	char *path_copy, *path_env, *dir, *candidate;
	size_t len;

	if (cmd == NULL || cmd[0] == '\0')
		return (NULL);

	/* bypass if command contains '/', check direct access */
	if (strchr(cmd, '/') != NULL)
	{
		if (access(cmd, X_OK) == 0)
			return (strdup(cmd));
		return (NULL);
	}

	/* get path from get env */
	path_env = _getenv("PATH");
	if (path_env == NULL)
		path_env = "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin";
	if (path_env[0] == '\0')
		return (NULL);

	/* duplicate path */
	path_copy = strdup(path_env);
	if (path_copy == NULL)
		return (NULL);

	/* strtok section */
	dir = strtok(path_copy, ":");
	while (dir != NULL)
	{
		/* build candidate path: dir + '/' + cmd */ 
		len = strlen(dir) + strlen(cmd) + 2;
		candidate = malloc(len);
		if (candidate == NULL)
		{
			free(path_copy);
			return (NULL);
		}
		sprintf(candidate, "%s/%s",dir, cmd);
	
		/* access check */
		if (access(candidate, X_OK) == 0)
		{
			free(path_copy);
			return(candidate);
		}

		free(candidate);
		dir = strtok(NULL, ":");

	}

	free(path_copy);
	return (NULL);
}
