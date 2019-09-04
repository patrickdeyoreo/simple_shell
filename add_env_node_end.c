#include "env.h"

/**
  * add_env_node_end - adds node at the end of list
  * @ptr: pointer
  * @key: name of environment variable
  * @value: value of environment variable
  * Return: pointer to list
  */
env_t *add_env_node_end(env_t **ptr, const char *key, const char *value)
{
	env_t *new;

	if (!ptr)
		return (NULL);

	if (*ptr)
		return (add_env_node_end(&((*ptr)->next), key, value));

	new = malloc(sizeof(env_t));
	if (!new)
		return (NULL);

	new->key = _strdup(key);
	new->value = _strdup(value);
	new->next = NULL;

	*ptr = new;
	return (new);
}

