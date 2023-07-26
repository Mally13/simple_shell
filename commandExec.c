#include "shell.h"
/**
 * execute_cmd - execute given command
 * @argv: Command argument
 */

void execute_cmd(char **argv)
{
	char *command = NULL;
	pid_t pid;
	int status;

	if (argv)
	{
		command = argv[0];
		if (strcmp(command, "exit") == 0)
			handle_exit();
		else if (strcmp(command, "env") == 0)
			handle_env();
		else
		{
			if (command && access(command, X_OK) == 0 && argv[1] == NULL)
			{
				pid = fork();
				if (pid < 0)
					perror("");
				else if (pid == 0)
				{
					if (system(command) == -1)
						perror("");
				}
				else
					wait(&status);
			}
			else
			{
				write(STDOUT_FILENO, "No such file or directory\n",
						strlen("No such file or directory\n"));
			}
		}
	}
}
