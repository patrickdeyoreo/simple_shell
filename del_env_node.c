#include "env.h"

/**
  * del_env_node - deletes a node
  * @headptr: pointer to head
  * @key: variable name passed
  * Return: pointer to list
  */
env_t *del_env_node(env_t **headptr, const char *key)
{
	env_t *tmp;

	if  (!(headptr && *headptr))
		return (NULL);
	if (!_strcmp((*headptr)->key, key))
	{
		tmp = *headptr;
		(*headptr) = tmp->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
	else
		del_env_node(&((*headptr)->next), key);
	return (*headptr);
}
