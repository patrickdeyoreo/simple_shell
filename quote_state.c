#include "quote.h"


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
	if (state && *str)
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
	if (state && *str)
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
	if (state && *str)
		*state = get_quote_state(*(str + 1));
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
	if (state && *str)
		*state = get_quote_state(*(str + 1));
	return (len);
}

