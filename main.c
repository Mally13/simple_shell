#include "shell.h"

/**
 * main - Get user input
 * @argc: Number of arguments supplied
 * @argv: An array of pointers to arguments
 *
 * Return: 0 (success)
 */

int main(int argc, char **argv)
{
	char *prompt = "($) ";
	char *line;
	size_t n = 0;
	ssize_t nchars_read;

	(void)argc;
	(void)argv;
	
	while (1)
	{
		printf("%s", prompt);
		nchars_read = getline(&line, &n, stdin);
		
		if (nchars_read == -1)
		{
			printf("exit\n");
			return (-1);
		}
		printf("%s\n", line);	
		free(line);
	}
	return (0);
}
