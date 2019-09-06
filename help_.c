#include "builtins.h"

/**
 * help_ - show help for builtins commands
 * @info: shell info
 * Return: status
 */
int help_(struct info *info)
{
	builtin_t *builtin;
	char **args = info->tokens + 1;

	if (*args)
	{
		info->status = EXIT_FAILURE;
		do {
			for (builtin = info->builtins; builtin->fn; ++builtin)
			{
				if (!_strcmp(*args, builtin->name))
				{
					info->status = EXIT_SUCCESS;
					write(STDOUT_FILENO, builtin->name,
						_strlen(builtin->name));
					write(STDOUT_FILENO, ": ", 2);
					write(STDOUT_FILENO, builtin->usage,
						_strlen(builtin->usage));
					write(STDOUT_FILENO, "\n", 1);
					write(STDOUT_FILENO, builtin->help,
						_strlen(builtin->help));
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
		for (builtin = info->builtins; builtin->fn; ++builtin)
		{
			write(STDOUT_FILENO, builtin->usage,
				_strlen(builtin->usage));
			write(STDOUT_FILENO, "\n", 1);
		}
	}
	return (info->status);
}
