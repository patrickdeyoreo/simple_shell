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
		if (var->val)
			write(STDOUT_FILENO, var->val, _strlen(var->val));
		write(STDOUT_FILENO, "\n", 1);
	}
	return (info->status);
}
