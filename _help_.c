#include "builtins.h"

/**
 * _help_ - show help for builtins commands
 * @info: shell info
 * Return: status
 */
int _help_(struct info *info)
{
	builtin_t *bltn;
	char **args = info->tokens + 1;

	if (*args)
	{
		info->status = EXIT_FAILURE;
		do {
			for (bltn = info->builtins; bltn->fn; ++bltn)
			{
				if (!_strcmp(*args, bltn->name))
				{
					info->status = EXIT_SUCCESS;
					write(STDOUT_FILENO, bltn->name,
						_strlen(bltn->name));
					write(STDOUT_FILENO, ": ", 2);
					write(STDOUT_FILENO, bltn->usage,
						_strlen(bltn->usage));
					write(STDOUT_FILENO, "\n", 1);
					write(STDOUT_FILENO, bltn->help,
						_strlen(bltn->help));
					write(STDOUT_FILENO, "\n", 1);
				}
			}
		} while (*(++args));

		if (info->status == EXIT_FAILURE)
			_lperror_default(info, "no help topics match",
				*info->tokens, *(args - 1), NULL);
	}
	else
	{
		info->status = EXIT_SUCCESS;
		for (bltn = info->builtins; bltn->fn; ++bltn)
		{
			write(STDOUT_FILENO, bltn->usage,
				_strlen(bltn->usage));
			write(STDOUT_FILENO, "\n", 1);
		}
	}
	return (info->status);
}
