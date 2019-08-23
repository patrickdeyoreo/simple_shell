#include "shell.h"


/**
 * add_node - insert a string at the beginning of the list
 * @head: a pointer to the address of the first list node
 * @str: the string to add to the list
 *
 * Return: If memory allocation fails, return NULL. Otherwise, return the
 * address of the new no
 */
list_t *add_node(list_t **headptr, const char *str)
{
	list_t *new;

	if (!headptr)
		return (NULL);

	new = malloc(sizeof(list_t));
	if (!new)
		return (NULL);

	new->str = _strdup(str);
	new->next = *headptr;

	*headptr = new;

	return (new);
}


/**
 * add_node_end - add a string at the end of the list
 * @head: a pointer to the address of the first list node
 * @str: the string to add to the list
 *
 * Return: If memory allocation fails, return NULL. Otherwise, return the
 * address of the new no
 */
list_t *add_node_end(list_t **headptr, const char *str)
{
	list_t *new;

	if (!headptr)
		return (NULL);

	if (*headptr)
		return (add_node_end(&((*headptr)->next), str));

	new = malloc(sizeof(list_t));
	if (!new)
		return (NULL);

	new->str = _strdup(str);
	new->next = *headptr;

	*headptr = new;

	return (new);
}


/**
 * free_list - free a linked list and and set head to NULL
 * @head: the first list node
 */
void free_list(list_t **headptr)
{
	if (!*headptr)
		return;

	free_list(&((*headptr)->next));
	free((*headptr)->str);
	free(*headptr);
	*headptr = NULL;
}


/**
 * strtolist - turn a string into a linked list
 */
list_t *strtolist(const char *str, char delim)
{
	list_t *head = NULL;
	list_t *tail = NULL;
	ssize_t len;

	if (!str)
		return (NULL);

	while (*str)
	{
		len = _strchr(str, delim);
		if (len == -1)
			len = _strlen(str);
		tail = add_node_end(&head, NULL);
		if (!tail)
		{
			free_list(&head);
			return (NULL);
		}

		tail->str = malloc(sizeof(char *) * len + 1);
		if (!tail->str)
		{
			free_list(&head);
			return (NULL);
		}
		_memcpy(tail->str, str, len);
		tail->str[len] = '\0';

		if (str[len])
			str += len + 1;
		else
			str += len;
	}

	return (head);
}
