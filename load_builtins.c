#include "builtins.h"

/**
 * load_builtins - load a static builtin array
 * @info: the info struct to load the builtins into
 */
void load_builtins(info_t *info)
{
	static builtin_t builtins[] = {
		{"alias", alias_, ALIAS_USAGE, ALIAS_HELP},
		{"cd", cd_, CD_USAGE, CD_HELP},
		{"env", env_, ENV_USAGE, ENV_HELP},
		{"exec", exec_, EXEC_USAGE, EXEC_HELP},
		{"exit", exit_, EXIT_USAGE, EXIT_HELP},
		{"help", help_, HELP_USAGE, HELP_HELP},
		{"setenv", setenv_, SETENV_USAGE, SETENV_HELP},
		{"unsetenv", unsetenv_, UNSETENV_USAGE, UNSETENV_HELP},
		{0}
	};
	info->builtins = builtins;
}
