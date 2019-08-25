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
	static info_t info = {
		NULL,
		0,
		1,
		NULL,
		0,
		NULL,
		NULL,
		EXIT_SUCCESS,
		0,
		NULL,
		NULL,
		NULL
	};
	ssize_t n_read;
	int interactive = isatty(STDIN_FILENO);

	info.pid = getpid();
	info.cwd = getcwd(NULL, 0);
	info.path = strtolist(_getenv("PATH"), ':');
	info.env = envtolist(environ);
	signal(2, _sigint);
	info.argv = argv;
	info.argc = argc;

	while (1)
	{
		if (interactive)
			write(STDERR_FILENO, "$ ", 2);

		_read(&info);

		info.tokens = tokenize(info.line);
		if (info.tokens)
			_run(&info);
		free_tokens(info.tokens);
		info.cmd_num += 1;
	}

}
