#include "info.h"

/**
 * init_info - initialize shell info
 * @info: a pointer to the info to initialize
 * @argc: the arg count
 * @argv: the arg values
 */
void init_info(info_t *info, int argc, char **argv)
{
	info->interactive = isatty(STDIN_FILENO);
	info->argc = argc;
	info->argv = argv;
	info->line = NULL;
	info->linesize = 0;
	info->lineno = 0;
	info->tokens = NULL;
	info->status = EXIT_SUCCESS;
	info->pid = getpid();
	info->cwd = getcwd(NULL, 0);
	info->exe = NULL;
	info->env = env_to_dict(environ);
	info->path = NULL;
	info->aliases = NULL;
	info->commands = NULL;
	init_builtins(info);
}


/**
 * free_info - free and nullify dynamically allocated shell info
 * @info: a pointer to the info to free
 */
void free_info(info_t *info)
{
	free(info->line);
	info->line = NULL;
	info->linesize = 0;
	free_tokens(&info->tokens);
	free(info->cwd);
	info->cwd = NULL;
	free(info->exe);
	info->exe = NULL;
	free_dict(&info->env);
	free_list(&info->path);
	free_dict(&info->aliases);
	free_cmd_list(&info->commands);
}

