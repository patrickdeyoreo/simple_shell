#include "shell.h"

int _read(info_t *info)
{
	ssize_t n_read = getline(&info->line, &info->len, stdin);
	if (n_read < 1)
	{
		free(info->line);
		free_list(&info->path);
		write(STDOUT_FILENO, "\n", 1);

		if (n_read < 0)
			exit(EXIT_FAILURE);

		exit(info->status);
	}
	info->status = EXIT_SUCCESS;
	return (EXIT_SUCCESS);
}
