#include "shell.h"


/** getenv - get a string from the environment
 */
char *_getenv(const char *name)
{
	char **env = environ;
	ssize_t pos;

	if (!(name && env))
		return (NULL);

	while (*env)
	{
		pos = _strchr(*env, '=');
		if (!_strncmp(*env, name, pos))
			return (*env + pos + 1);
		++env;
	}

	return (NULL);
}
