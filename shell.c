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
 * init_info - initialize an info_t struct
 * @info: a pointer to the struct to initialize
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

	if (argc > 1)
		open_script(argv);

	init_info(&info, argc, argv, ops);
	signal(2, _sigint);
	while (1)
	{
		if (info.interactive)
			write(STDERR_FILENO, "$ ", 2);
		_read(&info);
		info.commands = cmd_to_list(info.line);
		while (info.commands)
		{
			info.tokens = tokenize(info.commands->cmd);
			if (info.tokens)
				_run(&info);
			free_tokens(info.tokens);
			remove_cmd(&info.commands, 0);
		}
		info.cmd_num += 1;
	}
}
