#include "shell.h"
/**
  * _read - reads the command line passed
  * @info: arguments passed
  * Return: int
  */
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

		if (info->interactive)
			write(STDOUT_FILENO, "\n", 1);

		exit(info->status);
	}
	return (EXIT_SUCCESS);
}
