#include "builtins.h"

/**
 * load_builtins - load a static builtin array
 * @info: the info struct to load the builtins into
 */
void load_builtins(info_t *info)
{
	static builtin_t builtins[] = {
		{"alias", alias_, "alias [NAME[='VALUE'] ...]", ALIAS_HELP},
		{"cd", cd_, "cd [DIR]", CD_HELP},
		{"env", env_, "env", ENV_HELP},
		{"exit", exit_, "exit [STATUS]", EXIT_HELP},
		{"help", help_, "help [BUILTIN]", HELP_HELP},
		{"setenv", setenv_, "setenv NAME VALUE", SETENV_HELP},
		{"unsetenv", unsetenv_, "unsetenv NAME", UNSETENV_HELP},
		{NULL, NULL, NULL, NULL}
	};
	info->builtins = builtins;
}
