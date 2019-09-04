#ifndef ERROR_H
#define ERROR_H

#include <unistd.h>
#include "info.h"
#include "string.h"
#include "types.h"


void _perror(const char *msg, size_t n, ...);
void _perror_default(info_t *info, const char *msg, size_t n, ...);
void _lperror(const char *msg, ...);
void _lperror_default(info_t *info, const char *msg, ...);

#endif /* ERROR_H */
