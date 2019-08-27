#include "shell.h"
/**
  * _run - runs the command
  * @info: arguments passed
  * Return: int
  */

int _run(info_t *info)
{
	ssize_t i;
	char *cmd_num;

	for (i = 0; ops[i].name; i++)
	{
		if (!_strcmp(info->tokens[0], ops[i].name))
			return (ops[i].f(info));
	}
	if (_strchr(info->tokens[0], '/') == -1)
	{
		free_list(&info->path);
		info->path = strtolist(_getenv(info->env, "PATH"), ':');
		info->full_cmd = search_path(info, info->path);
	}
	else
		info->full_cmd = _strdup(info->tokens[0]);
	if (info->full_cmd)
		return (_exec(info));

	cmd_num = num_to_str(info->cmd_num);
	_perror(4, info->argv[0], cmd_num, info->tokens[0], "not found");
	free(cmd_num);
	return (-1);
}
