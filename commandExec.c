#include "shell.h"
/**
 * execute_cmd - execute given command
 * @argv: Command argument
 */

void execute_cmd(char **argv)
{
	char *command = NULL, *absolute_command = NULL, *error_msg;
	pid_t pid;
	int status;

	if (argv && argv[0])
	{
		command = argv[0];
		if (strcmp(command, "exit") == 0)
			handle_exit();
		else if (strcmp(command, "env") == 0)
			handle_env();
		else
		{
			absolute_command = get_cmd_path(command);
			if (absolute_command && access(absolute_command, X_OK) == 0)
			{
				pid = fork();
				if (pid < 0)
					perror("");
				else if (pid == 0)
				{
					if (execve(absolute_command, argv, NULL) == -1)
						perror(command);
				}
				else
				{
					wait(&status);
				}
			}
			else
			{
				error_msg = malloc(strlen(command) + strlen(": command not found") + 2);
				if (error_msg)
				{
					sprintf(error_msg, "%s: command not found\n", command);
					write(STDOUT_FILENO, error_msg, strlen(error_msg));
					free(error_msg);
				}
			}
		}
	}
}
