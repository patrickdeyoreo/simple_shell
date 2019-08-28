#ifndef QUOTE_H
#define QUOTE_H

#include "shell.h"

/**
 * enum quote_state - a quote state mnemonic
 */
enum quote_state
{
	NONE, WORD, DOUBLE, SINGLE
};

char *dequote(const char *str);
size_t dequote_len(const char *str);

enum quote_state get_quote_state(int c);

size_t quote_state_none(const char *str, enum quote_state *state);
size_t quote_state_word(const char *str, enum quote_state *state);
size_t quote_state_double(const char *str, enum quote_state *state);
size_t quote_state_single(const char *str, enum quote_state *state);

static size_t (*quote_state_fn[])(const char *, enum quote_state *) = {
	quote_state_none,
	quote_state_word,
	quote_state_double,
	quote_state_single
};

#endif /* QUOTE_H */
