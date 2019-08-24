#include "shell.h"

void _num_to_str(char **buf, size_t n)
{
	if (n > 9)
		_num_to_str(buf, n/10);
	**buf = '0' + n % 10;
	*buf += 1;
	**buf = '\0';
}
