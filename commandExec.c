#include "shell.h"
char *absolute_command = NULL;
/**
 * execute_cmd - execute given command
 * @argv: Command argument
 */
int execute_cmd(char **argv)
{
	char *command = NULL;
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
				free(absolute_command);
				_exit(errno);
			}
			else if (pid == 0)
			{
				if (execve(absolute_command, argv, NULL) == -1)
				{
					free(absolute_command);
					_exit(errno);
				}
				free(absolute_command);
				_exit(errno);
			}
			else
			{
				waitpid(pid, &status, WUNTRACED);
				free(absolute_command);
				handle_exit();
			}
			return (0);
		}
		else
		{
			free(absolute_command);
			return (-1);
		};
	}
	return (-1);
}
