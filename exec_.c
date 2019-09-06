#include "builtins.h"

/**
  * exec_ - replace the running shell with a new program
  * @info: arguments passed
  * Return: int
  */
int exec_(info_t *info)
{
	char *exe, **argv, **env;

	if (!info->tokens[1])
	{
		info->status = EXIT_SUCCESS;
		return (EXIT_SUCCESS);
	}
	argv = arrdup(++info->tokens);
	if (_strchr(*argv, '/') == -1)
	{
		free_list(&info->path);
		info->path = str_to_list(get_dict_val(info->env, "PATH"), ':');
		exe = search_path(info, info->path);
	}
	else
	{
		exe = _strdup(*info->tokens);
	}
	--info->tokens;

	env = dict_to_env(info->env);

	free_info(info);

	execve(exe, argv, env);

	_lperror_default(info, "not found", "exec", *argv, NULL);

	free(exe);
	free_tokens(&argv);
	free_tokens(&env);

	exit(127);
}

