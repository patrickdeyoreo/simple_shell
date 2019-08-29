#include "quote.h"
/**
 * get_quote_state - sets the state
 * @c: argument passed
 * quote_state_t - a quote state mnemonic
 * Return: quote_state_t
 */

quote_state_t get_quote_state(int c)
{
	if (_isspace(c))
		return (NONE);
	if (c == '"')
		return (DOUBLE);
	if (c == '\'')
		return (SINGLE);
	return (WORD);
}
/**
 * quote_state_none - returns the number of characters
 * @str: string passed
 * @state: state
 * Return: number of characters
 */

size_t quote_state_none(const char *str, quote_state_t *state)
{
	size_t len = 0;

	while (_isspace(*str))
		++str, ++len;
	*state = get_quote_state(*str);
	return (len);
}
/**
 * quote_state_word - returns the number of characters
 * @str: string passed
 * @state: state
 * Return: number of characters
 */

size_t quote_state_word(const char *str, quote_state_t *state)
{
	size_t len = 0;

	while (*str && !_isspace(*str) && !_isquote(*str))
		++str, ++len;
	*state = get_quote_state(*str);
	return (len);
}

/**
 * quote_state_double - returns the number of characters
 * @str: string passed
 * @state: state
 * Return: number of characters
 */
size_t quote_state_double(const char *str, quote_state_t *state)
{
	size_t len = 0;

	while (*str && *str != '"')
		++str, ++len;
	if (*str)
		*state = get_quote_state(*(str + 1));
	else
		*state = NONE;
	return (len);
}
/**
 * quote_state_single - returns the number of characters
 * @str: string passed
 * @state: state
 * Return: number of characters
 */

size_t quote_state_single(const char *str, quote_state_t *state)
{
	size_t len = 0;

	while (*str && *str != '\'')
		++str, ++len;
	if (*str)
		*state = get_quote_state(*(str + 1));
	else
		*state = NONE;
	return (len);
}

