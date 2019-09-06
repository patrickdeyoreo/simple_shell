#include "quote.h"

/**
 * quote_state - get the state associated with a given character
 * @c: character
 *
 * Return: the state associated with c
 */
quote_state_t quote_state(char c)
{
	if (_isspace(c))
		return (Q_NONE);
	if (c == '"')
		return (Q_DOUBLE);
	if (c == '\'')
		return (Q_SINGLE);
	if (c == '\\')
		return (Q_ESCAPE);
	return (Q_WORD);
}


/**
 * quote_state_fn - get the function associated with a given state
 * @s: state
 *
 * Return: the state associated with c
 */
quote_state_func quote_state_fn(quote_state_t s)
{
	switch (s)
	{
	case Q_NONE:
		return (_quote_state_none);
	case Q_WORD:
		return (_quote_state_word);
	case Q_DOUBLE:
		return (_quote_state_double);
	case Q_SINGLE:
		return (_quote_state_single);
	case Q_ESCAPE:
		return (_quote_state_escape);
	}
	return (NULL);
}


/**
 * quote_state_len - get the length of a given state
 * @str: string
 * @state: state
 *
 * Return: the state associated with c
 */
size_t quote_state_len(const char *str, quote_state_t state)
{
	return (quote_state_fn(state)(str, NULL));
}
