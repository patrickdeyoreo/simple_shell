#include "shell.h"

my_env_t *add_env_node_end(my_env_t **headptr, const char *key, const char *value)
{
	my_env_t *new;

	if (!headptr)
		return (NULL);

	if (*headptr)
		return (add_env_node_end(&((*headptr)->next), key, value));

	new = malloc(sizeof(my_env_t));
	if (!new)
		return (NULL);

	new->key = _strdup(key);
	new->value = _strdup(value);
	new->next = NULL;

	*headptr = new;
	return (new);
}

