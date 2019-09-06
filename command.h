#ifndef COMMAND_H
#define COMMAND_H

#include <stdlib.h>
#include "quote.h"
#include "string.h"
#include "tokens.h"
#include "types.h"

/**
 * struct cmd_list - a linked list of commands
 * @tokens: tokenized command
 * @next: next command
 */
struct cmd_list
{
	char **tokens;
	struct cmd_list *next;
};

/**
 * struct cmd_tree - a binary tree of commands
 * @tokens: a simple command with no separators
 * @left: the command to execute upon failure
 * @right: the command to execute upon success
 */
struct cmd_tree
{
	char **tokens;
	struct cmd_tree *left;
	struct cmd_tree *right;
};

cmd_list_t *cmd_to_list(const char *cmd);
cmd_list_t *_cmd_to_list(cmd_list_t **tailptr, char *split, size_t count);

size_t split_cmd(char *cmd);

cmd_list_t *add_cmd_end(cmd_list_t **headptr, const char *cmd);
cmd_list_t *del_cmd(cmd_list_t **headptr, size_t index);
char **pop_cmd(cmd_list_t **headptr);
void free_cmd_list(cmd_list_t **headptr);

cmd_tree_t *cmd_to_tree(const char *cmd);
void free_cmd_tree(cmd_tree_t **rootptr);

#endif /* COMMAND_H */
