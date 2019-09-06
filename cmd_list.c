#include "command.h"


/**
 * add_cmd_end - add a command at the end of the list
 * @headptr: a pointer to the address of the first list node
 * @cmd: the cmd to add to the list
 *
 * Return: If memory allocation fails, return NULL. Otherwise, return the
 * address of the new node.
 */
cmd_list_t *add_cmd_end(cmd_list_t **headptr, const char *cmd)
{
	cmd_list_t *new;

	if (!headptr)
		return (NULL);
	if (*headptr)
		return (add_cmd_end(&((*headptr)->next), cmd));

	new = malloc(sizeof(cmd_list_t));
	if (!new)
		return (NULL);

	new->tokens = tokenize(cmd);
	if (!new->tokens)
	{
		free(new);
		return (NULL);
	}
	new->next = NULL;
	*headptr = new;

	return (new);
}


/**
 * del_cmd - remove a command from a command list
 * @headptr: the first node
 * @index: argument passed
 * Return: address of deleted node
 */
cmd_list_t *del_cmd(cmd_list_t **headptr, size_t index)
{
	cmd_list_t *old;

	if (!(headptr && *headptr))
		return (NULL);
	if (index)
		return (del_cmd(&((*headptr)->next), index - 1));

	old = *headptr;
	*headptr = (*headptr)->next;

	free_tokens(&(old->tokens));
	free(old);

	return (old);
}


/**
 * pop_cmd - remove a node and retrieve it's tokens
 * @headptr: the first node
 * Return: command tokens
 */
char **pop_cmd(cmd_list_t **headptr)
{
	cmd_list_t *pop;
	char **tokens;

	if (!(headptr && *headptr))
		return (NULL);

	pop = *headptr;
	tokens = pop->tokens;
	*headptr = (*headptr)->next;

	free(pop);

	return (tokens);
}


/**
 * free_cmd_list - free a linked list and and set head to NULL
 * @headptr: the first node
 */
void free_cmd_list(cmd_list_t **headptr)
{
	if (headptr && *headptr)
	{
		free_cmd_list(&((*headptr)->next));
		free_tokens(&((*headptr)->tokens));
		free(*headptr);
		*headptr = NULL;
	}
}
