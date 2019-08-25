#include "shell.h"

int _exec(info_t *info)
{
	char **env;
	pid_t child = fork();

	if (child == 0)
	{
		env = listtoenv(info->env);
		free(info->line);
		free_list(&info->path);
		free(info->cwd);
		free_env(&info->env);
		execve(info->full_cmd, info->tokens, env);
		perror(info->argv[0]);
		free(info->full_cmd);
		free_tokens(info->tokens);
		free_tokens(env);
		exit(EXIT_FAILURE);
	}

	if (child > 0)
		wait(&info->status);

	free(info->full_cmd);
	info->full_cmd = NULL;

	info->status = WEXITSTATUS(info->status);
	return (info->status);
}
