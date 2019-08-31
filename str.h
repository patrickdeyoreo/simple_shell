#ifndef STR_H
#define STR_H

#include <stdlib.h>

ssize_t _strchr(const char *str, char c);
ssize_t _strnchr(const char *str, char c, size_t n);
char *_strdup(const char *str);
char *_strndup(const char *str, size_t n);
ssize_t _strlen(const char *str);
ssize_t _strnlen(const char *str, size_t n);
char *_strcpy(char *dest, const char *src);
char *_strncpy(char *dest, const char *src, size_t n);
int _strcmp(const char *s1, const char *s2);
int _strncmp(const char *s1, const char *s2, size_t n);

#endif /* STR_H */
