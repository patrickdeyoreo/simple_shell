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
		str += (1 && (state & (Q_DOUBLE | Q_SINGLE | Q_ESCAPE)));
		state_len = quote_state_len(str, state);
		if (state & Q_DOUBLE)
		{
			for ( ; state_len; --state_len)
			{
				if (quote_state(*str++) & Q_ESCAPE)
				{
					if (*str == '\n')
					{
						++str, --state_len;
						continue;
					}
					if (_isspecial_double(*str))
						++str, --state_len;
				}
				new[len++] = str[-1];
			}
		}
		_memcpy(new + len, str, state_len);
		len += state_len;
		str += state_len;
		str += (*str && (state & (Q_DOUBLE | Q_SINGLE)));
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
		str += (1 && (state & (Q_DOUBLE | Q_SINGLE | Q_ESCAPE)));
		state_len = quote_state_len(str, state);
		if (state & Q_DOUBLE)
		{
			for ( ; state_len; --state_len)
			{
				if (quote_state(*str++) & Q_ESCAPE)
				{
					if (*str == '\n')
					{
						++str, --state_len;
						continue;
					}
					if (_isspecial_double(*str))
						++str, --state_len;
				}
				len++;
			}
		}
		len += state_len;
		str += state_len;
		str += (*str && (state & (Q_DOUBLE | Q_SINGLE)));
	}
	return (len);
}
