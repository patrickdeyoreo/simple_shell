#include "shell.h"

/**
  * get_cmd - read a command
  * @info: shell information
  *
  * Return: line size
  */
int get_cmd(info_t *info)
{
	char **lineptr = &info->line, *line = NULL, *temp;
	size_t *nptr = &info->linesize;

	if (info->interactive)
		write(STDERR_FILENO, "$ ", 2);

	while (++info->lineno, _get_cmd(info, lineptr, nptr) & (Q_DOUBLE | Q_SINGLE))
	{
		temp = line;
		line = strjoin(line, *lineptr, '\0', NULL);
		free(temp);

		if (info->interactive)
			write(STDERR_FILENO, "> ", 2);
	}
	temp = *lineptr;
	*lineptr = strjoin(line, *lineptr, '\0', nptr);
	free(temp);
	free(line);

	return (*nptr);
}


/**
 * _get_cmd - read a single line
 * @info: shell information
 * @lineptr: line buffer
 * @nptr: line buffer size
 *
 * Return: ending quote state
 */
int _get_cmd(info_t *info, char **lineptr, size_t *nptr)
{
	static quote_state_t state = Q_NONE;
	size_t index = 0;
	ssize_t n_read = _getline(lineptr, nptr, STDIN_FILENO);

	if (n_read < 1)
	{
		free_info(info);
		free(*lineptr);

		if (info->interactive)
			write(STDOUT_FILENO, "\n", 1);

		exit(info->status);
	}

	while ((*lineptr)[index] && (*lineptr)[index] != '\n')
	{
		index += quote_state_fn(state)((*lineptr) + index, NULL);

		if (!(*lineptr)[index] || (*lineptr)[index] == '\n')
			break;
		if (state & (Q_DOUBLE | Q_SINGLE))
			++index;

		state = quote_state((*lineptr)[index]);

		if (!(*lineptr)[index] || (*lineptr)[index] == '\n')
			break;
		if (state & (Q_DOUBLE | Q_SINGLE))
			++index;
	}
	return (state);
}
