#include "shell.h"
/**
 * execute - executes a command
 * @commands: commands
 * @cmd_type: command type
 * Return: 0
 */
void execute(char **commands, int cmd_type)
{
	void (*func)(char **command);

	switch (cmd_type)
	{
		case EXTERNAL_CMD:
		{
			if (execve(commands[0], commands, NULL) == -1)
			{
				perror(_getenv("PWD"));
				exit(2);
			}
			break;
		}
		case INTERNAL_CMD:
		{
			func = get_func(commands[0]);
			func(commands);
			break;
		}
		case PATH_CMD:
		{
			break;
		}
		case INVALID_CMD:
		{
			break;
		}
	}
}
