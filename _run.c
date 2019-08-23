#include "shell.h"

int _run(info_t *info)
{
	ssize_t i;

	for (i = 0; ops[i].name; i++)
	{
		if (!_strcmp(info->tokens[0], ops[i].name))
			return (ops[i].f(info));
	}
	if (_strchr(info->tokens[0], '/') == -1)
		info->full_cmd = search_path(info->tokens[0], info->path);
	else
		info->full_cmd = _strdup(info->tokens[0]);
	if (info->full_cmd)
		return (_exec(info));
	
	return (-1);
}
