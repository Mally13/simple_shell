#include "shell.h"
/**
 * execute_cmd - execute given command
 * @argv: Command argument
 */
int execute_cmd(char **argv)
{
	char *command = NULL, *absolute_command = NULL;
	pid_t pid;
	int status;

	if (argv && argv[0])
	{
		command = argv[0];
		absolute_command = get_cmd_path(command);
		if (absolute_command && access(absolute_command, X_OK) == 0)
		{
			pid = fork();
			if (pid < 0)
			{
				exit(errno);
			}
			else if (pid == 0)
			{
				if (execve(absolute_command, argv, NULL) == -1)
					exit(errno);
				exit(1);
			}
			else
			{
				waitpid(pid, &status, WUNTRACED);
				if (WIFEXITED(status))
					errno = WEXITSTATUS(status);
			}
			return (0);
		}
		else
		{
			errno = 127;
			return (-1);
		}
		free(absolute_command);
	}
	errno = 127;
	return (-1);
}
