#include "shell.h"


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
	_setenv(info);

	free(info->cwd);
	info->cwd = getcwd(NULL, 0);

	setenv_tokens[1] = "PWD";
	setenv_tokens[2] = info->cwd;
	_setenv(info);

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
	char *lineno, *error;

	lineno = num_to_str(info->lineno);
	error = strjoin("can't cd to", dir, ' ');

	_perror(4, info->argv[0], lineno, info->tokens[0], error);

	free(lineno);
	free(error);

	info->status = 2;
}


/**
 * _cd - changes the directory
 * @info: arguments passed
 *
 * Return: int
 */
int _cd(info_t *info)
{
	char *dir;

	if (info->tokens[1])
	{
		if (_strcmp(info->tokens[1], "-"))
		{
			dir = info->tokens[1];
			info->status = chdir(dir);
		}
		else
		{
			dir = _getenv(info->env, "OLDPWD");
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
		dir = _getenv(info->env, "HOME");
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
