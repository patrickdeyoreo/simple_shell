#include "shell.h"


/**
 * init_info - initialize shell info
 * @info: a pointer to the info to initialize
 * @argc: the arg count
 * @argv: the arg values
 * @ops: array of built-ins
 */
void init_info(info_t *info, int argc, char **argv, built_in_t *ops)
{
	info->argv = argv;
	info->argc = argc;
	info->cmd_num = 0;
	info->line = NULL;
	info->len = 0;
	info->tokens = NULL;
	info->env = envtolist(environ);
	info->status = EXIT_SUCCESS;
	info->interactive = isatty(STDIN_FILENO);
	info->pid = getpid();
	info->cwd = getcwd(NULL, 0);
	info->path = NULL;
	info->full_cmd = NULL;
	info->ops = ops;
	info->commands = NULL;
	info->aliases = NULL;
}


/**
 * free_info - free & nullify dynamically allocated shell info
 * @info: a pointer to the info to free
 */
void free_info(info_t *info)
{
	free(info->line);
	free_tokens(info->tokens);
	free_env(&info->env);
	free(info->cwd);
	free_list(&info->path);
	free(info->full_cmd);
	free_cmd_list(&info->commands);
	free_env(&info->aliases);
}

