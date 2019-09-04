#ifndef BUILTINS_H
#define BUILTINS_H

#include <limits.h>
#include <stdlib.h>
#include <unistd.h>
#include "alias.h"
#include "env.h"
#include "error.h"
#include "general.h"
#include "info.h"
#include "string.h"

/**
  * struct builtin - builtin command
  * @name: name of the builtin
  * @fn: builtin function address
  * @help: help message
  */
struct builtin
{
	char *name;
	int (*fn)(info_t *);
	char *help;
};

int alias_(info_t *info);
int cd_(info_t *info);
int env_(info_t *info);
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
