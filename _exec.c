#include "shell.h"
/**
  * _exec - executes the command
  * @info: arguments passed
  * Return: int
  */
int _exec(info_t *info)
{
	char *path, **argv, **env;
	pid_t child = fork();

	if (child == 0)
	{
		path = info->full_cmd;
		argv = info->tokens;
		env = listtoenv(info->env);

		info->full_cmd = NULL;
		info->tokens = NULL;
		free_info(info);

		execve(path, argv, env);
		perror(argv[0]);

		free(path);
		free_tokens(argv);
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
