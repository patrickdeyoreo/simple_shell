#include "shell.h"
/**
  * _sigint - reprompts
  * @signal: signal passed
  */

void _sigint(int signal)
{
	write(STDERR_FILENO, "\n$ ", 3);
}
