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

	while (input(&info))
	{
		parse(&info);
		while ((info.tokens = pop_cmd(&(info.commands))))
		{
			execute(&info);
			free_tokens(&(info.tokens));
		}
	}
	if (info.interactive)
		write(STDOUT_FILENO, "\n", 1);

	if (info.script)
		close(STDIN_FILENO);

	free_info(&info);
	exit(info.status);
}
