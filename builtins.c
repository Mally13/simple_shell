#include "shell.h"
/**
 * handle_exit - exit the shell
 */
void handle_exit(void)
{
	exit(0);
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
