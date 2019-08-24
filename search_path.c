#include "shell.h"

char *search_path(info_t *info, list_t *path)
{
	char *s;
	struct stat st;

	while (path)
	{
		if (*path->str == '\0')
			s = strjoin(info->cwd, info->tokens[0], '/');
		else
			s = strjoin(path->str, info->tokens[0], '/');
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
