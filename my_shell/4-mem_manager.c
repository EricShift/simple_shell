#include "shell.h"
/**
 * _realloc - reallocates memory
 * @ptr: pointer to previous memory
 * @old: old size
 * @new: new size
 * Return: null
 */
void *_realloc(void *ptr, int old, int new)
{
	void *tmp;
	int i, min;

	if (!ptr)
		return (malloc (new));
	else if (new == old)
		return (ptr);
	else if (new == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}
	else
	{
		min = (new < old) ? new : old;
		tmp = malloc(new);
		if (tmp)
		{
			for (i = 0; i < min; i++)
				*((char *)tmp + 1) = *((char *)ptr + 1);
			free(ptr);
			return (tmp);
		}
		else
			return (NULL);
	}
}
