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
	size_t len, state_len;
	quote_state_t state;

	if (!str)
		return (NULL);

	new = malloc(sizeof(char) * (dequote_len(str) + 1));
	if (!new)
		return (NULL);

	for (len = 0, state = get_quote_state(*str); *str; len += state_len)
	{
		if (state == NONE)
		{
			state_len = quote_state_none(str, &state);
			_memcpy(new + len, str, state_len);
			str += state_len;
		}
		else if (state == WORD)
		{
			state_len = quote_state_word(str, &state);
			_memcpy(new + len, str, state_len);
			str += state_len;
		}
		else
		{
			++str;
			if (state == DOUBLE)
				state_len = quote_state_double(str, &state);
			else
				state_len = quote_state_single(str, &state);
			_memcpy(new + len, str, state_len);
			str += state_len;
			if (*str)
				++str;
		}
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
	size_t len, state_len;
	quote_state_t state;

	for (len = 0, state = get_quote_state(*str); *str; len += state_len)
	{
		if (state == NONE)
		{
			state_len = quote_state_none(str, &state);
			str += state_len;
		}
		else if (state == WORD)
		{
			state_len = quote_state_word(str, &state);
			str += state_len;
		}
		else
		{
			++str;
			if (state == DOUBLE)
				state_len = quote_state_double(str, &state);
			else
				state_len = quote_state_single(str, &state);
			str += state_len;
			if (*str)
				++str;
		}
	}
	return (len);
}
