#include "shell.h"

int _isnumber(char *s)
{
	while (*s)
	{
		if (_isdigit(*s) == 0)
			return (0);
		s++;
	}
	return (1);
}
