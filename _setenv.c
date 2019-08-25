#include "shell.h"

int _setenv(info_t *info)
{
	my_env_t *var;
	char *value = "";
	char *cmd_num;

	if (!info->tokens[1])
		return(_env(info));

	if (info->tokens[2])
	{
		if (info->tokens[3])
		{
			cmd_num = num_to_str(info->cmd_num);
			_perror(4, info->argv[0], cmd_num, info->tokens[0], "Too many arguments.");
			free(cmd_num);
			info->status = 1;
			return (info->status);
		}
		value = info->tokens[2];
	}

	var = find_env_node(info->env, info->tokens[1]);

	if (!var)
		add_env_node_end(&info->env, info->tokens[1], value);
	else
	{
		free(var->value);
		var->value = _strdup(value);
	}
	info->status = 0;

	return (info->status);
}
