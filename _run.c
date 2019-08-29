#include "shell.h"

/**
 * arrjoin - join two arrays
 * @arr1: the first array
 * @arr2: the second array
 *
 * Return: a dynamically-allocated array of the elements from arr1 and arr2
 */
char **arrjoin(char **arr1, char **arr2)
{
	char **new_arr;
	size_t arr1_len, arr2_len, new_len;

	for (arr1_len = 0; arr1[arr1_len]; ++arr1_len)
		;
	for (arr2_len = 0; arr2[arr2_len]; ++arr2_len)
		;
	new_len = arr1_len + arr2_len;

	new_arr = malloc(sizeof(char *) * (new_len + 1));
	if (!new_arr)
		return (NULL);

	new_len = 0;
	while (*arr1)
		new_arr[new_len++] = _strdup(*arr1++);
	while (*arr2)
		new_arr[new_len++] = _strdup(*arr2++);
	new_arr[new_len] = NULL;

	return (new_arr);
}

/**
  * _run - runs the command
  * @info: arguments passed
  * Return: int
  */
int _run(info_t *info)
{
	alias_t *alias;
	char **tokens, **alias_tokens, *alias_value, *cmd_num, *error;
	size_t i;

	for (alias = info->aliases; alias; alias = alias->next)
	{
		if (!_strcmp(info->tokens[0], alias->key))
		{
			tokens = info->tokens;
			alias_value = _strdup(alias->value);
			alias_tokens = tokenize(alias_value);
			info->tokens = arrjoin(alias_tokens, tokens + 1);
			for (i = 0; alias_tokens[i]; ++i)
				free(alias_tokens[i]);
			free(alias_tokens);
			free(alias_value);
			for (i = 0; tokens[i]; ++i)
				free(tokens[i]);
			free(tokens);
			break;
		}
	}
	for (i = 0; info->ops[i].name; i++)
	{
		if (!_strcmp(info->tokens[0], info->ops[i].name))
			return ((info->ops)[i].f(info));
	}
	if (_strchr(info->tokens[0], '/') == -1)
	{
		free_list(&info->path);
		info->path = strtolist(_getenv(info->env, "PATH"), ':');
		info->full_cmd = search_path(info, info->path);
	}
	else
	{
		info->full_cmd = _strdup(info->tokens[0]);
	}

	if (info->full_cmd)
	{
		if (access(info->full_cmd, X_OK) == 0)
			return (_exec(info));
		info->status = 126;
		error = "Permission denied";
	}
	else
	{
		info->status = 127;
		error = "not found";
	}

	cmd_num = num_to_str(info->cmd_num);
	_perror(4, info->argv[0], cmd_num, info->tokens[0], error);
	free(cmd_num);

	return (info->status);
}
