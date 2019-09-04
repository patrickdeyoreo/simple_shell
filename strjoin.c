#include "string.h"

/**
 * strjoin - joins two strings with a character
 * @c: character passed
 * @s1: string passed
 * @s2: string passed
 * @sizeptr: address to store the size of the new string
 *
 * Return: new string
 */
char *strjoin(const char *s1, const char *s2, char c, size_t *sizeptr)
{
	char *new;
	ssize_t s1_len, s2_len;

	if (!s1)
		s1 = "";
	if (!s2)
		s2 = "";

	s1_len = _strlen(s1);
	s2_len = _strlen(s2);

	new = malloc(sizeof(char) * (s1_len + s2_len + (c != '\0') + 1));
	if (!new)
		return (NULL);

	if (sizeptr)
		*sizeptr = s1_len + s2_len + (c != '\0') + 1;

	_memcpy(new, s1, s1_len);
	*(new + s1_len) = c;
	_memcpy(new + s1_len + (c != '\0'), s2, s2_len + 1);

	return (new);
}


/**
 * strjoina - join strings from an array with a character
 * @arr: array of strings
 * @c: character
 * @sizeptr: address to store the size of the new string
 *
 * Return: a dynamically-allocated string of the elements in arr joined by c
 */
char *strjoina(const char **arr, char c, size_t *sizeptr)
{
	char *new;
	size_t n = 0, len = 0;

	while (arr[n])
		len += _strlen(arr[n++]);

	new = malloc(sizeof(char) * (len + (c ? n : 1)));
	if (!new)
		return (NULL);

	if (sizeptr)
		*sizeptr = len + (c ? n : 1);

	for (len = 0; *arr; ++arr)
	{
		_strcpy(new + len, *arr);
		len += _strlen(*arr);
		if (c && --n)
			new[len++] = c;
	}
	return (new);
}


/**
 * strjoinl - joins a NULL terminated list of strings with a character
 * @sizeptr: address to store the size of the new string
 * @c: character
 * @...: strings
 *
 * Return: new string
 */
char *strjoinl(size_t *sizeptr, char c, ...)
{
	char *new, *tmp;
	size_t n = 0, len = 0;
	va_list strings;

	va_start(strings, c);
	while ((tmp = va_arg(strings, char *)))
		++n, len += _strlen(tmp);
	va_end(strings);

	new = malloc(sizeof(char) * (len + (c ? n : 1)));
	if (!new)
		return (NULL);

	if (sizeptr)
		*sizeptr = len + (c ? n : 1);

	len = 0;
	va_start(strings, c);
	while ((tmp = va_arg(strings, char *)))
	{
		_strcpy(new + len, tmp);
		len += _strlen(tmp);
		if (c && --n)
			new[len++] = c;
	}
	va_end(strings);
	return (new);
}
