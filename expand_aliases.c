#include "shell.h"

/**
  * expand_aliases - perform recursive alias expansion on the current command
  * @info: arguments passed
  *
  * Return: If expansion succeeds, return a pointer t to the otherwise 0
  */
void expand_aliases(alias_t *aliases, char ***tokptr)
{
	char *name;

	do {
		name = expand_alias(aliases, tokptr);
	} while (name && **tokptr && _strcmp(name, **tokptr));
}


/**
  * expand_alias - perform a single alias expansion on the current command
  * @info: arguments passed
  *
  * Return: If expansion succeeds, return a pointer the alias name.
  * Otherwise, return NULL.
  */
char *expand_alias(alias_t *aliases, char ***tokptr)
{
	char **alias_tokens, **tokens = *tokptr;

	if (!*tokens)
		return (NULL);

	while (aliases)
	{
		if (!_strcmp(*tokens, aliases->key))
		{
			alias_tokens = tokenize(aliases->val);
			*tokptr = arrjoin(alias_tokens, tokens + 1);

			free_tokens(&tokens);
			free_tokens(&alias_tokens);

			return (aliases->key);
		}
		aliases = aliases->next;
	}
	return (NULL);
}
