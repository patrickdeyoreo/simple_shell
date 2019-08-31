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

	new = malloc(s1_len + s2_len + 2);
	if (!new)
		return (NULL);

	_strcpy(new, s1);
	new[s1_len] = c;
	_strcpy(new + s1_len + 1, s2);

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
	size_t len;
	va_list strings;

	va_start(strings, c);

	for (len = 0; (tmp = va_arg(strings, char *)); len += _strlen(tmp) + 1)
		;

	va_end(strings);

	new = malloc(len + 1);
	if (!new)
		return (NULL);

	va_start(strings, c);

	for (len = 0; (tmp = va_arg(strings, char *)); len += _strlen(tmp) + 1)
	{
		_strcpy(new + len, tmp);
		new[len] = c;
	}

	va_end(strings);

	return (new);
}
