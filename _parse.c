#include "shell.h"

int _parse(info_t *info)
{
	char *tok;
	size_t i;

	info->tokens = tokenize(info->commands->cmd);
	if (!info->tokens)
		return (0);

	expand_aliases(info);
	if (!info->tokens)
		return (0);

	/*
	expand_vars(info);
	if (!info->tokens)
		return (0);
	*/
	for (i = 0, tok = info->tokens[0]; tok; tok = info->tokens[++i])
	{
		info->tokens[i] = dequote(tok);
		free(tok);
	}

	return (i);
}
