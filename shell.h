#ifndef SHELL_H
#define SHELL_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

extern char **environ;

/**
 * struct list_s - singly linked list
 * @str: dynamically-allocated string
 * @next: pointer to the next node
 */
typedef struct list
{
	char *str;
	struct list *next;
} list_t;

list_t *strtolist(const char *str, char delim);
list_t *add_node(list_t **headptr, const char *str);
list_t *add_node_end(list_t **headptr, const char *str);
void free_list(list_t **headptr);

ssize_t _strchr(const char *str, char c);
char *_strdup(const char *str);
ssize_t _strlen(const char *str);
int _strncmp(const char *s1, const char *s2, size_t n);
char **tokenize(const char *str);

size_t count_tokens(const char *str);
void free_tokens(char **tokens);

int _isspace(int c);
char *_memcpy(char *dest, const char *src, size_t n);

char *_getenv(const char *name);

#endif /* SHELL_H */
