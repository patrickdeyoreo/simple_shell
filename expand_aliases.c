#include "shell.h"


/**
  * expand_aliases - perform recursive alias expansion on the current command
  * @info: arguments passed
  *
  * Return: If expansion succeeds, return a pointer t to the otherwise 0
  */
void expand_aliases(info_t *info)
{
	char *name;

	do {
		name = expand_alias(info);
	} while (name && info->tokens[0] && _strcmp(name, info->tokens[0]));
}


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
	char **tokens = info->tokens, **alias_tokens;

	if (!tokens[0])
		return (NULL);

	for (alias = info->aliases; alias; alias = alias->next)
	{
		if (!_strcmp(tokens[0], alias->key))
		{
			alias_tokens = tokenize(alias->value);

			info->tokens = arrjoin(alias_tokens, tokens + 1);

			free_tokens(tokens);
			free_tokens(alias_tokens);

			return (alias->key);
		}
	}
	return (NULL);
}
