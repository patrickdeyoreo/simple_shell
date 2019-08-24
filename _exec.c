#include "shell.h"

int _exec(info_t *info)
{
	pid_t child = fork();

	if (child == 0)
	{
		free(info->line);
		free_list(&info->path);
		free(info->cwd);
		execve(info->full_cmd, info->tokens, environ);
		perror(info->argv[0]);
		free(info->full_cmd);
		free_tokens(info->tokens);
		exit(EXIT_FAILURE);
	}

	if (child > 0)
		wait(&info->status);

	free(info->full_cmd);
	info->full_cmd = NULL;

	info->status = WEXITSTATUS(info->status);
	return (info->status);
}
