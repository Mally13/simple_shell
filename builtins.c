#include "shell.h"
/**
 * handle_exit - exit the shell
 * Return: 0
 */
void handle_exit(void)
{
	_exit(0);
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

/**
 * changeDirectory - Changes the directory
 * @argv: Argument variable
 * Return: 0 on success
 */
int changeDirectory(char **argv)
{
	char *currentDirectory, *dirError = ": no such directory\n";

	currentDirectory = malloc(sizeof(char *) * 1024);
	if (argv[1] == NULL)
	{
		chdir(getenv("HOME"));
		return (1);
	}
	else if (strcmp(argv[1], "-") == 0)
	{
		chdir(getenv("HOME"));
		return (1);
	}
	else
	{
		if (chdir(argv[1]) == -1)
		{
			write(STDOUT_FILENO, argv[1], strlen(argv[1]));
			write(STDOUT_FILENO, dirError, strlen(dirError));
			return (-1);
		}
	}
	getcwd(currentDirectory, 1024);
	setenv("PWD", currentDirectory, 0);
	free(currentDirectory);

	return (0);
}
