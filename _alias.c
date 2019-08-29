#include "shell.h"

/**
 * _print_alias - print an alias
 * @alias: the alias to print
 */
void _print_alias(alias_t *alias)
{
	write(STDOUT_FILENO, alias->key, _strlen(alias->key));
	write(STDOUT_FILENO, "='", 2);
	write(STDOUT_FILENO, alias->value, _strlen(alias->value));
	write(STDOUT_FILENO, "'\n", 2);
}

/**
 * _print_aliases - print all aliases
 * @alias: a list of aliases to print
 */
void _print_aliases(alias_t *alias)
{
	while (alias)
	{
		_print_alias(alias);
		alias = alias->next;
	}
}
/**
 * _alias - create and display aliases
 * @info: shell info struct
 *
 * Return: success or failure
 */
int _alias(info_t *info)
{
	alias_t *alias;
	char *value, **tokens = info->tokens;
	ssize_t name_len;

	info->status = EXIT_SUCCESS;
	if (!tokens[1])
	{
		_print_aliases(info->aliases);
		return (info->status);
	}
	while (*(++tokens))
	{
		name_len = _strchr((*tokens), '=');
		if (name_len == -1)
		{
			alias = find_env_node(info->aliases, (*tokens));
			if (alias)
				_print_alias(alias);
			else
			{
				_perror(3, "alias", (*tokens), "not found");
				info->status = EXIT_FAILURE;
			}
		}
		else
		{
			(*tokens)[name_len] = '\0';
			value = (*tokens) + name_len + 1;
			alias = find_env_node(info->aliases, (*tokens));
			if (alias)
			{
				free(alias->value);
				alias->value = _strdup(value);
			}
			else
				add_env_node_end(&info->aliases, (*tokens), value);
			(*tokens)[name_len] = '=';
		}
	}
	return (info->status);
}
