#include "shell.h"


/**
 * open_script - execute cmds from a script
 * @info: shell information
 */
void open_script(info_t *info)
{
	char *lineno, *error;

	close(STDIN_FILENO);

	if (open(info->argv[1], O_RDONLY) == -1)
	{
		lineno = num_to_str(info->lineno);
		error = strjoin("Can't open", info->argv[1], ' ');
		_perror(3, info->argv[0], lineno, error);
		free(lineno);
		free(error);
		free_info(info);
		exit(127);
	}
	info->interactive = isatty(STDIN_FILENO);
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

	init_info(&info, argc, argv, ops);

	if (argc > 1)
		open_script(&info);

	while (1)
	{
		_read(&info);

		info.cmds = cmd_to_list(info.line);
		while (info.cmds)
		{
			if (_parse(&info))
				_run(&info);
			free_tokens(info.tokens);
			remove_cmd(&info.cmds, 0);
		}
		info.tokens = NULL;

		free(info.line);
		info.line = NULL;
		info.len = 0;
	}
}
