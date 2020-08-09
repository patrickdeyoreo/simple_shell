#include "getline.h"
#include "string.h"

/**
 * _realloc - reallocate a buffer
 * @old: pointer to the buffer
 * @old_size: current size of the buffer
 * @new_size: desired size of the buffer
 * Return: If memory allocation fails, return NULL.
 * Otherwise, return a pointer to the new buffer.
 */
static void *_realloc(void *old, size_t old_size, size_t new_size)
{
	void *new = NULL;

	if (old)
	{
		if (new_size)
		{
			new = malloc(new_size);
			if (new)
			{
				_memcpy(new, old, old_size < new_size ? old_size : new_size);
				free(old);
			}
		}
		else
		{
			free(old);
		}
	}
	return (new);
}

/**
 * _getline_next - read a line of input
 * @buf: pointer to the static buffer
 * @line: address of a pointer to the line
 * @size: address of a pointer to the line size
 * @n: number of characters to copy from the buffer
 * Return: If memory allocation fails, return NULL.
 * Otherwise, return a pointer to the line of input.
 */
static char *_getline_next(buf_t *buf, char **line, size_t *size, size_t n)
{
	char *temp = NULL;

	if (*line)
		temp = _realloc(*line, *size, *size + n);
	else
		temp = malloc(n + 1);

	if (temp)
	{
		*line = temp;

		if (*size)
			*size -= 1;

		_memcpy(*line + *size, buf->next, n);
		*size += n;

		(*line)[*size] = '\0';
		*size += 1;
	}
	else
	{
		free(*line);
		*line = NULL;
	}
	return (*line);
}

/**
 * _getline_buf - create, get, and delete buffers
 * @table: buffers indexed by file descriptor
 * @fd: file descriptor
 * Return: NULL or a pointer to the buffer associated with fd
 */
static buf_t *_getline_buf(buf_table_t *table, const int fd)
{
	buf_table_node_t *node = NULL;
	buf_t *buf = NULL;
	size_t index = fd % GETLINE_TABLE_SIZE;

	if (table)
	{
		if (fd > -1)
		{
			node = (*table)[index];
			while (node && node->fd != fd)
				node = node->next;
			if (node == NULL)
			{
				node = malloc(sizeof(*node));
				if (node)
				{
					node->fd = fd;
					node->buf.remaining = 0;
					node->next = (*table)[index];
					(*table)[index] = node;
				}
			}
			if (node)
				buf = &node->buf;
		}
		else
		{
			for (index = 0; index < GETLINE_TABLE_SIZE; index += 1)
			{
				while ((node = (*table)[index]))
					(*table)[index] = node->next, free(node);
			}
		}
	}
	return (buf);
}

/**
 * _getline - read a line of input
 * @fd: file descriptor from which to read
 * Return: If an error occurs or there are no more lines, return NULL.
 * Otherwise, return the next line of input.
 */
char *_getline(const int fd)
{
	static buf_table_t table;
	buf_t *buf = _getline_buf(&table, fd);
	char *line = NULL;
	size_t size = 0, n_next = 0;
	ssize_t eol = 0, n_read = 0;

	if (buf)
	{
		do {
			if (n_read == -1)
				return (free(line), NULL);
			if (buf->remaining == 0)
				buf->next = buf->buffer;
			if (n_read)
				buf->remaining = n_read;
			if (buf->remaining == 0)
				continue;
			eol = _memchr(buf->next, '\n', buf->remaining);
			if (eol == -1)
				n_next = buf->remaining;
			else
				n_next = eol + 1;
			if (_getline_next(buf, &line, &size, n_next))
				buf->next += n_next, buf->remaining -= n_next;
			else
				return (NULL);
			if (line[size - 1] == '\n')
				return (line);
		} while ((n_read = read(fd, buf->buffer, GETLINE_BUFFER_SIZE)));
	}
	return (line);
}
