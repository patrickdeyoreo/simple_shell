#include "shell.h"

/**
  * expand_alias - perform alias expansion on the current command
  * @info: arguments passed
  */
void expand_alias(info_t *info)
{
	alias_t *alias;
	char **tokens, **alias_tokens, *alias_value;
	size_t i;

	for (alias = info->aliases; alias; alias = alias->next)
	{
		if (!_strcmp(info->tokens[0], alias->key))
		{
			tokens = info->tokens;
			alias_value = _strdup(alias->value);
			alias_tokens = tokenize(alias_value);

			info->tokens = arrjoin(alias_tokens, tokens + 1);

			for (i = 0; tokens[i]; ++i)
				free(tokens[i]);
			free(tokens);
			for (i = 0; alias_tokens[i]; ++i)
				free(alias_tokens[i]);
			free(alias_tokens);
			free(alias_value);

			return;
		}
	}
}
