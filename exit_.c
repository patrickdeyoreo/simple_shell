#include "shell.h"


int exit_(info_t *info)
{	
	if (info->tokens[1])
	{
		if (_isnumber(info->tokens[1]) != 0)
			info->status = _atoi(info->tokens[1]);
		else
		{
			write(STDERR_FILENO, "exit: Illegal number: ", 22);
			write(STDERR_FILENO, info->tokens[1], _strlen(info->tokens[1]));
			write(STDERR_FILENO, "\n", 1);
			info->status = 2;
			return (info->status);
		}
	}
	free(info->line);
	free_list(&info->path);
	free(info->cwd);
	free(info->full_cmd);
	free_tokens(info->tokens);

	exit(info->status);
	return (0);
}
