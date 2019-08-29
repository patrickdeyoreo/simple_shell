#include "shell.h"

/**
  * _run - runs the command
  * @info: arguments passed
  *
  * Return: status
  */
int _run(info_t *info)
{
	char *cmd_num, *error;
	size_t i;

	while (expand_alias(info))
		;
	for (i = 0; info->ops[i].name; i++)
	{
		if (!_strcmp(info->tokens[0], info->ops[i].name))
			return ((info->ops)[i].f(info));
	}
	if (_strchr(info->tokens[0], '/') == -1)
	{
		free_list(&info->path);
		info->path = strtolist(_getenv(info->env, "PATH"), ':');
		info->full_cmd = search_path(info, info->path);
	}
	else
	{
		info->full_cmd = _strdup(info->tokens[0]);
	}

	if (info->full_cmd)
	{
		if (access(info->full_cmd, X_OK) == 0)
			return (_exec(info));
		info->status = 126;
		error = "Permission denied";
	}
	else
	{
		info->status = 127;
		error = "not found";
	}

	cmd_num = num_to_str(info->cmd_num);
	_perror(4, info->argv[0], cmd_num, info->tokens[0], error);
	free(cmd_num);

	return (info->status);
}
