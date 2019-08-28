#include "quote.h"


enum quote_state get_quote_state(int c)
{
	if (_isspace(c))
		return (NONE);
	if (c == '"')
		return (DOUBLE);
	if (c == '\'')
		return (SINGLE);
	return (WORD);
}


size_t quote_state_none(const char *str, enum quote_state *state)
{
	size_t len = 0;

	while (_isspace(*str))
		++str, ++len;
	*state = get_quote_state(*str);
	return (len);
}


size_t quote_state_word(const char *str, enum quote_state *state)
{
	size_t len = 0;

	while (*str && !_isspace(*str) && !_isquote(*str))
		++str, ++len;
	*state = get_quote_state(*str);
	return (len);
}


size_t quote_state_double(const char *str, enum quote_state *state)
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


size_t quote_state_single(const char *str, enum quote_state *state)
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

