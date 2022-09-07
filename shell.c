#include "main.h"

/**
 * main - The main shell program
 * @ac: The argument count
 * @av: The argument vector
 * @env: the environment variable
 *
 * Return: Always zero (0)
 */

int main(__attribute__((unused)) int ac, __attribute__((unused)) char **av,
		__attribute__((unused)) char **env)
{
	char *line = NULL;
	size_t lineCap = 0;
	size_t lineReturn = 1;
	int stats;
	int flag;
	char **toks;
	pid_t childPid;

	while (lineReturn > 0)
	{
		flag = 1;
		printf("$ ");
		fflush(stdout);
		lineReturn = getline(&line, &lineCap, stdin);
		if (lineReturn == ULONG_MAX)
			break;
		toks = populate(line, 0);
		process(toks, env, &flag);
		if (flag == 1)
			childPid = fork();
		if (childPid != -1 && flag == 1)
		{
			if (childPid == 0)
			{
				execve(toks[0], toks, NULL);
				perror(av[0]);
				exit(1);
			}
			else
			{
				wait(&stats);
			}
		}
	}
	return (0);
}
