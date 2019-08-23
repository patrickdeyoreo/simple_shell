#include "shell.h"
/**
 * _atoi - convert a string to an integer
 * @s: character to check
 * Return: int
 */

int _atoi(char *s)
{
	int i;
	int dash_counter = 0;
	int number = 0;
	int number_started = 0;

	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			number_started = 1;
			number = number * 10 - (s[i] - '0');
		}
		else
		{
			if (number_started == 1)
			{
				break;
			}
			if (s[i] == '-')
			{
				dash_counter++;
			}
		}

	}
	if (dash_counter % 2 == 0)
	{
		return (-number);
	}
	return (number);
}
