#ifndef QUOTE_H
#define QUOTE_H

#include <stdlib.h>
#include "ctype.h"
#include "string.h"

/**
 * enum quote_state - a quote state mnemonic
 * @NONE: In an unquoted sequence of blanks
 * @WORD: In an unquoted sequence of non-blanks
 * @DOUBLE: In double quotes
 * @SINGLE: In single quotes
 */
typedef enum quote_state
{
	NONE   = 0,
	WORD   = 1,
	DOUBLE = 2,
	SINGLE = 4
} quote_state_t;

quote_state_t get_quote_state(int c);
size_t (*get_quote_state_fn(quote_state_t s))(const char *, quote_state_t *);
size_t quote_state_none(const char *str, quote_state_t *state);
size_t quote_state_word(const char *str, quote_state_t *state);
size_t quote_state_double(const char *str, quote_state_t *state);
size_t quote_state_single(const char *str, quote_state_t *state);

char *dequote(const char *str);
size_t dequote_len(const char *str);

#endif /* QUOTE_H */
