#include "builtins.h"

/**
  * __exit - exits from shell
  * @info: arguments passed
  * Return: int
  */
int __exit(info_t *info)
{
	char **args = info->tokens + 1;

	if (*args)
	{
		if (_isnumber(*args) && atou(*args) <= INT_MAX)
		{
			info->status = atou(*args);
		}
		else
		{
			perrorl_default(*info->argv, info->lineno, "Illegal number",
					*info->tokens, *args, NULL);
			info->status = 2;

			return (info->status);
		}
	}
	if (info->file)
		close(STDIN_FILENO);

	free_info(info);
	exit(info->status);
}
