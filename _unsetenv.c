#include "shell.h"
/**
  * _unsetenv - unsets the environment variable
  * @info: arguments passed
  * Return: status
  */

int _unsetenv(info_t *info)
{
	char *cmd_num;
	size_t i;

	if (!info->tokens[1])
	{
		cmd_num = num_to_str(info->cmd_num);
		_perror(4, info->argv[0], cmd_num, info->tokens[0], "Too few arguments.");
		free(cmd_num);
		info->status = 1;
		return (info->status);
	}
	for (i = 1; info->tokens[i]; i++)
		del_env_node(&info->env, info->tokens[i]);
	info->status = 0;
	return (info->status);
}
