#include "env.h"

/**
 * free_env - free a linked list and and set head to NULL
 * @headptr: the first list node
 */
void free_env(env_t **headptr)
{
	if (!*headptr)
		return;

	free_env(&((*headptr)->next));
	free((*headptr)->key);
	free((*headptr)->value);
	free(*headptr);
	*headptr = NULL;
}
