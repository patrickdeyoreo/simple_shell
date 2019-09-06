#include "builtins.h"

/**
 * setenv_ - sets the environment variables
 * @info: arguments passed
 *
 * Return: status
 */
int setenv_(info_t *info)
{
	env_t *var;
	char **args = info->tokens + 1;

	info->status = EXIT_SUCCESS;

	if (args[0] && args[1])
	{
		if (args[2])
		{
			_lperror_default(info, "Too many arguments.",
				*info->tokens, NULL);
			info->status = EXIT_FAILURE;
		}
		else
		{
			var = get_dict_node(info->env, args[0]);
			if (var)
			{
				free(var->val);
				var->val = _strdup(args[1]);
			}
			else
			{
				add_dict_node_end(&info->env, args[0], args[1]);
			}
		}
	}
	return (info->status);
}
