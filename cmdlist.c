#include "command.h"

/**
 * cmd_to_list - construct a linked list of command trees
 * @cmd: the command to parse
 *
 * Return: If memory allocation fails, return NULL. Otherwise, return the
 * address of the head of the new list
 */
cmdlist_t *cmd_to_list(const char *cmd)
{
	cmdlist_t *head = NULL, *tail = NULL;
	char *temp;
	ssize_t len;

	if (!cmd)
		return (NULL);

	while (*cmd)
	{
		len = _strchr(cmd, ';');
		if (len == -1)
			len = _strlen(cmd);

		temp = _strndup(cmd, len);
		tail = add_cmd_end(&head, temp);
		free(temp);

		if (!tail)
			return (free_cmdlist(&head));

		if (cmd[len])
			cmd += len + 1;
		else
			cmd += len;
	}
	return (head);
}

/**
 * add_cmd - insert a command at the beginning of the list
 * @headptr: a pointer to the address of the first list node
 * @cmd: the cmd to add to the list
 *
 * Return: If memory allocation fails, return NULL. Otherwise, return the
 * address of the new node.
 */
cmdlist_t *add_cmd(cmdlist_t **headptr, const char *cmd)
{
	cmdlist_t *new;

	if (!headptr)
		return (NULL);

	new = malloc(sizeof(cmdlist_t));
	if (!new)
		return (NULL);

	new->cmd = _strdup(cmd);
	new->next = *headptr;
	*headptr = new;

	return (new);
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

	new->cmd = _strdup(cmd);
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

	free(temp->cmd);
	free(temp);

	return (temp);
}

/**
 * free_cmdlist - free a linked list and and set head to NULL
 * @headptr: the first node
 *
 * Return: NULL
 */
cmdlist_t *free_cmdlist(cmdlist_t **headptr)
{
	if (headptr && *headptr)
	{
		free_cmdlist(&((*headptr)->next));
		free((*headptr)->cmd);
		free(*headptr);
		*headptr = NULL;
	}
	return (NULL);
}
