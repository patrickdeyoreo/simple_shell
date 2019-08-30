#include "shell.h"

/**
  * expand_alias - perform a single alias expansion on the current command
  * @info: arguments passed
  *
  * Return: If expansion succeeds, return a pointer the alias name.
  * Otherwise, return NULL.
  */
char *expand_alias(info_t *info)
{
	alias_t *alias;
	char **tokens, **alias_tokens, *alias_value;

	for (alias = info->aliases; alias; alias = alias->next)
	{
		if (!_strcmp(info->tokens[0], alias->key))
		{
			tokens = info->tokens;
			alias_value = _strdup(alias->value);
			alias_tokens = tokenize(alias_value);

			info->tokens = arrjoin(alias_tokens, tokens + 1);

			free_tokens(tokens);
			free_tokens(alias_tokens);
			free(alias_value);

			return (alias->key);
		}
	}

	return (NULL);
}
