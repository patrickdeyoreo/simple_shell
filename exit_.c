#include "shell.h"
/**
  * exit_ - exits from shell
  * @info: arguments passed
  * Return: int
  */


int exit_(info_t *info)
{
	char *cmd_num;

	if (info->tokens[1])
	{
		if (_isnumber(info->tokens[1]) && _atou(info->tokens[1]) <= INT_MAX)
		{
			info->status = _atou(info->tokens[1]);
		}
		else
		{
			cmd_num = num_to_str(info->cmd_num);
			_perror(5, info->argv[0], cmd_num, info->tokens[0],
					"Illegal number", info->tokens[1]);
			free(cmd_num);
			info->status = 2;
			return (info->status);
		}
	}

	free_info(info);

	exit(info->status);
	return (0);
}
