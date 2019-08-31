#include "string.h"

/**
 * _memcpy - copy a memory area
 * @dest: a pointer to the start of the target area
 * @src: a pointer to the start of the source area
 * @n: the number of bytes to copy
 *
 * Description: This function copies n bytes from the memory area at src
 * to the memory area at dest. These memory areas must not overlap.
 *
 * Return: a pointer to dest
 */
char *_memcpy(char *dest, const char *src, size_t n)
{
	char *pos = dest;

	while (n--)
		*pos++ = *src++;

	return (dest);
}
