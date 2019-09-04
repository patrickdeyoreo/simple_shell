#include "shell.h"

/**
  * search_path - searches for the directory with the executable program
  * @info: argument passed
  * @path: argument passed
  * Return: pointer to directory string
  */
char *search_path(info_t *info, list_t *path)
{
	char *pathname, *command = info->tokens[0];
	struct stat sb;

	while (path)
	{
		if (*path->str == '\0')
			pathname = strjoin(".", command, '/', NULL);
		else
			pathname = strjoin(path->str, command, '/', NULL);
		if (stat(pathname, &sb) == 0)
		{
			if ((sb.st_mode & S_IFMT) != S_IFDIR)
				return (pathname);
		}
		free(pathname);
		path = path->next;
	}
	return (NULL);
}
