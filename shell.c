#include "shell.h"


/**
 * main - entry point
 * @argc: the argument count
 * @argv: the argument vector
 *
 * Return: Always 0
 */
int main(int argc, char **argv)
{
	cmd_list_t *command_list;
	built_in_t ops[] = {
		{"cd", _cd, "Usage: cd [DIRECTORY]"},
		{"env", _env, "Usage: env"},
		{"exit", exit_, "Usage: exit"},
		{"setenv", _setenv, "Usage: setenv VARIABLE VALUE"},
		{"unsetenv", _unsetenv, "Usage: unsetenv VARIABLE"},
		{"help", _help, "Usage: help [BUILTIN]"},
		{NULL, NULL, NULL}
	};
	info_t info = {
		NULL,
		0,
		1,
		NULL,
		0,
		NULL,
		NULL,
		EXIT_SUCCESS,
		0,
		0,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL
	};
	info.interactive = isatty(STDIN_FILENO);
	info.pid = getpid();
	info.cwd = getcwd(NULL, 0);
	info.env = envtolist(environ);
	signal(2, _sigint);
	info.argv = argv;
	info.argc = argc;
	info.ops = ops;


	while (1)
	{
		if (info.interactive)
			write(STDERR_FILENO, "$ ", 2);
		_read(&info);
		command_list = cmd_to_list(info.line);
		while (command_list)
		{
			info.tokens = tokenize(command_list->cmd);
			if (info.tokens)
				_run(&info);
			free_tokens(info.tokens);
			remove_cmd(&command_list, 0);
		}
		info.cmd_num += 1;
	}
}
