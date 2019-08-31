#include "quote.h"


/**
 * get_quote_state - get the state associated with a given character
 * @c: character
 *
 * Return: the state associated with c
 */
quote_state_t get_quote_state(int c)
{
	if (_isspace(c))
		return (NONE);
	if (c == '\'')
		return (SINGLE);
	if (c == '"')
		return (DOUBLE);
	return (WORD);
}


/**
 * quote_state_none - returns the length of state
 * @str: string
 * @state: state
 *
 * Return: length of state
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
 * quote_state_word - returns the length of state
 * @str: string
 * @state: state
 *
 * Return: length of state
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
 * quote_state_double - returns the length of state
 * @str: string
 * @state: state
 *
 * Return: length of state
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
 * quote_state_single - returns the length of state
 * @str: string
 * @state: state
 *
 * Return: length of state
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

