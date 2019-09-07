#ifndef BUILTINS_H
#define BUILTINS_H

#include <limits.h>
#include <stdlib.h>
#include <unistd.h>
#include "alias.h"
#include "env.h"
#include "error.h"
#include "info.h"
#include "path.h"
#include "string.h"
#include "types.h"

#define ALIAS_USAGE "alias [NAME[=VALUE] ...]"
#define ALIAS_HELP \
	"Define or display aliases.\n\0"\
	"Without arguments, a list of aliases is printed.\0"\
	"With arguments, an alias is defined for each NAME=VALUE pair.\0"\
	"For each NAME without a VALUE, the corresponding alias is printed.\0"\
	"When expanded, a trailing space in VALUE causes expansion of the next word."\
	"\0\0"

#define CD_USAGE "cd [DIR]"
#define CD_HELP \
	"Change the current directory to DIR.\n\0"\
	"If DIR is ommitted, the value of the variable HOME is used instead.\0"\
	"If DIR is -, the directory is changed to the previous working directory."\
	"\0\0"

#define ENV_USAGE "env"
#define ENV_HELP \
	"Print the environment."\
	"\0\0"

#define EXEC_USAGE "exec COMMAND [ARGUMENTS ...]"
#define EXEC_HELP \
	"Replace the shell with the given command.\n\0"\
	"COMMAND is executed, replacing the shell with the specified program.\0"\
	"ARGUMENTS become the arguments to COMMAND.\0"\
	"If the command cannot be executed, the shell exits."\
	"\0\0"

#define EXIT_USAGE "exit [STATUS]"
#define EXIT_HELP \
	"Exit the shell with a status of STATUS.\n\0"\
	"If STATUS is omitted, the exit status is that of the previous command."\
	"\0\0"


#define HELP_USAGE "help [BUILTIN]"
#define HELP_HELP \
	"Display information about builtin commands.\n\0"\
	"If BUILTIN is omitted, a list of available builtins is printed."\
	"\0\0"

#define SETENV_USAGE "setenv NAME [VALUE]"
#define SETENV_HELP \
	"Set the environment variable NAME to VALUE.\n\0"\
	"If NAME is omitted, print the current environment.\0"\
	"If VALUE is omitted, set the variable NAME to the null string."\
	"\0\0"

#define UNSETENV_USAGE "unsetenv NAME"
#define UNSETENV_HELP \
	"Remove the variable NAME from the environment."\
	"\0\0"

/**
 * struct builtin - builtin command
 * @name: name of the builtin
 * @fn: builtin function address
 * @usage: usage information
 * @help: help text
 */
struct builtin
{
	char *name;
	int (*fn)(info_t *);
	const char *usage;
	const char *help;
};

void init_builtins(info_t *info);

int alias_(info_t *info);
int cd_(info_t *info);
int env_(info_t *info);
int exec_(info_t *info);
int exit_(info_t *info);
int setenv_(info_t *info);
int unsetenv_(info_t *info);
int help_(info_t *info);

void alias_add(alias_t **aliases, const char *name, const char *value);
void alias_print(alias_t *alias);

void cd_success(info_t *info);
void cd_error(info_t *info, char *dir);

int isnumber(char *s);

unsigned int atou(char *s);

#endif /* BUILTINS_H */
