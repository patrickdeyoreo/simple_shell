#include "shell.h"

char *search_path(char *cmd, list_t *path)
{
	char *s;
	struct stat st;
	while (path)
	{
		s = strjoin(path->str, cmd, '/');
		if (stat(s, &st) == 0)
		{
			if ((st.st_mode & S_IFMT) != S_IFDIR)
				return (s);
		}
		path = path->next;
		free(s);
	}
	return (NULL);
}
