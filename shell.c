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
	builtin_t builtins[] = {
		{"alias", alias_, "Usage: alias [NAME[='VALUE'] ...]"},
		{"cd", cd_, "Usage: cd [DIRECTORY]"},
		{"env", env_, "Usage: env"},
		{"exit", exit_, "Usage: exit [STATUS]"},
		{"help", help_, "Usage: help [BUILTIN]"},
		{"setenv", setenv_, "Usage: setenv VARIABLE VALUE"},
		{"unsetenv", unsetenv_, "Usage: unsetenv VARIABLE"},
		{NULL, NULL, NULL}
	};
	info_t info;

	signal(2, _sigint);

	init_info(&info, argc, argv, builtins);

	if (argc > 1)
		open_script(&info);

	while (1)
	{
		get_cmd(&info);

		info.commands = cmd_to_list(info.line);
		while (info.commands)
		{
			if (parse_cmd(&info))
				exec_cmd(&info);

			free_tokens(&info.tokens);
			remove_cmd(&info.commands, 0);
		}
	}
}
