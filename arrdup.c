#include "tokens.h"

/**
 * arrjoin - join two arrays
 * @arr1: the first array
 * @arr2: the second array
 *
 * Return: a dynamically-allocated array of the elements from arr1 and arr2
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

