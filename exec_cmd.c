#include "shell.h"

/**
  * exec_cmd - execute a command
  * @info: arguments passed
  *
  * Return: status
  */
int exec_cmd(info_t *info)
{
	builtin_t *builtin;

	for (builtin = info->builtins; builtin->name; ++builtin)
	{
		if (!_strcmp(*info->tokens, builtin->name))
			return (builtin->fn(info));
	}

	if (_strchr(*info->tokens, '/') == -1)
	{
		free_list(&info->path);
		info->path = str_to_list(_getenv(info->env, "PATH"), ':');
		info->exe = search_path(info, info->path);
	}
	else
	{
		info->exe = _strdup(*info->tokens);
	}

	if (info->exe)
	{
		if (access(info->exe, X_OK) == 0)
			return (_exec_cmd(info));

		_perror_default(info, "Permission denied", 1, *info->tokens);
		info->status = 126;
	}
	else
	{
		_perror_default(info, "not found", 1, *info->tokens);
		info->status = 127;
	}

	return (info->status);
}


/**
 * _exec_cmd - fork and exec the current command
 * @info: shell information
 *
 * Return: exit status of the child process
 */
int _exec_cmd(info_t *info)
{
	char *exe, **argv, **env;

	switch (fork())
	{
	case 0:
		exe = info->exe;
		argv = info->tokens;
		env = list_to_env(info->env);

		info->exe = NULL;
		info->tokens = NULL;
		free_info(info);

		execve(exe, argv, env);
		perror(argv[0]);

		free(exe);
		free_tokens(&argv);
		free_tokens(&env);

		exit(EXIT_FAILURE);
		break;
	case -1:
		_perror_default(info, "Cannot fork", 0);
		info->status = 2;
		break;
	default:
		wait(&info->status);
		info->status = WEXITSTATUS(info->status);
		break;
	}
	free(info->exe);
	info->exe = NULL;
	return (info->status);
}
