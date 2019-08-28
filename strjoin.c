#include "shell.h"
/**
  * strjoin - joins the strings and a character into a string
  * @s1: string passed
  * @s2: string passed
  * @c: character passed
  * Return: new string
  */

char *strjoin(char *s1, char *s2, char c)
{
	char *new_s;
	ssize_t s1_len, s2_len;

	if (!s1)
		s1 = "";
	if (!s2)
		s2 = "";

	s1_len = _strlen(s1);
	s2_len = _strlen(s2);

	new_s = malloc(s1_len + s2_len + 2);
	if (!new_s)
		return (NULL);
	_strcpy(new_s, s1);
	new_s[s1_len] = c;
	_strcpy(new_s + s1_len + 1, s2);

	return (new_s);
}
