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
	"  Define or display aliases.\n\n"\
	"  Without arguments, a list of aliases is printed.\n"\
	"  With arguments, an alias is defined for each NAME=VALUE pair.\n"\
	"  For each NAME without a VALUE, the corresponding alias is printed.\n"\
	"  Upon expansion, a trailing space in VALUE causes expansion of the next word."

#define CD_USAGE "cd [DIR]"
#define CD_HELP \
	"  Change the current directory to DIR.\n\n"\
	"  If DIR is ommitted, the value of the variable HOME is used instead.\n"\
	"  If DIR is -, the directory is changed to the previous working directory."

#define ENV_USAGE "env"
#define ENV_HELP \
	"  Print the environment."

#define EXEC_USAGE "exec COMMAND [ARGUMENTS ...]"
#define EXEC_HELP \
	"  Replace the shell with the given command.\n\n"\
	"  COMMAND is executed, replacing the shell with the specified program.\n"\
	"  ARGUMENTS become the arguments to COMMAND.\n"\
	"  If the command cannot be executed, the shell exits."

#define EXIT_USAGE "exit [STATUS]"
#define EXIT_HELP \
	"  Exit the shell with a status of STATUS.\n\n"\
	"  If STATUS is omitted, the exit status is that of the previous command."

#define HELP_USAGE "help [BUILTIN]"
#define HELP_HELP \
	"  Display information about builtin commands.\n\n"\
	"  If BUILTIN is omitted, a list of available builtins is printed."

#define SETENV_USAGE "setenv NAME VALUE"
#define SETENV_HELP \
	"  Set the environment variable NAME to VALUE."

#define UNSETENV_USAGE "unsetenv NAME"
#define UNSETENV_HELP \
	"  Remove the variable NAME from the environment."

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
	char *usage;
	char *help;
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
