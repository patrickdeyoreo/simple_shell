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
#include "parse.h"
#include "quote.h"
#include "str.h"
extern char **environ;

/**
 * struct list - singly linked list
 * @str: dynamically-allocated string
 * @next: pointer to the next node
 */
typedef struct list
{
	char *str;
	struct list *next;
} list_t;
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

typedef struct built_in built_in_t;

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
  * @commands: arguments passed
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
	list_t *path;
	char *full_cmd;
	built_in_t *ops;
	struct cmd_list *commands;
	alias_t *aliases;
} info_t;

/**
  * struct built_in - built-in command
  * @name: arguments passed
  * @f: function
  * @help: arguments passed
  */
struct built_in
{
	char *name;
	int (*f)(info_t *);
	char *help;
};

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
void open_script(char **argv);

int _read(info_t *info);
int _run(info_t *info);
int _exec(info_t *info);

char *num_to_str(size_t n);
void _num_to_str(char **buf, size_t n);
void _perror(size_t argc, ...);

list_t *strtolist(const char *str, char delim);
list_t *add_node(list_t **headptr, const char *str);
list_t *add_node_end(list_t **headptr, const char *str);
void free_list(list_t **headptr);

my_env_t *envtolist(char **env);
char **listtoenv(my_env_t *head);
my_env_t *add_env_node_end(my_env_t **ptr, const char *key, const char *value);
my_env_t *find_env_node(my_env_t *head, const char *key);
my_env_t *del_env_node(my_env_t **headptr, const char *key);
void free_env(my_env_t **headptr);

char *search_path(info_t *info, list_t *path);
void expand_aliases(info_t *info);
char *expand_alias(info_t *info);

char *strjoin(char *s1, char *s2, char c);
char **arrjoin(char **arr1, char **arr2);

int _isnumber(char *s);
int _isdigit(char c);
int _isquote(int c);
int _isspace(int c);

unsigned int _atou(char *s);

char *_memcpy(char *dest, const char *src, size_t n);

char *_getenv(my_env_t *env, const char *key);

#endif /* SHELL_H */
