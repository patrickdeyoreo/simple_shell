#include "string.h"

/**
 * _memdup - duplicate a memory area
 * @src: a pointer to the start of the source area
 * @n: the number of bytes to duplicate
 *
 * Return: If memory allocation fails, return NULL. Otherwise, return a
 * pointer to the start of the duplicated memory.
 */
char *_memdup(const char *src, size_t n)
{
	char *dest, *dup = dest = malloc(sizeof(char) * n);

	if (!dest)
		return (NULL);

	while (n--)
		*dest++ = *src++;

	return (dup);
}
