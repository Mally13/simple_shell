#include "shell.h"
/**
 * get_cmd_path - Get command full path
 * @command: command argument
 * Return: Return the full path on success
 */
char *get_cmd_path(char *command)
{
	char *path = getenv("PATH"), *path_duplicate, *path_token, *file_path;
	int command_len, directory_len;
	struct stat buffer;

	if (path)
	{
		path_duplicate = strdup(path);
		path_token = strtok(path_duplicate, ":");
		while (path_token != NULL)
		{
			directory_len = strlen(path_token);
			command_len = strlen(command);
			file_path = malloc(directory_len + command_len + 2);
			if (!file_path)
			{
				free(path_duplicate);
				return (NULL);
			}
			strcpy(file_path, path_token);
			strcat(file_path, "/");
			strcat(file_path, command);
			if (stat(file_path, &buffer) == 0)
			{
				free(path_duplicate);
				return (file_path);
			}
			else
			{
				free(file_path);
				file_path = NULL;
				path_token = strtok(NULL, ":");
			}
		}
		free(path_duplicate);
	}
	if (stat(command, &buffer) == 0)
	{
		file_path = malloc(strlen(command) + 1);
		if (!file_path)
			return (NULL);
		strcpy(file_path, command);
		return (file_path);
	}
	free(file_path);
	return (NULL);
}
