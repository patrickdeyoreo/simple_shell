#include "shell.h"

/**
 * open_script - execute commands from a script
 * @argv: the arguments to the shell
 */
void open_script(char **argv)
{
	char *error;

	close(STDIN_FILENO);
	if (open(argv[1], O_RDONLY) < 0)
	{
		error = strjoin("Can't open", argv[1], ' ');
		_perror(3, argv[0], "0", error);
		free(error);
		exit(127);
	}
}

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
	info->cmd_num = 1;
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
 * free_info - free dynamically allocated shell info
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

/**
 * main - entry point
 * @argc: the argument count
 * @argv: the argument vector
 *
 * Return: Always 0
 */
int main(int argc, char **argv)
{
	built_in_t ops[] = {
		{"alias", _alias, "Usage: alias [NAME[='VALUE'] ...]"},
		{"cd", _cd, "Usage: cd [DIRECTORY]"},
		{"env", _env, "Usage: env"},
		{"exit", exit_, "Usage: exit [STATUS]"},
		{"setenv", _setenv, "Usage: setenv VARIABLE VALUE"},
		{"unsetenv", _unsetenv, "Usage: unsetenv VARIABLE"},
		{"help", _help, "Usage: help [BUILTIN]"},
		{NULL, NULL, NULL}
	};
	info_t info;

	signal(2, _sigint);

	if (argc > 1)
		open_script(argv);

	init_info(&info, argc, argv, ops);

	while (++info.cmd_num, 1)
	{
		if (info.interactive)
			write(STDERR_FILENO, "$ ", 2);

		_read(&info);

		if (info.line)
			info.commands = cmd_to_list(info.line);

		while (info.commands)
		{
			info.tokens = tokenize(info.commands->cmd);
			if (info.tokens)
				_run(&info);
			info.tokens = free_tokens(info.tokens);
			remove_cmd(&info.commands, 0);
		}
	}
}
