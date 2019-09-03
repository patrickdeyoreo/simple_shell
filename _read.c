#include "shell.h"


/**
  * _read - reads the command line passed
  * @info: arguments passed
  *
  * Return: int
  */
int _read(info_t *info)
{
	char *line = NULL, *temp = NULL;
	size_t len = 0;

	if (info->interactive)
		write(STDERR_FILENO, "$ ", 2);

	while (_read_one(info, &line, &len) & (DOUBLE | SINGLE))
	{
		if (info->interactive)
			write(STDERR_FILENO, "> ", 2);

		temp = info->line;
		info->line = strjoin(info->line, line, '\0');
		info->len += len;
		free(temp);
	}
	temp = info->line;
	info->line = strjoin(info->line, line, '\0');
	info->len += len;
	free(temp);
	free(line);

	return (1);
}


/**
 * _read_one - read a single line
 * @info: shell information
 * @lineptr: line buffer
 * @nptr: line buffer size
 *
 * Return: ending quote state
 */
quote_state_t _read_one(info_t *info, char **lineptr, size_t *nptr)
{
	static quote_state_t state = NONE;
	size_t index = 0;
	ssize_t n_read = _getline(lineptr, nptr, STDIN_FILENO);

	if (n_read < 1)
	{
		free(*lineptr);

		free_info(info);

		if (info->interactive)
			write(STDOUT_FILENO, "\n", 1);

		exit(info->status);
	}

	while ((*lineptr)[index] && (*lineptr)[index] != '\n')
	{
		index += get_quote_state_fn(state)((*lineptr) + index, NULL);

		if (!(*lineptr)[index] || (*lineptr)[index] == '\n')
			break;
		if (state & (DOUBLE | SINGLE))
			++index;

		state = get_quote_state((*lineptr)[index]);

		if (!(*lineptr)[index] || (*lineptr)[index] == '\n')
			break;
		if (state & (DOUBLE | SINGLE))
			++index;
	}

	return (state);
}
