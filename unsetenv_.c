#include "builtins.h"

/**
  * unsetenv_ - unsets the environment variable
  * @info: arguments passed
  * Return: status
  */
int unsetenv_(info_t *info)
{
	char **args = info->tokens + 1;

	if (*args)
	{
		do {
			del_dict_node(&info->env, *args);
		} while (*(++args));
		info->status = EXIT_SUCCESS;
	}
	else
	{
		_lperror_default(info, "Too few arguments.",
			*info->tokens, NULL);
		info->status = EXIT_FAILURE;
	}
	return (info->status);
}
