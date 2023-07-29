#include "shell.h"
char **argv;
char *cmdline_copy = NULL;
int argc;
char *commandline = NULL;
char *prog;
int execution_count = 0;

/**
 * main - Get user input
 *
 * Return: 0 (success)
 */

int main(int ac, char **av)
{
	int cont = 1, numtokens = 0, i;
	char *prompt = "", exit_msg[] = "exit\n";
	size_t n = 0;
	ssize_t nchars_read;

	prog = av[(ac - ac)];
	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO))
		prompt = "($) ";
	while (cont)
	{
		execution_count++;
		write(STDIN_FILENO, prompt, strlen(prompt));
		nchars_read = getline(&commandline, &n, stdin);
		if (nchars_read == -1)
		{
			if (feof(stdin))
			{
				free(commandline);
				return (-1);
			}
			write(STDOUT_FILENO, exit_msg, strlen(exit_msg));
			free(commandline);
			return (-1);
		}
		if (commandline[nchars_read - 1] == '\n')
			commandline[nchars_read - 1] = '\0';
		cmdline_copy = malloc(sizeof(char) * nchars_read);
		if (cmdline_copy == NULL)
		{
			perror("");
			free(commandline);
			return (-1);
		}
		strcpy(cmdline_copy, commandline);
		numtokens = count_tokens(commandline);
		argc = numtokens + 1;
		argv = malloc(sizeof(char *) * argc);
		if (argv == NULL)
		{
			perror("");
			free(cmdline_copy);
			free(commandline);
			return (-1);
		}
		store_tokens(cmdline_copy, argv);
		if (strcmp(argv[0], "exit") == 0)
		{
			handle_exit();
			cont = 0;
		}
		if (strcmp(argv[0], "env") == 0)
			handle_env();
		execute_cmd(argv);
		for (i = 0; i < argc; i++)
			free(argv[i]);
		free(argv);
		free(cmdline_copy);
	}
	free(commandline);
	return (0);
}
