#include "shell.h"


/**
 * _isspace - check if a character is whitespace
 * @c: the character to check
 *
 * Return: If c is a whitespace character, return 1.
 * If not, return 0.
 */
int _isspace(int c)
{
	return (c == ' ' || (c >= 0x09 && c <= 0x0d));
}


/**
 * _memcpy - copy a memory area
 * @dest: a pointer to the start of the target area
 * @src: a pointer to the start of the source area
 * @n: the number of bytes to copy
 *
 * Description: This function copies n bytes from the memory area at src
 * to the memory area at dest. These memory areas must not overlap.
 *
 * Return: a pointer to dest
 */
char *_memcpy(char *dest, const char *src, size_t n)
{
	char *pos = dest;

	while (n--)
		*pos++ = *src++;

	return (dest);
}


/**
 * count_tokens - count the words in a string
 * @str: the string to evaluate
 *
 * Return: If str is NULL, return -1.
 * Otherwise, return the number of words in str.
 */
size_t count_tokens(const char *str)
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
 */
void free_tokens(char **tokens)
{
	char **current;

	if (!tokens)
		return;

	current = tokens;
	while (*current)
		free(*current++);
	free(tokens);
}


/**
 * strtow - split a string into words (tokens)
 * @str: the string to tokenize
 *
 * Return: If malloc fails or if str is NULL or contains no tokens, return NULL.
 * Otherwise, return an array containing the tokens in str, terminated by NULL.
 */
char **tokenize(const char *str)
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

		tokens[tok_count][tok_len] = '\0';
		_memcpy(tokens[tok_count], str, tok_len);

		str += tok_len;
	}
	tokens[tok_count] = NULL;

	return (tokens);
}
