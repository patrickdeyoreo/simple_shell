#include "shell.h"
/**
 * 
 *
 */
int _alias(info_t *info)
{
	size_t i, j;
	char **tokens = info->tokens;
	char *alias_val;
	info->status = EXIT_SUCCESS;
	alias_t *alias;

	for (i = 1; tokens[i]; i++)
	{
		alias_val = _getenv(info->aliases, tokens[i]);
		if (_strchr(tokens[i], '=') == -1)
		{
			if (!alias_val)
			{
				_perror(3,"alias:", tokens[i], "not found");
				info->status = EXIT_FAILURE;
			}
			else
			{
				write(STDOUT_FILENO, tokens[i], _strlen(tokens[i]));
				write(STDOUT_FILENO, '=', 1);
				write(STDOUT_FILENO, alias_value, _strlen(alias_value));
				write(STDOUT_FILENO, '\n', 1);
			}
		}
		else
		{
			alias = find_env_node(info->aliases, tokens[i]);
			if (alias)
			{
				free(alias->value);
				alias->value = _strdup(alias_val);
			}
			else
			{
				tokens[i][_strchr(tokens[i], '=')] = '\0';
				add_env_node_end(tokens[i], alias_val);
			}

		}
	}
	return(info->status);
}
