#ifndef SHELL_H
#define SHELL_H

#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>
#include <errno.h>
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
  *
  *
  */
typedef struct my_env
{
	char *key;
	char *value;
	struct my_env *next;
} my_env_t;
/**
  * struct info - shell state
  */
typedef struct info
{
	char **argv;
	int argc;
	size_t cmd_num;
	char *line;
	size_t len;
	char **tokens;
	my_env_t *env;;
	int status;
	pid_t pid;
	list_t *path;
	char *full_cmd;
	char *cwd;
} info_t;

/**
  * struct built_in - built-in command
  */
typedef struct built_in
{
	char *name;
	int (*f)(info_t *);
	char *help;
} built_in_t;

int _env(info_t *info);
int exit_(info_t *info);
int _setenv(info_t *info);
int _unsetenv(info_t *info);

static built_in_t ops[] = {
	{"env", _env, "Usage: env"},
	{"exit", exit_, "Usage: exit"},
	{"setenv", _setenv, "Usage: setenv VARIABLE VALUE"},
	{"unsetenv", _unsetenv, "Usage: unsetenv VARIABLE"},
	{NULL, NULL, NULL}
};
char *num_to_str(size_t n);
void _num_to_str(char **buf, size_t n);
void _sigint(int signal);
int _read(info_t *info);
int _run(info_t *info);
int _exec(info_t *info);
void _perror(size_t argc, ...);
list_t *strtolist(const char *str, char delim);
list_t *add_node(list_t **headptr, const char *str);
list_t *add_node_end(list_t **headptr, const char *str);
void free_list(list_t **headptr);
my_env_t *envtolist(char **env);
char **listtoenv(my_env_t *head);
my_env_t *add_env_node_end(my_env_t **headptr, const char *key, const char *value);
my_env_t *find_env_node(my_env_t *head, const char *key);
void free_env(my_env_t **headptr);
my_env_t *del_env_node(my_env_t **headptr, const char *key);

int _atoi(char *s);
int _isnumber(char *s);
int _isdigit(char c);
ssize_t _strchr(const char *str, char c);
char *_strdup(const char *str);
ssize_t _strlen(const char *str);
char *_strcpy(char *dest, char *src);
int _strcmp(const char *s1, const char *s2);
int _strncmp(const char *s1, const char *s2, size_t n);
char **tokenize(const char *str);
char *strjoin(char *s1, char *s2, char c);
char *search_path(info_t *info, list_t *path);

size_t count_tokens(const char *str);
void free_tokens(char **tokens);

int _isspace(int c);
char *_memcpy(char *dest, const char *src, size_t n);

char *_getenv(const char *name);

#endif /* SHELL_H */
