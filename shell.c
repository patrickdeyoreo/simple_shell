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
	char **tokens = NULL;
	char *line = NULL;
	size_t len = 0;
	ssize_t n_read;
	pid_t child;
	int status = 0;

	int interactive = isatty(STDIN_FILENO);

	list_t *path = strtolist(_getenv("PATH"), ':');

	while (1)
	{
		if (interactive)
			write(STDERR_FILENO, "$ ", 2);

		n_read = getline(&line, &len, stdin);
		if (n_read < 1)
		{
			free(line);
			free_list(&path);
			write(STDOUT_FILENO, "\n", 1);

			if (n_read < 0)
				exit(EXIT_FAILURE);

			exit(WEXITSTATUS(status));
		}

		tokens = tokenize(line);
		if (tokens)
		{
			child = fork();

			if (child == 0)
			{
				free(line);
				free_list(&path);
				execve(tokens[0], tokens, NULL);
				free_tokens(tokens);
				exit(EXIT_FAILURE);
			}

			if (child > 0)
				wait(&status);

			free_tokens(tokens);
		}
	}

}
