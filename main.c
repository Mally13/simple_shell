#include "shell.h"
/**
 * main - Get user input
 *
 * Return: 0 (success)
 */

int main(void)
{
	char **argv;
	int argc;
	char *prompt = "", exit_msg[] = "exit\n";
	char *commandline = NULL, *cmdline_copy = NULL;
	size_t n = 0;
	ssize_t nchars_read;
	int numtokens = 0, i;

	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO))
		prompt = "($) ";
	while (1)
	{
		write(STDIN_FILENO, prompt, strlen(prompt));
		nchars_read = getline(&commandline, &n, stdin);
		if (nchars_read == -1)
		{
			if (feof(stdin))
				break;
			write(STDOUT_FILENO, exit_msg, strlen(exit_msg));
			return (-1);
		}
		cmdline_copy = strdup(commandline);
		if (cmdline_copy == NULL)
		{
			perror("");
			return (-1);
		}
		numtokens = count_tokens(commandline);
		argc = numtokens + 1;
		argv = malloc(sizeof(char *) * argc);
		store_tokens(cmdline_copy, argv);
		execute_cmd(argv);
	}
	for (i = 0; i < argc; i++)
	{
		free(argv[i]);
	}
	free(commandline);
	free(cmdline_copy);
	free(argv);
	return (0);
}
