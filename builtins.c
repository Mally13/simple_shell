#include "shell.h"
/**
 * handle_exit - exit the shell
 */
void handle_exit()
{
	int status = 0, i;

	if (argv[1] != NULL)
		status = atoi(argv[1]);
	if (strcmp(argv[0], "exit") != 0)
		status = errno;

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
