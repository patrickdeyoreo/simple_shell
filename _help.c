#include "shell.h"
/**
  * _help - prints help messages
  * @info: arguments passed
  * Return: int
  */

int _help(info_t *info)
{
	size_t i, j, flag;
	char *cmd_num;

	if (info->tokens[1])
	{
		flag = 0;
		for (i = 1; info->tokens[i]; i++)
		{
			for (j = 0; ops[j].name; j++)
			{
				if (!(_strcmp(info->tokens[i], ops[j].name)))
				{
					flag = 1;
					write(STDOUT_FILENO, ops[j].help, _strlen(ops[j].help));
					write(STDOUT_FILENO, "\n", 1);
					break;
				}
			}
		}
		if (!flag)
		{
			cmd_num = num_to_str(info->cmd_num);
			_perror(5, info->argv[0], cmd_num, info->tokens[0], info->tokens[1],
					"no help topics match");
			free(cmd_num);
			info->status = EXIT_FAILURE;
			return (info->status);
		}
	}
	else
	{
		for (i = 0; ops[i].name; i++)
		{
			write(STDOUT_FILENO, ops[i].name, _strlen(ops[i].name));
			write(STDOUT_FILENO, "\n", 1);
		}
	}
	info->status = EXIT_SUCCESS;
	return (info->status);
}
