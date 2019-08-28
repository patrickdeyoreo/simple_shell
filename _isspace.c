#include "shell.h"

/**
 * _isspace - check if a character is whitespace
 * @c: the character to check
 * Return: If c is a whitespace character, return 1. Otherwise, return 0.
 */
int _isspace(int c)
{
	return (c == ' ' || (c >= 0x09 && c <= 0x0d));
}
