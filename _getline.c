#include "shell.h"

#ifndef BUFSIZE
#define BUFSIZE 4096
#endif

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
	static size_t pos, rem;
	ssize_t n_read, eol = -1;
	size_t len = 0;
	char *tmp;

	if (!(fd > -1 && lineptr && nptr))
		return (-1);

	if (rem > 0)
	{
		eol = _strnchr(buffer + pos, '\n', rem);
		if (eol > -1)
		{
			len = eol + 1;
			if (len >= *nptr)
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
			_memcpy(*lineptr, buffer + pos, len);
			(*lineptr)[len] = '\0';
			rem -= len;
			if (rem)
				pos += len;
			else
				pos = 0;
			return (len);
		}
	}

	len = 0;
	while ((n_read = read(fd, buffer + pos + rem, BUFSIZE - (pos + rem))))
	{
		if (n_read == -1)
		{
			free(*lineptr);
			*lineptr = NULL;
			*nptr = 0;
			return (-1);
		}

		eol = _strnchr(buffer + pos, '\n', n_read);
		if (eol > -1)
		{
			if (len + eol + 1 >= *nptr)
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
			_memcpy(*lineptr + len, buffer + pos, eol + 1);
			(*lineptr)[len + eol + 1] = '\0';
			rem = n_read - (eol + 1);
			if (rem)
				pos += eol + 1;
			else
				pos = 0;
			return (len + eol + 1);
		}

		if (len + n_read >= *nptr)
		{
			if (*lineptr)
				tmp = realloc(*lineptr, sizeof(char) * (len + n_read + 1));
			else
				tmp = malloc(sizeof(char) * (len + n_read + 1));
			if (!tmp)
			{
				free(*lineptr);
				*lineptr = NULL;
				*nptr = 0;
				return (-1);
			}
			*lineptr = tmp;
			*nptr = len + n_read + 1;
		}
		_memcpy(*lineptr + len, buffer + pos, n_read);
		(*lineptr)[len + n_read] = '\0';
		pos = 0;
		rem = 0;
		len += n_read;
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
	(*lineptr)[len] = '\004';

	return (len);
}

