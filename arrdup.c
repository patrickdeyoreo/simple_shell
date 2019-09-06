#include "tokens.h"

/**
 * arrdup - duplicate an array
 * @arr: the array to duplicate
 *
 * Return: a dynamically-allocated duplicate of arr
 */
char **arrdup(char **arr)
{
	char **new;
	size_t len = 0;

	if (arr)
	{
		while (arr[len])
			++len;
	}
	new = malloc(sizeof(char *) * (len + 1));
	if (!new)
		return (NULL);

	len = 0;
	if (arr)
	{
		while (*arr)
			new[len++] = _strdup(*arr++);
	}
	new[len] = NULL;
	return (new);
}

