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

	do {
		while (*cmd && (state = quote_state(*cmd)) != Q_NONE)
		{
			if (state & Q_WORD)
			{
				state_len = _quote_state_word(cmd, NULL);
				sep_index = _strnchr(cmd, ';', state_len);
				if (sep_index != -1)
				{
					state_len = sep_index;
					*(cmd++ + state_len) = '\0';
					++count;
				}
				cmd += state_len;
			}
			else if (state & Q_ESCAPE)
			{
				if (*(cmd + 1) == '\n')
					_strcpy(cmd, cmd + 2);
				else if (*(++cmd))
					++cmd;
			}
			else
			{
				cmd += quote_state_len(cmd + 1, state) + 1;
				if (*cmd && (state & (Q_SINGLE | Q_DOUBLE)))
					++cmd;
			}
		}
	} while (*(cmd += quote_state_len(cmd, Q_NONE)));

	return (count);
}

