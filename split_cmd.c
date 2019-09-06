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

	while (*(cmd += _quote_state_none(cmd, &state)))
	{
		do {
			if (state == Q_WORD)
			{
				state_len = _quote_state_word(cmd, NULL);
				sep_index = _strnchr(cmd, ';', state_len);
				if (sep_index == -1)
				{
					cmd += state_len;
				}
				else
				{
					cmd[sep_index] = '\0';
					cmd += sep_index + 1;
					++count;
				}
				state = quote_state(*cmd);
			}
			else
			{
				++cmd;
				cmd += quote_state_fn(state)(cmd, &state);
				if (*cmd)
					++cmd;
			}
		} while (*cmd && state != Q_NONE);
	}
	return (count);
}

