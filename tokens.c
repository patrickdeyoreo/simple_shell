#include "parse.h"


/**
 * tokenize - split a string into words (tokens) and dequote
 * @str: the string to tokenize
 * Return: If malloc fails or if str is 0 or contains no tokens, return NULL.
 * Otherwise, return an array containing the tokens in str, terminated by NULL.
 */
char **tokenize(char *str)
{
	char **tokens, *tok;
	ssize_t count;
	quote_state_t state;

	if (!str)
		return (NULL);

	tokens = malloc(sizeof(char *) * (count_tokens(str) + 1));
	if (!tokens)
		return (NULL);

	for (count = 0; *(str += quote_state_none(str, &state)); ++count)
	{
		tok = str;
		while (*str && state != NONE)
		{
			if (state == WORD)
				str += quote_state_word(str, &state);
			else
			{
				++str;
				if (state == DOUBLE)
					str += quote_state_double(str, &state);
				else
					str += quote_state_single(str, &state);
				if (*str)
					++str;
			}
		}
		if (*str)
			*str++ = '\0';
		tokens[count] = dequote(tok);
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
	size_t count;
	quote_state_t state;

	for (count = 0; *(str += quote_state_none(str, &state)); ++count)
	{
		while (*str && state != NONE)
		{
			if (state == WORD)
				str += quote_state_word(str, &state);
			else
			{
				++str;
				if (state == DOUBLE)
					str += quote_state_double(str, &state);
				else
					str += quote_state_single(str, &state);
				if (*str)
					++str;
			}
		}
	}
	return (count);
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
