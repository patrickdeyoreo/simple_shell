#ifndef LIST_H
#define LIST_H

#include <stdlib.h>
#include <unistd.h>
#include "string.h"

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

list_t *strtolist(const char *str, char delim);
list_t *add_node(list_t **headptr, const char *str);
list_t *add_node_end(list_t **headptr, const char *str);
void free_list(list_t **headptr);

#endif /* LIST_H */
