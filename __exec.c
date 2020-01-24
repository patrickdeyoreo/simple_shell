#include "builtins.h"

/**
 * __exec - replace the running shell with a new program
 * @info: arguments passed
 * Return: int
 */
int __exec(info_t *info)
{
	char *exe, **args = info->tokens + 1, **env = NULL;

	if (!*args)
	{
		info->status = EXIT_SUCCESS;
		return (EXIT_SUCCESS);
	}
	info->tokens = args;
	args = arrdup(args);

	if (_strchr(*args, '/') == -1)
	{
		free_list(&info->path);
		info->path = str_to_list(get_dict_val(info->env, "PATH"), ':');
		exe = search_path(info, info->path);
	}
	else
	{
		exe = _strdup(*args);
	}
	--info->tokens;

	if (access(exe, X_OK) == 0)
	{
		env = dict_to_env(info->env);

		free_info(info);
		execve(exe, args, env);

		_perror_default(info, "not found", 2, "exec", *args);
		free(exe);
		free_tokens(&args);
		free_tokens(&env);
		exit(127);
	}
	_perror_default(info, "Permission denied", 2, "exec", *args);
	free(exe);
	free_tokens(&args);
	free_info(info);
	exit(126);
}
