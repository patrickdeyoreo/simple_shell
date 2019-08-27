#include "shell.h"
/**
  * _getenv - gets value of the environment variable
  * @env: pointer to environment
  * @key: name of the environment variable
  * Return: pointer to string
  */
char *_getenv(my_env_t *env, const char *key)
{
	if (!key)
		return (NULL);

	while (env)
	{
		if (!_strcmp(env->key, key))
			return (env->value);
		env = env->next;
	}

	return (NULL);
}
