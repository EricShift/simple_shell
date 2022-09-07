#include "main.h"

/**
 * pathfinder - finds the path varaible and enables it to run
 * @env: This is the environment varaible
 *
 * Return: The path string
 */

char *pathfinder(char **env)
{
	char *path;
	int i, pathInt = 0;

	for (i = 0; env[i] != NULL; i++)
	{
		if (env[i][0] == 'P' && env[i][1] == 'A'
				&& env[i][2] == 'T' && env[i][3] == 'H')
		{
			pathInt = i;
			break;
		}
		else
			continue;
	}

	if (pathInt)
	{
		path = _strdup(env[pathInt]);
		return (path);
	}
	return (NULL);
}
