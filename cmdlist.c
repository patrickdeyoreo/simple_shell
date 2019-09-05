#include "command.h"

/**
 * cmd_to_list - construct a linked list of tokenized commands
 * @cmd: the command to parse
 *
 * Return: If memory allocation fails, return NULL. Otherwise, return a
 * pointer to the head of the new list.
 */
cmdlist_t *cmd_to_list(const char *cmd)
{
	cmdlist_t *head = NULL;
	size_t count;
	char *split = _strdup(cmd);

	if (!split)
		return (NULL);

	count = split_cmd(split);

	if (!_cmd_to_list(&head, split, count))
	{
		free_cmdlist(&head);
		return (NULL);
	}
	free(split);

	return (head);
}


/**
 * _cmd_to_list - construct a linked list of tokenized commands (helper)
 * @tailptr: pointer to the tail of the command list
 * @split: a line split with null bytes on separators
 * @count: the number of commands contained in split
 *
 * Return: If memory allocation fails, return NULL. Otherwise, return a
 * pointer to the tail of the new list.
 */
cmdlist_t *_cmd_to_list(cmdlist_t **tailptr, const char *split, size_t count)
{
	cmdlist_t *tail;

	if (!count)
		return (*tailptr);

	tail = add_cmd_end(tailptr, split);
	if (!tail)
		return (NULL);

	while (*split++)
		;

	return (_cmd_to_list(&tail, split, count - 1));
}


/**
 * add_cmd_end - add a command at the end of the list
 * @headptr: a pointer to the address of the first list node
 * @cmd: the cmd to add to the list
 *
 * Return: If memory allocation fails, return NULL. Otherwise, return the
 * address of the new node.
 */
cmdlist_t *add_cmd_end(cmdlist_t **headptr, const char *cmd)
{
	cmdlist_t *new;

	if (!headptr)
		return (NULL);

	if (*headptr)
		return (add_cmd_end(&((*headptr)->next), cmd));

	new = malloc(sizeof(cmdlist_t));
	if (!new)
		return (NULL);

	new->tokens = tokenize(cmd);
	new->next = *headptr;
	*headptr = new;

	return (new);
}


/**
 * remove_cmd - remove a command from a command list
 * @headptr: the first node
 * @index: argument passed
 * Return: NULL
 */
cmdlist_t *remove_cmd(cmdlist_t **headptr, size_t index)
{
	cmdlist_t *temp;

	if (!(headptr && *headptr))
		return (NULL);
	if (index)
		return (remove_cmd(&((*headptr)->next), index - 1));

	temp = *headptr;
	*headptr = (*headptr)->next;

	free_tokens(&temp->tokens);
	free(temp);

	return (temp);
}


/**
 * free_cmdlist - free a linked list and and set head to NULL
 * @headptr: the first node
 */
void free_cmdlist(cmdlist_t **headptr)
{
	if (!(headptr && *headptr))
		return;

	free_cmdlist(&((*headptr)->next));
	free_tokens(&((*headptr)->tokens));
	free(*headptr);
	*headptr = NULL;
}
