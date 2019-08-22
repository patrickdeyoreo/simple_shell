#include "shell.h"


int exit_(info_t *info)
{
	exit(info->status);
	return (0);
}
