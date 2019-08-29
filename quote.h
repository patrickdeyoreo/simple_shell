#ifndef QUOTE_H
#define QUOTE_H

#include "shell.h"

/**
 * quote_state_t - a quote state mnemonic
 */
typedef enum quote_state
{
	NONE, WORD, DOUBLE, SINGLE
} quote_state_t;

char *dequote(const char *str);
size_t dequote_len(const char *str);

quote_state_t get_quote_state(int c);

size_t quote_state_none(const char *str, quote_state_t *state);
size_t quote_state_word(const char *str, quote_state_t *state);
size_t quote_state_double(const char *str, quote_state_t *state);
size_t quote_state_single(const char *str, quote_state_t *state);

#endif /* QUOTE_H */
