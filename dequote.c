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
	enum quote_state state;
	static size_t (*quote_state_fn[])(const char *, enum quote_state *) = {
		quote_state_none,
		quote_state_word,
		quote_state_double,
		quote_state_single
	};

	if (!str)
		return (NULL);

	new = malloc(sizeof(char) * (dequote_len(str) + 1));
	if (!new)
		return (NULL);

	for (len = 0, state = NONE; *str; len += state_len)
	{
		if (state == DOUBLE || state == SINGLE)
		{
			state_len = quote_state_fn[state](str, &state);
			_memcpy(new + len, str, state_len);
			str += state_len;
			if (state == DOUBLE || state == SINGLE)
				str += 2;
			else if (*str)
				++str;
		}
		else
		{
			state_len = quote_state_fn[state](str, &state);
			_memcpy(new + len, str, state_len);
			str += state_len;
			if (state == DOUBLE || state == SINGLE)
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
	enum quote_state state;
	static size_t (*quote_state_fn[])(const char *, enum quote_state *) = {
		quote_state_none,
		quote_state_word,
		quote_state_double,
		quote_state_single
	};

	if (!str)
		return (0);

	for (len = 0, state = NONE; *str; len += state_len)
	{
		if (state == DOUBLE || state == SINGLE)
		{
			state_len = quote_state_fn[state](str, &state);
			str += state_len;
			if (state == DOUBLE || state == SINGLE)
				str += 2;
			else if (*str)
				++str;
		}
		else
		{
			state_len = quote_state_fn[state](str, &state);
			str += state_len;
			if (state == DOUBLE || state == SINGLE)
				++str;
		}
	}
	return (len);
}
