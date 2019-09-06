#include "command.h"

/**
 * cmd_to_list - construct a linked list of tokenized commands
 * @cmd: the command to parse
 *
 * Return: If memory allocation fails, return NULL. Otherwise, return a
 * pointer to the head of the new list.
 */
cmd_list_t *cmd_to_list(const char *cmd)
{
	cmd_list_t *head = NULL;
	size_t count;
	char *split = _strdup(cmd);

	if (!split)
		return (NULL);

	count = split_cmd(split);

	if (!_cmd_to_list(&head, split, count))
	{
		free_cmd_list(&head);
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
cmd_list_t *_cmd_to_list(cmd_list_t **tailptr, char *split, size_t count)
{
	cmd_list_t *tail;

	if (!count)
		return (*tailptr);

	tail = add_cmd_end(tailptr, split);
	if (!tail)
		return (NULL);

	while (*split++)
		;

	return (_cmd_to_list(&tail, split, count - 1));
}
