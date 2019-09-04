#include "error.h"

/**
  * _perror - print a formatted message to standard error
  * @msg: error message
  * @n: number of context strings
  * @...: list of context strings
  */
void _perror(const char *msg, size_t n, ...)
{
	const char *str;
	va_list strings;

	va_start(strings, n);
	while (n--)
	{
		str = va_arg(strings, char *);
		if (str)
			write(STDERR_FILENO, str, _strlen(str));
		write(STDERR_FILENO, ": ", 2);
	}
	va_end(strings);

	if (msg)
		write(STDERR_FILENO, msg, _strlen(msg));
	write(STDERR_FILENO, "\n", 1);
}


/**
  * _perror_default - print a formatted message to standard error
  * @info: shell information
  * @msg: error message
  * @n: number of context strings
  * @...: list of context strings
  */
void _perror_default(info_t *info, const char *msg, size_t n, ...)
{
	const char *str;
	va_list strings;
	char *lineno = num_to_str(info->lineno);

	if (*info->argv)
		write(STDERR_FILENO, *info->argv, _strlen(*info->argv));
	write(STDERR_FILENO, ": ", 2);

	if (lineno)
		write(STDERR_FILENO, lineno, _strlen(lineno));
	write(STDERR_FILENO, ": ", 2);

	va_start(strings, n);
	while (n--)
	{
		str = va_arg(strings, char *);
		if (str)
			write(STDERR_FILENO, str, _strlen(str));
		write(STDERR_FILENO, ": ", 2);
	}
	va_end(strings);

	if (msg)
		write(STDERR_FILENO, msg, _strlen(msg));
	write(STDERR_FILENO, "\n", 1);

	free(lineno);
}


/**
  * _lperror - print a formatted message to standard error
  * @msg: error message
  * @...: NULL-terminated list of strings to prepend (context)
  */
void _lperror(const char *msg, ...)
{
	const char *str;
	va_list context;

	va_start(context, msg);
	while ((str = va_arg(context, char *)))
	{
		write(STDERR_FILENO, str, _strlen(str));
		write(STDERR_FILENO, ": ", 2);
	}
	va_end(context);

	if (msg)
		write(STDERR_FILENO, msg, _strlen(msg));
	write(STDERR_FILENO, "\n", 1);
}


/**
  * _lperror_default - print a formatted message to standard error
  * @info: shell information
  * @msg: error message
  * @...: NULL-terminated list of strings to prepend (context)
  */
void _lperror_default(info_t *info, const char *msg, ...)
{
	const char *str;
	va_list context;
	char *lineno = num_to_str(info->lineno);

	if (*info->argv)
		write(STDERR_FILENO, *info->argv, _strlen(*info->argv));
	write(STDERR_FILENO, ": ", 2);

	if (lineno)
		write(STDERR_FILENO, lineno, _strlen(lineno));
	write(STDERR_FILENO, ": ", 2);

	va_start(context, msg);
	while ((str = va_arg(context, char *)))
	{
		write(STDERR_FILENO, str, _strlen(str));
		write(STDERR_FILENO, ": ", 2);
	}
	va_end(context);

	if (msg)
		write(STDERR_FILENO, msg, _strlen(msg));
	write(STDERR_FILENO, "\n", 1);

	free(lineno);
}
