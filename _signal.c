#include "shell.h"

void _sigint(int signal)
{
	write(STDERR_FILENO, "\n$ ", 3);
}
