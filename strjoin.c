#include "string.h"


/**
  * strjoin - joins two strings with a character
  * @c: character passed
  * @s1: string passed
  * @s2: string passed
  *
  * Return: new string
  */
char *strjoin(const char *s1, const char *s2, char c)
{
	char *new;
	ssize_t s1_len, s2_len;

	if (!s1)
		s1 = "";
	if (!s2)
		s2 = "";

	s1_len = _strlen(s1);
	s2_len = _strlen(s2);

	new = malloc(s1_len + s2_len + (c != 0) + 1);
	if (!new)
		return (NULL);

	_strcpy(new, s1);
	if (c)
		new[s1_len] = c;
	_strcpy(new + s1_len + (c != 0), s2);

	return (new);
}


/**
 * strjoina - join strings from an array with a character
 * @arr: array of strings
 * @c: character
 *
 * Return: a dynamically-allocated string of the elements in arr joined by c
 */
char *strjoina(const char **arr, char c)
{
	char *new;
	size_t n = 0, len = 0;

	while (arr[n])
		len += _strlen(arr[n++]);

	new = malloc(len + (c ? n : 1));
	if (!new)
		return (NULL);

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
  * @c: character
  * @...: strings
  *
  * Return: new string
  */
char *strjoinl(char c, ...)
{
	char *new, *tmp;
	size_t n = 0, len = 0;
	va_list strings;

	va_start(strings, c);
	while ((tmp = va_arg(strings, char *)))
		++n, len += _strlen(tmp);
	va_end(strings);

	new = malloc(len + (c ? n : 1));
	if (!new)
		return (NULL);

	va_start(strings, c);
	len = 0;
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
