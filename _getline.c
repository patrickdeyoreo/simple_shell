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
	static char *pos = buffer, *end = buffer;
	ssize_t n_read, eol = -1;
	size_t len = 0;
	char *tmp;

	if (!(fd > -1 && lineptr && nptr))
		return (-1);

	if (end - pos > 0)
	{
		eol = _strnchr(pos, '\n', end - pos);
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
			_memcpy(*lineptr, pos, len);
			(*lineptr)[len] = '\0';
			pos += len;
			if (pos >= end)
			{
				pos = buffer;
				end = buffer;
			}
			return (len);
		}
	}

	len = 0;
	while ((n_read = read(fd, end, buffer + BUFSIZE - end)))
	{
		if (n_read == -1)
		{
			free(*lineptr);
			*lineptr = NULL;
			*nptr = 0;
			return (-1);
		}

		end += n_read;

		eol = _strnchr(pos, '\n', n_read);
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
			_memcpy(*lineptr + len, pos, eol + 1);
			(*lineptr)[len + eol + 1] = '\0';
			pos += (eol + 1);
			if (pos >= end)
			{
				pos = buffer;
				end = buffer;
			}
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
		_memcpy(*lineptr + len, pos, end - pos);
		(*lineptr)[len + n_read] = '\0';
		len += n_read;
		pos = buffer;
		end = buffer;
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

