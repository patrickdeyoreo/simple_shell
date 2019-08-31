#include "shell.h"


/**
 * open_script - execute commands from a script
 * @info: shell information
 */
void open_script(info_t *info)
{
	char *cmd_num, *error;

	close(STDIN_FILENO);
	if (open(info->argv[1], O_RDONLY) == -1)
	{
		cmd_num = num_to_str(info->cmd_num);
		error = strjoin("Can't open", info->argv[1], ' ');
		_perror(3, info->argv[0], cmd_num, error);
		free(cmd_num);
		free(error);
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
		++info.cmd_num;

		if (info.interactive)
			write(STDERR_FILENO, "$ ", 2);

		_read(&info);

		if (info.line)
			info.commands = cmd_to_list(info.line);

		while (info.commands)
		{
			if (_parse(&info))
				_run(&info);
			free_tokens(info.tokens);
			remove_cmd(&info.commands, 0);
		}
		info.tokens = NULL;
	}
}
