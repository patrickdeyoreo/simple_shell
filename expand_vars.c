#include "shell.h"


/**
 * expand_vars - perform variable expansion on the current set of tokens
 * @info: shell information
 */
void expand_vars(info_t *info)
{
	char **new = NULL, **old, **tmp, **tokens;

	for (tokens = info->tokens; *info->tokens; ++info->tokens)
	{
		old = new;
		tmp = _expand_vars(info);
		new = arrjoin(old, tmp);
		free_tokens(old);
		free_tokens(tmp);
		free(*info->tokens);
	}
	free(tokens);
	info->tokens = new;
}


/**
 * _expand_vars - perform variable expansion on a token
 * @info: shell information
 *
 * Return: the expanded token
 */
char **_expand_vars(info_t *info)
{
	char *var = NULL, *val = NULL, *tok = *info->tokens;
	size_t pos = 0, var_len = 1, val_len = 1;
	quote_state_t state = NONE;

	while (tok[pos])
	{
		if (get_quote_state_fn(state)(tok + pos, NULL) == 0)
		{
			if ((state & (DOUBLE | SINGLE)) && !tok[++pos])
				break;
			state = get_quote_state(*(tok + pos));
			if ((state & (DOUBLE | SINGLE)) && !tok[++pos])
				break;
		}
		if (state == SINGLE)
		{
			pos += quote_state_single(tok + pos, &state);
			continue;
		}
		if (tok[pos] != '$')
		{
			++pos;
			continue;
		}
		if (tok[pos + 1] == '$')
		{
			val = num_to_str(info->pid);
		}
		else if (tok[pos + 1] == '?')
		{
			val = num_to_str(info->status);
		}
		else if (_isident(tok[pos + 1]) && !_isdigit(tok[pos + 1]))
		{
			while (_isident(tok[pos + var_len + 1]))
				++var_len;

			var = _strndup(tok + pos + 1, var_len);
			val = _getenv(info->env, var);

			if (val)
				val = _strdup(val);
			else
				val = _strdup("");

			free(var);
			var = NULL;
		}
		if (val)
		{
			val_len = _strlen(val);
			*info->tokens = malloc(sizeof(char) * (
					pos + val_len + _strlen(tok + pos + var_len) + 1)
					);
			_memcpy(*info->tokens, tok, pos);
			_memcpy(*info->tokens + pos, val, val_len);
			_strcpy(*info->tokens + pos + val_len, tok + pos + var_len + 1);

			free(tok);
			tok = *info->tokens;

			free(val);
			val = NULL;

			var_len = 1;

			pos += val_len;

			continue;
		}
		++pos;
	}
	return (tokenize(*info->tokens));
}
