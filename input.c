#include "shell.h"

/**
 * input - get input
 * @info: shell information
 *
 * Return: line size
 */
int input(info_t *info)
{
	char **lineptr = &info->line, *line = NULL, *tmp;
	size_t *nptr = &info->linesize;

	if (info->interactive)
		write(STDERR_FILENO, "$ ", 2);

	while (++info->lineno,
		_input(lineptr, nptr) & (Q_DOUBLE | Q_SINGLE | Q_ESCAPE))
	{
		line = strjoin(tmp = line, *lineptr, '\0', NULL);
		free(tmp);

		if (info->interactive)
			write(STDERR_FILENO, "> ", 2);
	}
	if (line)
	{
		*lineptr = strjoin(line, tmp = *lineptr, '\0', nptr);
		free(tmp);
		free(line);
	}
	return (*nptr);
}


/**
 * _input - read a single line
 * @lineptr: line buffer
 * @nptr: line buffer size
 *
 * Return: ending quote state
 */
quote_state_t _input(char **lineptr, size_t *nptr)
{
	static quote_state_t state = Q_NONE;
	size_t index = 0;
	ssize_t n_read = _getline(lineptr, nptr, STDIN_FILENO);

	if (n_read < 1)
	{
		free(*lineptr);
		*lineptr = NULL;
		*nptr = 0;
		return (Q_NONE);
	}

	switch (state & (Q_DOUBLE | Q_SINGLE))
	{
	case Q_DOUBLE:
	case Q_SINGLE:
		do {
			index += quote_state_len(*lineptr + index, state);
			if (!(*lineptr)[index])
				continue;
			if (state & (Q_DOUBLE | Q_SINGLE))
				++index;
	case 0:
			state = quote_state((*lineptr)[index]);
			if (state & (Q_DOUBLE | Q_SINGLE | Q_ESCAPE))
				++index;
		} while ((*lineptr)[index]);
	}
	return (state);
}
