#ifndef SHELL_H
#define SHELL_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

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
  * struct info - shell state
  */
typedef struct info
{
	char *line;
	size_t len;
	char **tokens;
	int status;
	pid_t pid;
	list_t *path;
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

static built_in_t ops[] = {
	{"env", _env, "Usage: env"},
	{"exit", exit_, "Usage: exit"},
	{NULL, NULL, NULL}
};

int _read(info_t *info);
int _run(info_t *info);
int _exec(info_t *info);

list_t *strtolist(const char *str, char delim);
list_t *add_node(list_t **headptr, const char *str);
list_t *add_node_end(list_t **headptr, const char *str);
void free_list(list_t **headptr);

ssize_t _strchr(const char *str, char c);
char *_strdup(const char *str);
ssize_t _strlen(const char *str);
int _strcmp(const char *s1, const char *s2);
int _strncmp(const char *s1, const char *s2, size_t n);
char **tokenize(const char *str);

size_t count_tokens(const char *str);
void free_tokens(char **tokens);

int _isspace(int c);
char *_memcpy(char *dest, const char *src, size_t n);

char *_getenv(const char *name);

#endif /* SHELL_H */
