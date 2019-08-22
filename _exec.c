#include "shell.h"

int _exec(info_t *info)
{
	pid_t child = fork();

	if (child == 0)
	{
		free(info->line);
		free_list(&info->path);
		execve(info->tokens[0], info->tokens, NULL);
		free_tokens(info->tokens);
		exit(EXIT_FAILURE);
	}

	if (child > 0)
		wait(&info->status);

	info->status = WEXITSTATUS(info->status);
	return (info->status);
}
