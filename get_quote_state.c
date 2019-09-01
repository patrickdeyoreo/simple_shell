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
	if (c == '"')
		return (DOUBLE);
	if (c == '\'')
		return (SINGLE);
	return (WORD);
}


/**
 * get_quote_state_fn - get the state associated with a given character
 * @c: character
 *
 * Return: the state associated with c
 */
size_t (*get_quote_state_fn(quote_state_t s))(const char *, quote_state_t *)
{
	if (s == NONE)
		return (quote_state_none);
	if (s == DOUBLE)
		return (quote_state_double);
	if (s == SINGLE)
		return (quote_state_single);
	return (quote_state_word);
}


