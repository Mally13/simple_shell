#include "shell.h"
/**
 * count_tokens - Counts the number of tokens in a string
 * @commandline: the string whose tokens are to be counted
 * Return: number of tokens
 */
int count_tokens(char *commandline)
{
	int numtokens = 0;
	char *commandline_copy, *token;
	const char *delim = " \n";

	commandline_copy = strdup(commandline);
	if (!commandline_copy)
	{
		perror("Memory allocation error");
		return (-1);
	}
	token = strtok(commandline_copy, delim);
	while (token != NULL)
	{
		numtokens++;
		token = strtok(NULL, delim);
	}
	free(commandline_copy);
	return (numtokens);
}

/**
 * store_tokens - gets tokens from a string and stores them
 * @cmdline_copy: sting to be tokenized
 * @argv: Where to store the tokenized striings
 */

void store_tokens(char *cmdline_copy, char **argv)
{
	int i;
	char *token, *copy = strdup(cmdline_copy);
	const char *delim = " \n";

	token = strtok(copy, delim);
	for (i = 0; token != NULL; i++)
	{
		argv[i] = strdup(token);
		if (!argv[i])
		{
			perror("");
			free(copy);
			free(token);
			return;
		}

		token = strtok(NULL, delim);
	}
	argv[i] = NULL;
	free(copy);
}
