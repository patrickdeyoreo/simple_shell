#include "shell.h"


void expand_vars(info_t *info)
{
	char **new, **old, **tmp, **tokens = info->tokens;

	new = malloc(sizeof(char *) * 1);
	if (new)
	{
		new[0] = NULL;
		while (*tokens)
		{
			old = new;
			tmp = tokenize(_expand_vars(info));
			new = arrjoin(old, tmp);
			free_tokens(old);
			free_tokens(tmp);
			free(*tokens);
			++tokens;
		}
		free(info->tokens);
		info->tokens = new;
	}
}


char *_expand_vars(info_t *info)
{
	char *var = NULL, *val = NULL, *tok = info->tokens[0];
	size_t pos = 0, var_len = 0, val_len = 0;

	while (tok[pos])
	{

		if (tok[pos++] == '$')
		{
			if (tok[pos] == '$')
			{
				var_len = 1;
				val = num_to_str(info->pid);
			}
			else if (tok[pos] == '?')
			{
				var_len = 1;
				val = num_to_str(info->status);
			}
			else if (_isident(tok[pos]) && !_isdigit(tok[pos]))
			{
				var_len = 1;
				while (_isident(tok[pos + var_len]))
					++var_len;

				var = _strndup(tok + pos, var_len);
				val = _strdup(_getenv(info->env, var));
				if (!val)
					val = _strdup("");

				free(var);
			}
		}
		if (val)
		{
			val_len = _strlen(val);

			tok = malloc(sizeof(char) * (pos + val_len + _strlen(info->tokens[0] + pos + var_len)));

			_memcpy(tok, info->tokens[0], pos - 1);
			_memcpy(tok + pos - 1, val, val_len);
			_strcpy(tok + pos - 1 + val_len, info->tokens[0] + pos + var_len);

			free(info->tokens[0]);
			info->tokens[0] = tok;

			pos += val_len;

			val = NULL;
		}
	}
	return (info->tokens[0]);
}
