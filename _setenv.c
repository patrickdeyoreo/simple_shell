#include "shell.h"
/**
 * _setenv - sets the environment variables
 * @info: arguments passed
 * Return: int
 */

int _setenv(info_t *info)
{
	my_env_t *var;
	char *lineno;

	if (info->tokens[1] && info->tokens[2])
	{
		if (info->tokens[3])
		{
			lineno = num_to_str(info->lineno);
			_perror(4, info->argv[0], lineno, info->tokens[0], "Too many arguments.");
			free(lineno);

			info->status = EXIT_FAILURE;
			return (info->status);
		}

		var = find_env_node(info->env, info->tokens[1]);
		if (var)
		{
			free(var->value);
			var->value = _strdup(info->tokens[2]);
		}
		else
		{
			add_env_node_end(&info->env, info->tokens[1], info->tokens[2]);
		}
	}

	info->status = EXIT_SUCCESS;
	return (info->status);
}
