#ifndef ENV_H
#define ENV_H

#include <stdlib.h>
#include "dict.h"
#include "string.h"

typedef struct dict env_t;

env_t *env_to_dict(char **env);
env_t *_env_to_dict(env_t **tailptr, char **env);
char **dict_to_env(env_t *head);

#endif /* ENV_H */
