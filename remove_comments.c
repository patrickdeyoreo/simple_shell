#include "shell.h"

/**
 * remove_comments - remove comments (#) from a command
 * @cmd: pointer to the cmd to process
 */
void remove_comments(cmd_list_t *cmd)
{
	char **tokens, **new, *tmp;

	for (tokens = cmd->tokens; *tokens; ++tokens)
	{
		if (**tokens == '#')
		{
			tmp = *tokens;
			*tokens = NULL;
			new = arrdup(cmd->tokens);
			*tokens = tmp;
			free_tokens(&(cmd->tokens));
			cmd->tokens = new;
			free_cmd_list(&(cmd->next));
			return;
		}
	}
}
