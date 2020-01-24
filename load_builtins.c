#include "builtins.h"

/**
 * load_builtins - load an array of builtins
 *
 * Return: a NULL terminated, statically allocated array of builtins
 */
builtin_t *load_builtins(void)
{
	static builtin_t builtins[] = {
		{"alias", __alias, ALIAS_USAGE, ALIAS_HELP},
		{"cd", __cd, CD_USAGE, CD_HELP},
		{"env", __env, ENV_USAGE, ENV_HELP},
		{"exec", __exec, EXEC_USAGE, EXEC_HELP},
		{"exit", __exit, EXIT_USAGE, EXIT_HELP},
		{"help", __help, HELP_USAGE, HELP_HELP},
		{"setenv", __setenv, SETENV_USAGE, SETENV_HELP},
		{"unsetenv", __unsetenv, UNSETENV_USAGE, UNSETENV_HELP},
		{0}
	};

	return (builtins);
}
