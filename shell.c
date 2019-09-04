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
	info_t info;

	signal(2, _sigint);

	init_info(&info, argc, argv);

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
