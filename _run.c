#include "shell.h"

int _run(info_t *info)
{
	ssize_t i;
	char *executable = NULL;

	for (i = 0; ops[i].name; i++)
	{
		if (!_strcmp(info->tokens[0], ops[i].name))
			return (ops[i].f(info));
	}
	/*
	executable = search_path(info->tokens[0], info->path);
	*/
	if (executable)
	{
		free(info->tokens[0]);
		info->tokens[0] = executable;
		return (_exec(info));
	}
	
	return (-1);
}
