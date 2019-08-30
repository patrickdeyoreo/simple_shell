#include "shell.h"

/**
  * expand_aliases - perform recursive alias expansion on the current command
  * @info: arguments passed
  *
  * Return: If expansion succeeds, return a pointer t to the otherwise 0
  */
void expand_aliases(info_t *info)
{
	char *name;

	while ((name = expand_alias(info)) && _strcmp(name, info->tokens[0]))
		;
}
