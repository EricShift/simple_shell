#include "shell.h"
/**
 * _printf - prints to std output
 * @var: pointer to variable string
 * @fd: file descriptor
 * Return: null
 */
int _printf(char *var, int fd)
{
	return (write(fd, var, _strlen(var)));
}
/**
 * get_func - gets function
 * @command: command
 * Return: null
 */
void (*get_func(char *command))(char **)
{
	int i;

	map_func map[] = {
		{"env", env},
		{"cd", ch_dir},
		{"exit", quit}
	};

	for (i = 0; i < 3; i++)
	{
		if (_strcmp(command, map[i].cmd_name) == 0)
			return (map[i].func);
	}
	return (NULL);
}
