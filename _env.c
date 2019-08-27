#include "shell.h"
/**
  * _env - displays environment
  * @info: arguments passed
  * Return: int
  */

int _env(info_t *info)
{
	my_env_t *var = info->env;

	while (var)
	{
		if (var->key)
			write(STDOUT_FILENO, var->key, _strlen(var->key));
		write(STDOUT_FILENO, "=", 1);
		if (var->value)
			write(STDOUT_FILENO, var->value, _strlen(var->value));
		write(STDOUT_FILENO, "\n", 1);
		var = var->next;
	}

	info->status = EXIT_SUCCESS;
	return (info->status);
}
