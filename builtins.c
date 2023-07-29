#include "shell.h"
/**
 * handle_exit - exit the shell
 */
void handle_exit(void)
{
	int status = 0, i;

	if (argv[1] != NULL)
		status = atoi(argv[1]);

	for (i = 0; i < argc; i++)
		free(argv[i]);
	free(argv);
	free(cmdline_copy);
	free(commandline);
	exit(status);
}
/**
 * handle_env - handle environ variable
 */
void handle_env(void)
{
	char **env;

	env = environ;
	for (; *env != NULL; env++)
	{
		write(STDOUT_FILENO, *env, strlen(*env));
		write(STDOUT_FILENO, "\n", 1);
	}
}
