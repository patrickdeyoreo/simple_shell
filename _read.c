#include "shell.h"
/**
  * _read - reads the command line passed
  * @info: arguments passed
  * Return: int
  */
int _read(info_t *info)
{
	ssize_t n_read = _getline(&info->line, &info->len, STDIN_FILENO);

	if (n_read < 1)
	{
		free_info(info);

		if (info->interactive)
			write(STDOUT_FILENO, "\n", 1);

		exit(info->status);
	}
	return (EXIT_SUCCESS);
}
