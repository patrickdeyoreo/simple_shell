#include "shell.h"
/**
  * listtoenv - creates linked list from environment
  * @head: argument passed
  * Return: pointer to list
  */

char **listtoenv(my_env_t *head)
{
	char **env;
	size_t len = 0;
	my_env_t *tmp = head;

	while (tmp)
	{
		tmp = tmp->next;
		len++;
	}
	env = malloc(sizeof(char*) * (len + 1));
	if (!env)
		return (NULL);
	for (len = 0; head; len++)
	{
		env[len] = strjoin(head->key, head->value, '=');
		head = head->next;
	}
	env[len] = NULL;
	return (env);
}
