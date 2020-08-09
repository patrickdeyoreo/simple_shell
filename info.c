#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "info.h"

/**
 * init_info - initialize shell info
 * @argc: the arg count
 * @argv: the arg values
 * Return: pointer to the info
 */
info_t *init_info(int argc, char **argv)
{
	static info_t info;

	info.argc = argc;
	info.argv = argv;
	info.file = NULL;
	info.fileno = STDIN_FILENO;
	info.status = EXIT_SUCCESS;
	info.line = NULL;
	info.lineno = 0;
	info.tokens = NULL;
	info.pid = getpid();
	info.cwd = getcwd(NULL, 0);
	info.exe = NULL;
	info.env = env_to_dict(environ);
	info.path = NULL;
	info.aliases = NULL;
	info.history = NULL;
	info.commands = NULL;
	if (argc > 1)
	{
		info.file = argv[1];
		info.fileno = open(info.file, O_RDONLY);
		if (info.fileno == -1)
		{
			info.file = NULL;
			info.fileno = STDIN_FILENO;
			info.status = EXIT_FAILURE;
		}
	}
	info.interactive = isatty(info.fileno);
	return (&info);
}


/**
 * free_info - free and nullify dynamically allocated info
 * @info: pointer to the info
 */
void free_info(info_t *info)
{
	free(info->line);
	info->line = NULL;
	free_tokens(&info->tokens);
	free(info->cwd);
	info->cwd = NULL;
	free(info->exe);
	info->exe = NULL;
	free_dict(&info->env);
	free_list(&info->path);
	free_dict(&info->aliases);
	free_cmdlist(&info->commands);
	_getline(-1);
}

