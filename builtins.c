#include "shell.h"
/**
 * handle_exit - exit the shell
 */
void handle_exit(void)
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
/**
 * changeDirectory - Changes the directory
 * @argv: Argument Vaiables
 * Return: Return 0
 */
void changeDirectory(char **argv)
{
	char *currentDirectory, *dirError = ": no such directory\n";
	int status = 0;

	currentDirectory = getcwd(NULL, 0);
	if (argv[1] == NULL)
	{
		chdir(getenv("HOME"));
		exit (status);
	}

	else if (strcmp(argv[1], "-") == 0)
	{
		chdir(getenv("HOME"));
		exit (status);
	}

	else
	{
		if (chdir(argv[1]) != 0)
		{
			write(STDOUT_FILENO, argv[1], strlen(argv[1]));
			write(STDOUT_FILENO, dirError, strlen(dirError));
			exit(1);
		}
	}

	currentDirectory = malloc(sizeof(char *) * 1024);
	setenv("PWD", currentDirectory, 0);
	free(currentDirectory);
}
