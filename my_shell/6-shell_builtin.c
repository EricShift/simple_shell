#include "shell.h"
/**
 * env - environmemt builtin
 * @command: builtin command
 * Return: 0
 */
void env(char **command __attribute__((unused)))
{
	int i = 0;

	while (environ[i])
	{
		_printf(environ[i++], STDOUT_FILENO);
		_printf("\n", STDOUT_FILENO);
	}
}
/**
 * quit - quit builtin
 * @command: builtin command
 * Return: 0
 */
void quit(char **command)
{
	(void) command;
}
/**
 * ch_dir - change directory builtin
 * @command: builtin command
 * Return: 0
 */
void ch_dir(char **command)
{
	(void) command;
}
