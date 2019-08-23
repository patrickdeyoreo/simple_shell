#include "shell.h"


/**
 * main - entry point
 * @argc: the argument count
 * @argv: the argument vector
 *
 * Return: Always 0
 */
int main(int argc __attribute__((unused)), char **argv __attribute__((unused)))
{
	static info_t info = {
		NULL,
		0,
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
	signal(2, _sigint);

	while (1)
	{
		if (interactive)
			write(STDERR_FILENO, "$ ", 2);

		_read(&info);


		info.tokens = tokenize(info.line);
		if (info.tokens)
			_run(&info);
		free_tokens(info.tokens);
	}

}
