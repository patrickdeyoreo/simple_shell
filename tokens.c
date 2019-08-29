#include "parse.h"


/**
 * tokenize - split a string into words (tokens) and dequote
 * @str: the string to tokenize
 * Return: If malloc fails or if str is 0 or contains no tokens, return NULL.
 * Otherwise, return an array containing the tokens in str, terminated by NULL.
 */
char **tokenize(char *str)
{
	char **tokens, *next;
	size_t count;
	enum quote_state state;

	static size_t (*quote_state_fn[])(const char *, enum quote_state *) = {
		quote_state_none, quote_state_word, quote_state_double, quote_state_single
	};
	count = count_tokens(str);
	if (!count)
		return (NULL);

	tokens = malloc(sizeof(char *) * (count + 1));
	if (!tokens)
		return (NULL);
	for (count = 0; *(str += quote_state_none(str, &state)); ++count)
	{
		next = str;
		while (*str && state != NONE)
		{
			if (state == DOUBLE || state == SINGLE)
			{
				++str;
				str += quote_state_fn[state](str, &state);
				if (*str)
					++str;
			}
			if (state == WORD)
				str += quote_state_word(str, &state);
		}
		if (*str)
			*str++ = '\0';
		tokens[count] = dequote(next);
		if (!tokens[count])
			return (free_tokens(tokens));
	}
	tokens[count] = NULL;
	return (tokens);
}

/**
 * count_tokens - compute the length of a string after dequoting
 * @str: the string to evaluate
 * Return: Return the length of str after dequoting
 */
size_t count_tokens(const char *str)
{
	size_t tok_count = 0;
	enum quote_state state = NONE;

	static size_t (*quote_state_fn[])(const char *, enum quote_state *) = {
		quote_state_none, quote_state_word, quote_state_double, quote_state_single
	};
	if (!str)
		return (0);
	while (*str)
	{
		if (state == DOUBLE || state == SINGLE)
		{
			str += quote_state_fn[state](str, &state);
			if (state == DOUBLE || state == SINGLE)
				str += 2;
			else if (state == WORD)
				++str;
			else if (*str)
				++str, ++tok_count;
			else
				++tok_count;
		}
		else if (state == WORD)
		{
			str += quote_state_word(str, &state);
			if (state == DOUBLE || state == SINGLE)
				++str;
			else
				++tok_count;
		}
		else
		{
			str += quote_state_none(str, &state);
			if (state == DOUBLE || state == SINGLE)
				++str;
		}
	}
	return (tok_count);
}


/**
 * tokenize_old - split a string into words (tokens)
 * @str: the string to tokenize
 * Return: If malloc fails or if str is 0 or contains no tokens, return NULL.
 * Otherwise, return an array containing the tokens in str, terminated by NULL.
 */
char **tokenize_old(char *str)
{
	char **tokens;
	size_t tok_count, tok_len;

	tok_count = count_tokens(str);
	if (!tok_count)
		return (NULL);
	tokens = malloc(sizeof(char *) * (tok_count + 1));
	if (!tokens)
		return (NULL);

	for (tok_count = 0; *str; ++tok_count)
	{
		while (_isspace(*str))
			++str;
		if (!*str)
			break;

		tok_len = 1;
		while (str[tok_len] && !_isspace(str[tok_len]))
			++tok_len;

		tokens[tok_count] = malloc(sizeof(char) * (tok_len + 1));
		if (!tokens[tok_count])
		{
			free_tokens(tokens);
			return (NULL);
		}
		_memcpy(tokens[tok_count], str, tok_len);
		tokens[tok_count][tok_len] = '\0';

		str += tok_len;
	}
	tokens[tok_count] = NULL;

	return (tokens);
}


/**
 * count_tokens_old - count the words in a string
 * @str: the string to evaluate
 * Return: If str is NULL, return -1.
 * Otherwise, return the number of words in str.
 */
size_t count_tokens_old(const char *str)
{
	size_t tok_count;

	if (!str)
		return (0);

	for (tok_count = 0; *str; ++tok_count)
	{
		while (_isspace(*str))
			++str;
		if (!*str)
			break;
		do {
			++str;
		} while (*str && !_isspace(*str));
	}
	return (tok_count);
}


/**
 * free_tokens - free an array of strings
 * @tokens: the array to free
 * Return: pointer
 */
char **free_tokens(char **tokens)
{
	char **tok;

	if (tokens)
	{
		for (tok = tokens; *tok; ++tok)
			free(*tok);
		free(tokens);
	}
	return (NULL);
}
