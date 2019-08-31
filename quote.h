#ifndef QUOTE_H
#define QUOTE_H

#include <stdlib.h>
#include "ctype.h"

/**
 * enum quote_state - a quote state mnemonic
 * @NONE: In an unquoted sequence of blanks
 * @WORD: In an unquoted sequence of non-blanks
 * @DOUBLE: In double quotes
 * @SINGLE: In single quotes
 */
typedef enum quote_state
{
	NONE,
	WORD,
	DOUBLE,
	SINGLE
} quote_state_t;

quote_state_t get_quote_state(int c);
size_t quote_state_none(const char *str, quote_state_t *state);
size_t quote_state_word(const char *str, quote_state_t *state);
size_t quote_state_double(const char *str, quote_state_t *state);
size_t quote_state_single(const char *str, quote_state_t *state);

#endif /* QUOTE_H */
