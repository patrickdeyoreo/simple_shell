#ifndef GETLINE_H
#define GETLINE_H

#include <stdlib.h>
#include <unistd.h>
#include "string.h"

#define BUFSIZE 8192

/**
 * struct buf - a buffer structure
 * @buffer: the buffer
 * @r_pos: the read position
 * @w_pos: the write position
 */
typedef struct buf
{
	char buffer[BUFSIZE];
	char *r_pos;
	char *w_pos;
} buf_t;

ssize_t _getline(char **line, size_t *n, int fd);
ssize_t _getline_one(buf_t *buf, ssize_t *len, char **line, size_t *n);
ssize_t _getline_full(buf_t *buf, ssize_t *len, char **line, size_t *n);
void _getline_free_line(char **line, size_t *n);

#endif /* GETLINE_H */
