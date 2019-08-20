#include "header.h"
size_t _getline(char **lineptr, size_t *nptr, int fd)
{
	static char buffer[BUFSIZE];
	size_t len = 0;
	ssize_t n_read;
	char *tmp;

	if (fd < 0 || !lineptr || !nptr)
		return (-1);
	while (n_read = read(fd, buffer, BUFSIZE))
	{
		if (n_read == -1)
		{
			free(*lineptr);
			*lineptr = NULL;
			*nptr = 0;
			return (-1);
		}
		if ((len + n_read + 1) > *nptr)
		{
			tmp = realloc(*lineptr, sizeof(char) * (len + n_read + 1));
			if (!tmp)
			{
				free(*lineptr);
				return (-1);
			}
			*lineptr = tmp;
			*nptr = len + n_read + 1;
			strncpy(*lineptr + len, buffer, n_read);
			len += n_read;
		}
	}
	(*lineptr)[len] = '\0';
	return (len);
}

