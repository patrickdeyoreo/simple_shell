#include "shell.h"
/**
  * _cd - changes the directory
  * @info: arguments passed
  * @Return: int
  */
int _cd(info_t *info)
{
	char *dir;
	char *setenv_tokens[] = { "setenv", "OLDPWD", info->cwd, NULL };
	char **tokens = info->tokens;

	if (tokens[1])
	{
		info->tokens = setenv_tokens;
		if (_strcmp(tokens[1], "-") == 0)
		{
			dir = _getenv(info->env, "OLDPWD");
			if (!dir)
			{
				chdir(".");
				_setenv(info);
			}
			else
			{
				chdir(dir);
				_setenv(info);
				free(info->cwd);
				info->cwd = getcwd(NULL, 0);
			}
		}
		else
		{
			chdir(tokens[1]);
			_setenv(info);
			free(info->cwd);
			info->cwd = getcwd(NULL, 0);
		}
	}
	else
	{
		dir = _getenv(info->env, "HOME");
		if (dir)
		{
			chdir(dir);
			_setenv(info);
			free(info->cwd);
			info->cwd = getcwd(NULL, 0);
		}
	}
	setenv_tokens[1] = "PWD";
	setenv_tokens[2] = info->cwd;
	_setenv(info);
	info->tokens = tokens;
	info->status = EXIT_SUCCESS;

	return (info->status);

}
