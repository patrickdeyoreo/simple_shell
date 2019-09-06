#include "shell.h"

/**
 * parse_cmd - parse a command
 * @info: shell information
 *
 * Description: This function expands aliases, variables, and word splitting
 *
 * Return: the final number of tokens
 */
int parse_cmd(info_t *info)
{
	char **tokens, *tok;
	size_t n = 0;
	cmdlist_t *cmd = info->commands = cmd_to_list(info->line);

	while (cmd)
	{
		remove_comments(cmd);
		if (!cmd->tokens)
		{
			cmd = cmd->next;
			remove_cmd(&info->commands, n);
			continue;
		}
		expand_aliases(info->aliases, &(cmd->tokens));
		if (!cmd->tokens)
		{
			cmd = cmd->next;
			remove_cmd(&info->commands, n);
			continue;
		}
		expand_vars(info, &(cmd->tokens));
		if (!cmd->tokens)
		{
			cmd = cmd->next;
			remove_cmd(&info->commands, n);
			continue;
		}
		tokens = cmd->tokens;
		for (tok = *tokens; tok; tok = *(++tokens))
		{
			*tokens = dequote(tok);
			free(tok);
		}
		cmd = cmd->next;
		++n;
	}
	return (n);
}
