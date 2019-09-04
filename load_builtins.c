#include "builtins.h"

/**
 * load_builtins - load a static builtin array
 * @info: the info struct to load the builtins into
 */
void load_builtins(info_t *info)
{
	static builtin_t builtins[] = {
		{"alias", _alias_, "alias [NAME[='VALUE'] ...]",
			"    Define or display aliases.\n\n"
				"    Without arguments, a list of aliases is "
				"printed in a reusable form.\n"
				"    With arguments an alias is defined for "
				"each NAME whose VALUE is given.\n"
				"    For each NAME whose VALUE is not given, the "
				"corresponding alias is printed if it exists."
		},
		{"cd", _cd_, "cd [DIR]",
			"    Change the current directory to DIR.\n\n"
				"    If DIR is ommitted, the directory is "
				"changed to the value of HOME.\n"
				"    If DIR is -, the directory is changed to "
				"the previous working directory."
		},
		{"env", _env_, "env",
			"    Print the environment."
		},
		{"exit", _exit_, "exit [STATUS]",
			"    Exit the shell with a status of STATUS.\n\n"
				"    If STATUS is omitted, the exit status is "
				"that of the previous command."
		},
		{"help", _help_, "help [BUILTIN]",
			"    Display information about builtin commands.\n\n"
				"    If BUILTIN is omitted, display a list of "
				"the available builtins."
		},
		{"setenv", _setenv_, "setenv NAME VALUE",
			"    Set the environment variable NAME to VALUE."
		},
		{"unsetenv", _unsetenv_, "unsetenv NAME",
			"    Remove the NAME from the environment."
		},
		{NULL, NULL, NULL, NULL}
	};
	info->builtins = builtins;
}
