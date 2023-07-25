#include "main.h"
/**
 * get_path - Get command full path
 * @command: command argument
 * Return: Return the full path on success
 */
char *get_path(char *command)
{
	char *path, *path_duplicate, *path_token, *file_path;
	int command_len, directory_len;
	struct stat buffer_holder;

	path = getenv("PATH");

	if (path)
	{
		command_len = strlen(command);
		path_duplicate = strdup(path);
		path_token = strtok(path_duplicate, ":");

		while (path_token != NULL)
		{
			directory_len = strlen(path_token);
			file_path = malloc(sizeof(char *) + (directory_len + command_len + 2));
			strcpy(file_path, path_token);
			strcat(file_path, "/");
			strcat(file_path, command);
			strcat(file_path, "\0");

			if (stat(file_path, &buffer_holder) == 0)
			{
				free(path_duplicate);
				return (file_path);
			}
			else
			{
				free(file_path);
				path_token = strtok(NULL, ":");
			}
		}
		free(path_duplicate);

		if (stat(command, &buffer_holder))
		{
			return (command);
		}

		return (NULL);
	}
		return (NULL);
}
