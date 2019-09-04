#include "builtins.h"

/**
  * _exit_ - exits from shell
  * @info: arguments passed
  * Return: int
  */
int _exit_(info_t *info)
{
	char **args = info->tokens + 1;

	if (*args)
	{
		if (isnumber(*args) && atou(*args) <= INT_MAX)
		{
			info->status = atou(*args);
		}
		else
		{
			_lperror_default(info, *args, *info->tokens,
				"Illegal number", NULL);
			info->status = 2;
			return (info->status);
		}
	}
	free_info(info);
	exit(info->status);
	return (info->status);
}
