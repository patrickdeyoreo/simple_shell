#include "quote.h"

/**
 * dequote - dequote a string
 * @str: the string to dequote
 * Return: If memory allocation fails, return NULL.
 * Otherwise return a dequoted copy of str.
 */
char *dequote(const char *str)
{
	char *new;
	size_t len = 0, state_len;
	quote_state_t state;

	if (!str)
		return (NULL);

	new = malloc(sizeof(char) * (dequote_len(str) + 1));
	if (!new)
		return (NULL);

	while (*str)
	{
		state = quote_state(*str);

		if (state & (Q_DOUBLE | Q_SINGLE | Q_ESCAPE))
			++str;

		state_len = quote_state_len(str, state);
		_memcpy(new + len, str, state_len);

		str += state_len;
		len += state_len;

		if (*str && (state & (Q_DOUBLE | Q_SINGLE)))
			++str;
	}
	new[len] = '\0';
	return (new);
}


/**
 * dequote_len - compute the length of a string after dequoting
 * @str: the string to evaluate
 * Return: Return the length of str after dequoting
 */
size_t dequote_len(const char *str)
{
	size_t len = 0, state_len;
	quote_state_t state;

	while (*str)
	{
		state = quote_state(*str);

		if (state & (Q_DOUBLE | Q_SINGLE | Q_ESCAPE))
			++str;

		state_len = quote_state_len(str, state);

		str += state_len;
		len += state_len;

		if (*str && (state & (Q_DOUBLE | Q_SINGLE)))
			++str;
	}
	return (len);
}
