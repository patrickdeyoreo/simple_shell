#include "shell.h"

my_env_t *find_env_node(my_env_t *head, const char *key)
{
	if (!head)
		return (NULL);
	if (!_strcmp(head->key, key))
		return (head);
	return (find_env_node(head->next, key));
}
