#include "shell.h"
/**
* count_tokens - Counts the number of tokens in a string
* @commandline: the string whose tokens are to be counted
* Return: number of tokens
*/
int count_tokens(char *commandline)
{
	int numtokens = 0;
	char *token;
	const char *delim = " \"\n";

	token = strtok(commandline, delim);
	while (token != NULL)
	{
		numtokens++;
		token = strtok(NULL, delim);
	}
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
	char *token;
	const char *delim = " \"\n";

	token = strtok(cmdline_copy, delim);
	for (i = 0; token != NULL; i++)
	{
		argv[i] = malloc(sizeof(char) * strlen(token));
		strcpy(argv[i], token);

		token = strtok(NULL, delim);
	}
	argv[i] = NULL;
}
