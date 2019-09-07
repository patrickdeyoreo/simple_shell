#include "shell.h"

/**
 * open_script - execute commands from a script
 * @info: shell information
 */
void open_script(info_t *info)
{
	char *err;

	if (close(STDIN_FILENO) == -1)
	{
		perror(*info->argv);

		free_info(info);
		exit(127);
	}
	info->script = info->argv[1];

	if (open(info->script, O_RDONLY) == -1)
	{
		err = strjoin("Can't open", info->script, ' ', NULL);

		_perror_default(info, err, 0);

		free_info(info);
		free(err);
		exit(127);
	}
	info->interactive = isatty(STDIN_FILENO);
}
