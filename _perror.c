#include "shell.h"

void _perror(size_t argc, ...)
{
	va_list messages;
	char *str;

	va_start(messages, argc);
	while (argc--)
	{
		str = va_arg(messages, char*);
		if (!str)
			str = "";
		write(STDERR_FILENO, str, _strlen(str));
		if (argc)
			write(STDERR_FILENO, ": ", 2);
	}
	write(STDERR_FILENO, "\n", 1);
	va_end(messages);
}
