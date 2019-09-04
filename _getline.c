#include "getline.h"

/**
 * _getline - get a line
 *
 * @line: pointer to the line buffer
 * @n: pointer to the size of the *line
 * @fd: file descriptor to read from
 *
 * Return: number of characters read
 */
ssize_t _getline(char **line, size_t *n, int fd)
{
	static buf_t buf;
	ssize_t n_read, len = 0;

	if (!buf.r_pos)
		buf.r_pos = buf.w_pos = buf.buffer;

	if (fd < 0 || !line || !n)
		return (-1);

	if (_getline_one(&buf, &len, line, n))
		return (len);

	while ((n_read = read(fd, buf.w_pos, buf.buffer + BUFSIZE - buf.w_pos)))
	{
		if (n_read == -1)
		{
			_getline_free_line(line, n);
			return (-1);
		}

		buf.w_pos += n_read;

		if (_getline_one(&buf, &len, line, n))
			return (len);

		if (_getline_full(&buf, &len, line, n) == -1)
			return (-1);
	}
	if (!*line)
	{
		*line = malloc(sizeof(char));
		if (!*line)
		{
			*n = 0;
			return (-1);
		}
		*n = 1;
	}
	(*line)[len] = '\0';
	return (len);
}


/**
 * _getline_one - get a line from the buffer
 * @buf: pointer to the buffer structure to read from
 * @len: pointer to the current length of the line
 * @line: pointer to the line buffer
 * @n: pointer to the size of the line buffer
 *
 * Return: If memory allocation fails, return -1. If a line is not found,
 * return 0. Otherwise, return the total length of the line.
 */
ssize_t _getline_one(buf_t *buf, ssize_t *len, char **line, size_t *n)
{
	char *new;
	ssize_t eol = _strnchr(buf->r_pos, '\n', buf->w_pos - buf->r_pos);

	if (eol == -1)
		return (0);

	if (*n < (size_t) *len + eol + 2)
	{
		if (*line)
			new = realloc(*line, sizeof(char) * (*len + eol + 2));
		else
			new = malloc(sizeof(char) * (*len + eol + 2));

		if (!new)
		{
			_getline_free_line(line, n);
			*len = (-1);
			return (-1);
		}
		*line = new;
		*n = *len + eol + 2;
	}
	_memcpy(*line + *len, buf->r_pos, eol + 1);
	(*line)[*len + eol + 1] = '\0';

	*len += eol + 1;

	if (buf->r_pos + eol + 1 < buf->w_pos)
		buf->r_pos += eol + 1;
	else
		buf->r_pos = buf->w_pos = buf->buffer;

	return (*len);
}


/**
 * _getline_full - copy the whole buffer
 * @buf: pointer to the buffer structure to read from
 * @len: pointer to the current length of the line
 * @line: pointer to the line buffer
 * @n: pointer to the size of the line buffer
 *
 * Return: If memory allocation fails, return -1. Otherwise, return the total
 * length of the line.
 */
ssize_t _getline_full(buf_t *buf, ssize_t *len, char **line, size_t *n)
{
	char *new;

	if (*n <= (size_t) *len + (buf->w_pos - buf->r_pos))
	{
		if (*line)
			new = realloc(*line, sizeof(char) * (*len + buf->w_pos - buf->r_pos + 1));
		else
			new = malloc(sizeof(char) * (*len + buf->w_pos - buf->r_pos + 1));

		if (!new)
		{
			_getline_free_line(line, n);
			*len = (-1);
			return (-1);
		}
		*line = new;
		*n = *len + buf->w_pos - buf->r_pos + 1;
	}
	_memcpy(*line + *len, buf->r_pos, buf->w_pos - buf->r_pos);
	(*line)[*len + buf->w_pos - buf->r_pos] = '\0';

	*len += buf->w_pos - buf->r_pos;

	buf->r_pos = buf->w_pos = buf->buffer;

	return (*len);
}


/**
 * _getline_free_line - free & nullify the line buffer
 * @line: pointer to the line buffer
 * @n: pointer to the size of the line buffer
 */
void _getline_free_line(char **line, size_t *n)
{
	free(*line);
	*line = NULL;
	*n = 0;
}
