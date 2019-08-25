#include "shell.h"

my_env_t *envtolist(char **env)
{
	char *env_str;
	my_env_t *head = NULL;
	size_t key_len = 0;

	while (*env)
	{
		env_str = _strdup(*env);
		key_len = _strchr(*env, '=');
		env_str[key_len] = '\0';
		add_env_node_end(&head, env_str, env_str + key_len + 1);
		free(env_str);
		env++;
	}
	return (head);
}
