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
	static size_t n_rem;
	ssize_t n_read, eol = -1;
	size_t len = 0;
	char *tmp;

	if (fd < 0 || !lineptr || !nptr)
		return (-1);

	if (n_rem)
	{
		eol = _strnchr(r_pos, '\n', n_rem);
		if (eol > -1)
		{
			len = eol + 1;
			if (*nptr <= len)
			{
				if (*lineptr)
					tmp = realloc(*lineptr, sizeof(char) * (len + 1));
				else
					tmp = malloc(sizeof(char) * (len + 1));
				if (!tmp)
				{
					free(*lineptr);
					*lineptr = NULL;
					*nptr = 0;
					return (-1);
				}
				*lineptr = tmp;
				*nptr = len + 1;
			}
			(*lineptr)[len] = '\0';
			_memcpy(*lineptr, r_pos, len);

			n_rem -= len;
			if (n_rem)
				r_pos += len;
			else
			{
				r_pos = buffer;
				w_pos = buffer;
			}
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

		n_rem += n_read;
		w_pos += n_read;

		eol = _strnchr(r_pos, '\n', n_rem);
		if (eol > -1)
		{
			if (*nptr <= len + eol + 1)
			{
				if (*lineptr)
					tmp = realloc(*lineptr, sizeof(char) * (len + eol + 2));
				else
					tmp = malloc(sizeof(char) * (len + eol + 2));
				if (!tmp)
				{
					free(*lineptr);
					*lineptr = NULL;
					*nptr = 0;
					return (-1);
				}
				*lineptr = tmp;
				*nptr = len + eol + 2;
			}
			(*lineptr)[len + eol + 1] = '\0';
			_memcpy(*lineptr + len, r_pos, eol + 1);

			n_rem -= eol + 1;
			if (n_rem)
				r_pos += (eol + 1);
			else
			{
				r_pos = buffer;
				w_pos = buffer;
			}
			return (len + eol + 1);
		}

		if (*nptr <= len + n_rem)
		{
			if (*lineptr)
				tmp = realloc(*lineptr, sizeof(char) * (len + n_rem + 1));
			else
				tmp = malloc(sizeof(char) * (len + n_rem + 1));
			if (!tmp)
			{
				free(*lineptr);
				*lineptr = NULL;
				*nptr = 0;
				return (-1);
			}
			*lineptr = tmp;
			*nptr = len + n_rem + 1;
		}
		(*lineptr)[len + n_rem] = '\0';
		_memcpy(*lineptr + len, r_pos, n_rem);

		len += n_rem;
		n_rem = 0;
		r_pos = buffer;
		w_pos = buffer;
	}

	if (!*lineptr)
	{
		tmp = malloc(sizeof(char));
		if (!tmp)
		{
			*nptr = 0;
			return (-1);
		}
		*lineptr = tmp;
		*nptr = 1;
	}
	(*lineptr)[len] = *r_pos;

	return (len);
}

