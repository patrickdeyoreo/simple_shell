#include "builtins.h"

/**
 * _alias_ - create and display aliases
 * @info: shell info struct
 *
 * Return: status
 */
int _alias_(info_t *info)
{
	alias_t *alias;
	char *name, **args = info->tokens + 1;
	ssize_t name_len;

	info->status = EXIT_SUCCESS;
	if (*args)
	{
		do {
			name_len = _strchr(*args, '=');
			if (name_len == -1)
			{
				alias = find_env_node(info->aliases, *args);
				if (alias)
				{
					_alias_print(alias);
				}
				else
				{
					_lperror("not found", *info->tokens,
						*args, NULL);
					info->status = EXIT_FAILURE;
				}
			}
			else
			{
				name = _strndup(*args, name_len);
				_alias_add(&info->aliases, name,
					*args + name_len + 1);
				free(name);
			}
		} while (*(++args));
	}
	else
	{
		for (alias = info->aliases; alias; alias = alias->next)
			_alias_print(alias);
	}
	return (info->status);
}


/**
 * _alias_add - add an alias to a list of aliases
 * @aliases: a pointer to a list of aliases
 * @name: the name of the alias
 * @value: the value of the alias
 */
void _alias_add(alias_t **aliases, const char *name, const char *value)
{
	alias_t *alias = find_env_node(*aliases, name);

	if (alias)
	{
		free(alias->value);
		alias->value = _strdup(value);
		return;
	}
	add_env_node_end(aliases, name, value);
}


/**
 * _alias_print - print an alias
 * @alias: the alias to print
 */
void _alias_print(alias_t *alias)
{
	write(STDOUT_FILENO, alias->key, _strlen(alias->key));
	write(STDOUT_FILENO, "='", 2);
	write(STDOUT_FILENO, alias->value, _strlen(alias->value));
	write(STDOUT_FILENO, "'\n", 2);
}
