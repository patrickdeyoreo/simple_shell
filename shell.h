#ifndef SHELL_H
#define SHELL_H

#include <limits.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>
#include <errno.h>
#include <fcntl.h>
#include "ctype.h"
#include "getline.h"
#include "list.h"
#include "parse.h"
#include "quote.h"
#include "string.h"

extern char **environ;

/**
  * struct my_env - singly linked list
  * @key: variable name
  * @value: value of variable
  * @next: pointer to the next node
  */
typedef struct my_env
{
	char *key;
	char *value;
	struct my_env *next;
} my_env_t;

typedef my_env_t alias_t;

/**
  * struct info - shell state
  * @argv: arguments passed
  * @argc: arguments passed
  * @cmd_num: arguments passed
  * @line: arguments passed
  * @len: arguments passed
  * @tokens: arguments passed
  * @env: arguments passed
  * @status: arguments passed
  * @interactive: arguments passed
  * @pid: arguments passed
  * @cwd: arguments passed
  * @path: arguments passed
  * @full_cmd: arguments passed
  * @ops: arguments passed
  * @cmds: arguments passed
  * @aliases: arguments passed
  */
typedef struct info
{
	char **argv;
	int argc;
	size_t cmd_num;
	char *line;
	size_t len;
	char **tokens;
	my_env_t *env;
	int status;
	int interactive;
	pid_t pid;
	char *cwd;
	struct list *path;
	char *full_cmd;
	struct built_in *ops;
	struct cmd_list *cmds;
	alias_t *aliases;
} info_t;

/**
  * struct built_in - built-in command
  * @name: arguments passed
  * @f: function
  * @help: arguments passed
  */
typedef struct built_in
{
	char *name;
	int (*f)(info_t *);
	char *help;
} built_in_t;

int _alias(info_t *info);
int _cd(info_t *info);
int _env(info_t *info);
int exit_(info_t *info);
int _setenv(info_t *info);
int _unsetenv(info_t *info);
int _help(info_t *info);

void _sigint(int signal);

void init_info(info_t *info, int argc, char **argv, built_in_t *ops);
void free_info(info_t *info);
void open_script(info_t *info);

int _read(info_t *info);
quote_state_t _read_one(info_t *info, char **lineptr, size_t *nptr);
int _parse(info_t *info);
int _run(info_t *info);
int _exec(info_t *info);

char *num_to_str(size_t n);
void _num_to_str(char **buf, size_t n);
void _perror(size_t argc, ...);

my_env_t *envtolist(char **env);
char **listtoenv(my_env_t *head);
my_env_t *add_env_node_end(my_env_t **ptr, const char *key, const char *value);
my_env_t *find_env_node(my_env_t *head, const char *key);
my_env_t *del_env_node(my_env_t **headptr, const char *key);
void free_env(my_env_t **headptr);

char *search_path(info_t *info, list_t *path);

void expand_aliases(info_t *info);
char *expand_alias(info_t *info);

void expand_vars(info_t *info);
char *_expand_vars(info_t *info);

char **arrjoin(char **arr1, char **arr2);

unsigned int _atou(char *s);

int _isnumber(char *s);

char *_getenv(my_env_t *env, const char *key);

#endif /* SHELL_H */
