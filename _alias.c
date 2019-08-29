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
 * @aliases: a list of aliases to print
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
	size_t i;

	info->status = EXIT_SUCCESS;
	if (!tokens[1])
	{
		_print_aliases(info->aliases);
		return (info->status);
	}
	for (i = 1; tokens[i]; i++)
	{
		name_len = _strchr(tokens[i], '=');
		if (name_len == -1)
		{
			alias = find_env_node(info->aliases, tokens[i]);
			if (alias)
				_print_alias(alias);
			else
			{
				_perror(3, "alias", tokens[i], "not found");
				info->status = EXIT_FAILURE;
			}
		}
		else
		{
			tokens[i][name_len] = '\0';
			value = tokens[i] + name_len + 1;
			alias = find_env_node(info->aliases, tokens[i]);
			if (alias)
			{
				free(alias->value);
				alias->value = _strdup(value);
			}
			else
				add_env_node_end(&info->aliases, tokens[i], value);
			tokens[i][name_len] = '=';
		}
	}
	return(info->status);
}
