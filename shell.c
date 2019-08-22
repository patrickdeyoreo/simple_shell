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
		NULL
	};
	ssize_t n_read;
	int interactive = isatty(STDIN_FILENO);

	info.pid = getpid();
	info.path = strtolist(_getenv("PATH"), ':');
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
