#include "builtins.h"

/**
 * __help - show help for builtins commands
 * @info: shell info
 * Return: status
 */
int __help(struct info *info)
{
	builtin_t *b;
	char * const *args = info->tokens + 1;
	const char *help;
	size_t len;

	if (!*args)
	{
		info->status = EXIT_SUCCESS;
		for (b = info->builtins; b->fn; ++b)
		{
			write(STDOUT_FILENO, b->usage, _strlen(b->usage));
			write(STDOUT_FILENO, "\n", 1);
		}
		return (info->status);
	}
	info->status = EXIT_FAILURE;
	do {
		for (b = info->builtins; b->fn; ++b)
		{
			if (!_strcmp(*args, b->name))
			{
				info->status = EXIT_SUCCESS;
				write(STDOUT_FILENO, b->name, _strlen(b->name));
				write(STDOUT_FILENO, ": ", 2);
				write(STDOUT_FILENO, b->usage, _strlen(b->usage));
				write(STDOUT_FILENO, "\n", 1);
				help = b->help;
				while ((len = _strlen(help)))
				{
					write(STDOUT_FILENO, "    ", 4);
					write(STDOUT_FILENO, help, len);
					write(STDOUT_FILENO, "\n", 1);
					help += len + 1;
				}
			}
		}
	} while (*(++args));
	if (info->status == EXIT_FAILURE)
		_lperror_default(info, "no topics match", *info->tokens, args[-1], NULL);
	return (info->status);
}
