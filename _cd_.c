#include "builtins.h"

/**
 * _cd_ - changes the directory
 * @info: arguments passed
 *
 * Return: int
 */
int _cd_(info_t *info)
{
	char *dir, **args = info->tokens + 1;

	if (*args)
	{
		if (_strcmp(*args, "-"))
		{
			dir = *args;
			info->status = chdir(dir);
		}
		else
		{
			dir = get_dict_val(info->env, "OLDPWD");
			if (!dir)
				dir = info->cwd;

			info->status = chdir(dir);
			if (!info->status)
			{
				write(STDOUT_FILENO, dir, _strlen(dir));
				write(STDOUT_FILENO, "\n", 1);
			}
		}
	}
	else
	{
		dir = get_dict_val(info->env, "HOME");
		if (dir)
			info->status = chdir(dir);
		else
			info->status = 0;
	}

	if (info->status == -1)
		_cd_error(info, dir);
	else
		_cd_success(info);

	return (info->status);
}


/**
 * _cd_success - update the environment upon success
 * @info: shell info
 */
void _cd_success(info_t *info)
{
	char **tokens = info->tokens;
	char *setenv_tokens[] = { "setenv", NULL, NULL, NULL };

	info->tokens = setenv_tokens;

	setenv_tokens[1] = "OLDPWD";
	setenv_tokens[2] = info->cwd;

	_setenv_(info);

	free(info->cwd);
	info->cwd = getcwd(NULL, 0);

	setenv_tokens[1] = "PWD";
	setenv_tokens[2] = info->cwd;

	_setenv_(info);

	info->tokens = tokens;

	info->status = EXIT_SUCCESS;
}


/**
 * _cd_error - print an error upon failure to change directory
 * @info: shell info
 * @dir: directory
 */
void _cd_error(info_t *info, char *dir)
{
	char *error = strjoin("can't cd to", dir, ' ', NULL);

	_lperror_default(info, error, *info->tokens, NULL);

	info->status = 2;

	free(error);
}
