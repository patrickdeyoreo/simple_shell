#include "shell.h"

#define BUFSIZE 8192

/**
 * _getline - get a line
 *
 * @lineptr: pointer to the line buffer
 * @nptr: pointer to the size of the *lineptr
 * @fd: file descriptor to read from
 *
 * Return: number of characters read
 */
ssize_t _getline(char **lineptr, size_t *nptr, int fd)
{
	static char buffer[BUFSIZE];
	static char *r_pos = buffer, *w_pos = buffer;
	ssize_t n_read, eol = -1;
	size_t len = 0;
	char *new;

	if (fd < 0 || !lineptr || !nptr)
		return (-1);

	if (w_pos - r_pos)
	{
		eol = _strnchr(r_pos, '\n', w_pos - r_pos);
		if (eol > -1)
		{
			len = eol + 1;
			if (*nptr <= len)
			{
				if (*lineptr)
					new = realloc(*lineptr, sizeof(char) * (len + 1));
				else
					new = malloc(sizeof(char) * (len + 1));
				if (!new)
				{
					free(*lineptr);
					*lineptr = NULL;
					*nptr = 0;
					return (-1);
				}
				*lineptr = new;
				*nptr = len + 1;
			}
			(*lineptr)[len] = '\0';
			_memcpy(*lineptr, r_pos, len);

			if (r_pos + len < w_pos)
				r_pos += len;
			else
				r_pos = w_pos = buffer;

			return (len);
		}
	}

	while ((n_read = read(fd, w_pos, buffer + BUFSIZE - w_pos)))
	{
		if (n_read == -1)
		{
			free(*lineptr);
			*lineptr = NULL;
			*nptr = 0;
			return (-1);
		}

		w_pos += n_read;

		eol = _strnchr(r_pos, '\n', w_pos - r_pos);
		if (eol > -1)
		{
			if (*nptr <= len + eol + 1)
			{
				if (*lineptr)
					new = realloc(*lineptr, sizeof(char) * (len + eol + 2));
				else
					new = malloc(sizeof(char) * (len + eol + 2));
				if (!new)
				{
					free(*lineptr);
					*lineptr = NULL;
					*nptr = 0;
					return (-1);
				}
				*lineptr = new;
				*nptr = len + eol + 2;
			}
			(*lineptr)[len + eol + 1] = '\0';
			_memcpy(*lineptr + len, r_pos, eol + 1);

			if (r_pos + eol + 1 < w_pos)
				r_pos += eol + 1;
			else
				r_pos = w_pos = buffer;

			return (len + eol + 1);
		}

		if (*nptr <= len + (w_pos - r_pos))
		{
			if (*lineptr)
				new = realloc(*lineptr, sizeof(char) * (len + w_pos - r_pos + 1));
			else
				new = malloc(sizeof(char) * (len + w_pos - r_pos + 1));
			if (!new)
			{
				free(*lineptr);
				*lineptr = NULL;
				*nptr = 0;
				return (-1);
			}
			*lineptr = new;
			*nptr = len + w_pos - r_pos + 1;
		}
		(*lineptr)[len + w_pos - r_pos] = '\0';
		_memcpy(*lineptr + len, r_pos, w_pos - r_pos);

		len += w_pos - r_pos;
		r_pos = w_pos = buffer;
	}

	if (!*lineptr)
	{
		new = malloc(sizeof(char));
		if (!new)
		{
			*nptr = 0;
			return (-1);
		}
		*lineptr = new;
		*nptr = 1;
	}
	(*lineptr)[len] = '\0';

	return (len);
}

