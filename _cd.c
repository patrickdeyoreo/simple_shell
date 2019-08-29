#include "shell.h"

/**
 * _cd_error - print an error upon failure to change directory
 * @info: shell info
 * @dir: directory name
 */
void _cd_error(info_t *info, char *dir)
{
	char *cmd_num, *error;

	cmd_num = num_to_str(info->cmd_num);
	error = strjoin("can't cd to", dir, ' ');
	_perror(4, info->argv[0], cmd_num, "cd", error);
	free(cmd_num);
	free(error);
	info->status = 2;
}

/**
 * _cd_success - update the environment upon success
 * @info: shell info
 * @setenv_tokens: tokens to set the environment
 */
void _cd_success(info_t *info, char **setenv_tokens)
{
	_setenv(info);
	free(info->cwd);
	info->cwd = getcwd(NULL, 0);
	setenv_tokens[1] = "PWD";
	setenv_tokens[2] = info->cwd;
	_setenv(info);
	info->status = EXIT_SUCCESS;
}

/**
 * _cd - changes the directory
 * @info: arguments passed
 *
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
		{
			dir = tokens[1];
			info->status = chdir(dir);
		}
		else
		{	if (!dir)
				dir = info->cwd;
			info->status = chdir(dir);
			write(STDOUT_FILENO, dir, _strlen(dir));
			write(STDOUT_FILENO, "\n", 1);
		}
	}
	else
	{
		dir = _getenv(info->env, "HOME");
		if (dir)
			info->status = chdir(dir);
	}
	if (info->status < 0)
		_cd_error(info, dir);
	else
		_cd_success(info, setenv_tokens);

	info->tokens = tokens;
	return (info->status);
}
