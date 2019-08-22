#include "shell.h"

int _env(info_t *info)
{
	size_t i;

	for (i = 0; environ[i] != NULL; i++)
	{
		write(STDOUT_FILENO, environ[i], _strlen(environ[i]));
		write(STDOUT_FILENO, "\n", 1);
	}

	info->status = EXIT_SUCCESS;
	return (EXIT_SUCCESS);
}
