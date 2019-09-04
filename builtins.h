#ifndef BUILTINS_H
#define BUILTINS_H

#include <limits.h>
#include <stdlib.h>
#include <unistd.h>
#include "alias.h"
#include "env.h"
#include "error.h"
#include "info.h"
#include "string.h"
#include "types.h"

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

void load_builtins(info_t *info);

int _alias_(info_t *info);
int _cd_(info_t *info);
int _env_(info_t *info);
int _exit_(info_t *info);
int _setenv_(info_t *info);
int _unsetenv_(info_t *info);
int _help_(info_t *info);

void _alias_add(alias_t **aliases, const char *name, const char *value);
void _alias_print(alias_t *alias);

void _cd_success(info_t *info);
void _cd_error(info_t *info, char *dir);

int isnumber(char *s);

unsigned int atou(char *s);

#endif /* BUILTINS_H */
