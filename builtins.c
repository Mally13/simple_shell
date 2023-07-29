#include "shell.h"
/**
 * handle_exit - exit the shell
 */
void handle_exit(void)
{
	int status = 0, i;

	if (argc > 0 && strcmp(argv[0], "exit") == 0)
	{
		for (i = 0; i < argc; i++)
			status += atoi(argv[i]);
	}

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
