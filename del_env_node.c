#include "shell.h"

my_env_t *del_env_node(my_env_t **headptr, const char *key)
{
	my_env_t *tmp;
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
