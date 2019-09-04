#include "shell.h"

/**
 * parse_cmd - parse a command
 * @info: shell information
 *
 * Description: This function expands aliases, variables, and word splitting
 *
 * Return: the final number of tokens
 */
int parse_cmd(info_t *info)
{
	char **tokens, *tok;

	info->tokens = tokenize(info->commands->cmd);
	if (!info->tokens)
		return (0);

	expand_aliases(info);
	if (!info->tokens)
		return (0);

	expand_vars(info);
	if (!info->tokens)
		return (0);

	for (tokens = info->tokens, tok = *tokens; tok; tok = *(++tokens))
	{
		*tokens = dequote(tok);
		free(tok);
	}
	return (tokens - info->tokens);
}
