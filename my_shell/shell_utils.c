#include "shell.h"
/**
 * ctrl_C - prints prompt
 * @signum: signum
 * Return: null
 */
void ctrl_C(int signum)
{
	if (signum == SIGINT)
		_printf("\n ($)", STDIN_FILENO);
}

/**
 * _getline - takes the input from the user
 * Return: the string read
 */
char *_getline(void)
{
	int bufSize = READ_BUF, no_read, position = 0;

	char *buffer = malloc(bufSize * sizeof(char));
	char c;

	if (buffer == NULL)
	{
		perror("failed to allocate memory");
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		no_read = read(STDIN_FILENO, &c, 1);
		if (c == EOF || !no_read)
		{
			if (isatty(STDIN_FILENO) == 1)
			{
				_printf("\n", STDIN_FILENO);
				return (NULL);
			}
		}
		else if (c == '\n' || !no_read)
		{
			buffer[position] = '\0';
			return (buffer);
		}
		else
			buffer[position] = c;
		position++;

		if (position >= bufSize)
		{
			bufSize += READ_BUF;
			buffer = _realloc(buffer, READ_BUF, bufSize);
			if (!buffer)
			{
				perror("failed to allocate a space in memory");
				exit(EXIT_FAILURE);
			}
		}
	}
}

/**
 * tokenize - split a string
 * @str: string to split
 * @delim: character to split string
 * Return: pointer to new or null
 */
char **tokenize(char *str, const char *delim)
{
	int k = 0, j = 0, i = 0, size = 0, lens[1200];
	char **arr;

	if (str == NULL || !str(*str))
		return (NULL);
	for (i = 0; str[i]; i++)
	{
		if (is_delimiter(delim, str[i]))
			continue;
		j = i;
		while (!is_delimiter(delim, str[i]) && str[i])
			i++;
		if (i > j)
			lens[size++] = i - j;
		if (!str[i])
			break;
	}
	if (!size)
		return (NULL);

	arr = malloc((size + 1) * sizeof(chsr *));
	for (i = 0; str[i]; i++)
	{
		if (is_delimiter(delim, str[i]))
			continue;
		arr[k] = malloc((lens[k] + 1) * sizeof(char));
		j = 0;
		while (!is_delimiter(delim, str[i]) && str[i])
			arr[k][j++] = str[i++];
		arr[k++][j] = '\0';
		if (!str[i])
			break;
	}
	arr[size] = NULL;
	return (arr);
}

/**
 * is_delimiter - checksif a character is in delimiter
 * @delimiters: pointer to delimiter
 * @c: character to ckeck
 * Return: 1 for true and 0 for false
 */
int is_delimiter(const char *delimiters, char c)
{
	int i = 0;

	if (!delimiters)
		return (0);
	while (delimiters[i])
	{
		if (delimiters[i] == c)
			return (1);
		i++;
	}
	return (0);
}

/**
 * shell_execute - checks a command to execute
 * @command: pointer to command
 * @cmd_type: command type
 * Return: command type
 */
void shell_execute(char **command, int cmd_type)
{
	int stat;
	pid_t PID;

	if (cmd_type == EXTERNAL_CMD || cmd_type == PATH_CMD)
	{
		PID = fork();

		if (PID == 0)
		{
			execute(command, cmd_type);
		}
		if (PID < 0)
		{
			perror("failed to call fork");
			exit(1);
		}
		else
			wait(&stat);
	}
	else
		execute(command, cmd_type);
}

/**
 * check_command - checks for command
 * @command: type of command
 * Return: command type
 */
int check_command(char *command)
{
	int i = 0;
	char *int_cmd[] = {"exit", "cd", "env", NULL};

	while (command[])
	{
		if (command[i] == '\')
			return (EXTERNAL_CMD);
		i++;
	}

	i = 0;
	while (int_cmd[i] != NULL)
	{
		if (_strcmp(command, int_cmd[i]) == 0)
			return (INTERNAL_CMD);
		i++;
	}

	return (INVALID_CMD);
}

/**
* execute - executes a command
* @commands: commands
* cmd_type: command type
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
