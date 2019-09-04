#include "builtins.h"

/**
  * env_ - displays environment
  * @info: arguments passed
  * Return: int
  */
int env_(info_t *info)
{
	env_t *var;

	info->status = EXIT_SUCCESS;

	for (var = info->env; var; var = var->next)
	{
		if (var->key)
			write(STDOUT_FILENO, var->key, _strlen(var->key));
		write(STDOUT_FILENO, "=", 1);
		if (var->value)
			write(STDOUT_FILENO, var->value, _strlen(var->value));
		write(STDOUT_FILENO, "\n", 1);
	}
	return (info->status);
}
