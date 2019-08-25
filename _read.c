#include "shell.h"

int _read(info_t *info)
{
	ssize_t n_read = getline(&info->line, &info->len, stdin);

	if (n_read < 1)
	{
		free(info->line);
		free_list(&info->path);
		free(info->cwd);
		free_env(&info->env);
		free(info->full_cmd);

		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "\n", 1);

		exit(info->status);
	}
	info->status = EXIT_SUCCESS;
	return (info->status);
}
