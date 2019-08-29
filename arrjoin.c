#include "shell.h"

/**
 * arrjoin - join two arrays
 * @arr1: the first array
 * @arr2: the second array
 *
 * Return: a dynamically-allocated array of the elements from arr1 and arr2
 */
char **arrjoin(char **arr1, char **arr2)
{
	char **new_arr;
	size_t arr1_len, arr2_len, new_len;

	for (arr1_len = 0; arr1[arr1_len]; ++arr1_len)
		;
	for (arr2_len = 0; arr2[arr2_len]; ++arr2_len)
		;
	new_len = arr1_len + arr2_len;

	new_arr = malloc(sizeof(char *) * (new_len + 1));
	if (!new_arr)
		return (NULL);

	new_len = 0;
	while (*arr1)
		new_arr[new_len++] = _strdup(*arr1++);
	while (*arr2)
		new_arr[new_len++] = _strdup(*arr2++);
	new_arr[new_len] = NULL;

	return (new_arr);
}

