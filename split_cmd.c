#include "command.h"

/**
 * split_cmd - split a command with NULL-bytes on unquoted semicolons
 * @cmd: the command to split
 *
 * Return: The total number of commands resulting from the split
 */
size_t split_cmd(char *cmd)
{
	size_t count = 1, state_len;
	ssize_t sep_index;
	quote_state_t state;

	while (*(cmd += quote_state_none(cmd, &state)))
	{
		do {
			if (state == WORD)
			{
				state_len = quote_state_word(cmd, &state);
				sep_index = _strnchr(cmd, ';', state_len);
				if (sep_index > -1)
				{
					cmd[sep_index] = '\0';
					++count;
				}
				cmd += state_len;
			}
			else
			{
				++cmd;
				cmd += get_quote_state_fn(state)(cmd, &state);
				if (*cmd)
					++cmd;
			}
		} while (*cmd && state != NONE);
	}
	return (count);
}

