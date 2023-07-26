#include "shell.h"
/**
 * main - Get user input
 *
 * Return: 0 (success)
 */

int main(void)
{
	char **argv;
	char *prompt = "", exit_msg[] = "exit\n";
	char *commandline = NULL, *cmdline_copy = NULL;
	size_t n = 0;
	ssize_t nchars_read;
	int numtokens = 0;

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
			else
			{
				write(STDOUT_FILENO, exit_msg, strlen(exit_msg));
				return (-1);
			}
		}
		cmdline_copy = malloc(sizeof(char) * nchars_read);
		if (cmdline_copy == NULL)
		{
			perror("");
			return (-1);
		}
		strcpy(cmdline_copy, commandline);
		numtokens = count_tokens(commandline);
		argv = malloc(sizeof(char *) * (numtokens + 1));
		store_tokens(cmdline_copy, argv);
		execute_cmd(argv);
	}
	free(commandline);
	free(cmdline_copy);
	free(argv);
	return (0);
}
