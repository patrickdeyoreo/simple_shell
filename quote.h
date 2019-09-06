#ifndef QUOTE_H
#define QUOTE_H

#include <stdlib.h>
#include "ctype.h"
#include "string.h"

/**
 * enum quote_state - a quote state mnemonic
 * @Q_NONE: In an unquoted sequence of blanks
 * @Q_WORD: In an unquoted sequence of non-blanks
 * @Q_DOUBLE: In double quotes
 * @Q_SINGLE: In single quotes
 * @Q_ESCAPE: Following a backslash
 */
typedef enum quote_state
{
	Q_NONE   = 0,
	Q_WORD   = 1,
	Q_DOUBLE = 2,
	Q_SINGLE = 4,
	Q_ESCAPE = 8
} quote_state_t;

typedef size_t (*quote_state_func)(const char *, quote_state_t *);

quote_state_t quote_state(char c);

quote_state_func quote_state_fn(quote_state_t s);

size_t quote_state_len(const char *str, quote_state_t state);

size_t _quote_state_none(const char *str, quote_state_t *state);
size_t _quote_state_word(const char *str, quote_state_t *state);
size_t _quote_state_double(const char *str, quote_state_t *state);
size_t _quote_state_single(const char *str, quote_state_t *state);
size_t _quote_state_escape(const char *str, quote_state_t *state);

int _isquote(char c);

int _isspecial_double(char c);

char *dequote(const char *str);
size_t dequote_len(const char *str);

#endif /* QUOTE_H */
