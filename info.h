#ifndef INFO_H
#define INFO_H

#include <stdlib.h>
#include <unistd.h>
#include "alias.h"
#include "builtins.h"
#include "command.h"
#include "env.h"
#include "list.h"
#include "tokens.h"
#include "types.h"

extern char **environ;

/**
  * struct info - shell state
  * @interactive: arguments passed
  * @argc: arguments passed
  * @argv: arguments passed
  * @line: arguments passed
  * @linesize: arguments passed
  * @lineno: arguments passed
  * @tokens: arguments passed
  * @status: arguments passed
  * @pid: arguments passed
  * @cwd: arguments passed
  * @exe: arguments passed
  * @env: arguments passed
  * @path: arguments passed
  * @aliases: arguments passed
  * @builtins: arguments passed
  * @commands: arguments passed
  */
struct info
{
	int interactive;
	int argc;
	char **argv;
	char *line;
	size_t linesize;
	size_t lineno;
	char **tokens;
	int status;
	pid_t pid;
	char *cwd;
	char *exe;
	env_t *env;
	list_t *path;
	alias_t *aliases;
	builtin_t *builtins;
	cmd_list_t *commands;
};

void init_info(info_t *info, int argc, char **argv);
void free_info(info_t *info);

#endif /* INFO_H */
