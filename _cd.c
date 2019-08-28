#include "shell.h"
/**
 * _cd - changes the directory
 * @info: arguments passed
 * Return: int
 */
int _cd(info_t *info)
{
	char **tokens = info->tokens;
	char *setenv_tokens[] = { "setenv", "OLDPWD", NULL, NULL };
	char *dir;

	info->tokens = setenv_tokens;
	setenv_tokens[2] = info->cwd;

	if (tokens[1])
	{
		dir = _getenv(info->env, "OLDPWD");
		if (_strcmp(tokens[1], "-") != 0)
			info->status = chdir(tokens[1]);
		else if (dir)
			info->status = chdir(dir);
		else
			info->status = chdir(".");
	}
	else
	{
		dir = _getenv(info->env, "HOME");
		if (dir)
			info->status = chdir(dir);
	}
	if (info->status < 0)
	{
		perror(info->argv[0]);
		info->status = EXIT_FAILURE;
	}
	else
	{
		_setenv(info);
		free(info->cwd);
		info->cwd = getcwd(NULL, 0);
		setenv_tokens[1] = "PWD";
		setenv_tokens[2] = info->cwd;
		_setenv(info);
		info->status = EXIT_SUCCESS;
	}

	info->tokens = tokens;
	return (info->status);
}
