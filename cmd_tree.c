#include "parse.h"

/**
 * cmd_to_tree - construct a binary tree of commands
 * @cmd: the command to parse
 *
 * Return: If memory allocation fails, return NULL. Otherwise, return the
 * address of the root of the new tree
 */
cmd_tree_t *cmd_to_tree(const char *cmd __attribute__((unused)))
{
	return (NULL);
}

/**
 * free_cmd_tree - free a binary tree and and set root to NULL
 * @rootptr: pointer
 * Return: NULL
 */
cmd_tree_t *free_cmd_tree(cmd_tree_t **rootptr)
{
	if (rootptr && *rootptr)
	{
		free_cmd_tree(&((*rootptr)->left));
		free_cmd_tree(&((*rootptr)->right));
		free((*rootptr)->cmd);
		*rootptr = NULL;
	}
	return (NULL);
}
