#ifndef HISTORY_H
#define HISTORY_H

#include "list.h"
#include "types.h"

/**
  * struct history - shell command history
  * @head: a pointer to the head of the history list
  * @filename: the name of the history to file
  * @n: the number of entries in the history list
  */
struct history
{
	struct list *head;
	char *filename;
	size_t n;
};

#endif /* HISTORY_H */
