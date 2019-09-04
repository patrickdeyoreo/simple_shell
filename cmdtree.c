#include "command.h"

/**
 * cmd_to_tree - construct a binary tree of commands
 * @cmd: the command to parse
 *
 * Return: If memory allocation fails, return NULL. Otherwise, return the
 * address of the root of the new tree
 */
cmdtree_t *cmd_to_tree(const char *cmd __attribute__((unused)))
{
	return (NULL);
}

/**
 * free_cmdtree - free a binary tree and and set root to NULL
 * @rootptr: pointer
 * Return: NULL
 */
cmdtree_t *free_cmdtree(cmdtree_t **rootptr)
{
	if (rootptr && *rootptr)
	{
		free_cmdtree(&((*rootptr)->left));
		free_cmdtree(&((*rootptr)->right));
		free((*rootptr)->cmd);
		*rootptr = NULL;
	}
	return (NULL);
}
