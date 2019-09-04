#ifndef ENV_H
#define ENV_H

#include <stdlib.h>
#include "dict.h"
#include "string.h"

typedef struct dict env_t;

char *_getenv(env_t *env, const char *key);
env_t *env_to_list(char **env);
char **list_to_env(env_t *head);
env_t *add_env_node_end(env_t **ptr, const char *key, const char *value);
env_t *find_env_node(env_t *head, const char *key);
env_t *del_env_node(env_t **headptr, const char *key);
void free_env(env_t **headptr);

#endif /* ENV_H */
