#include "shell.h"

/**
 * _getenv - get the environment variable
 * @env_name: the name of the environment
 *
 * Return: the value for the env_name
 */

char *_getenv(const char *env_name)
{
	extern char **environ;
	char *key;
	int i = 0;

	while (environ)
	{
		key = strtok(environ[i], "=");
		if (strcmp(env_name, key) == 0)
			return (strtok(NULL, "\n"));
		i++;
	}
	return (NULL);
}

/**
 * get_path - handle the PATH
 *
 * @command: the input command
 * Return: 0
 */

char *get_path(char *command)
{
	char *path = _getenv("PATH");
	char *token;
	char *command_path;

	command_path = malloc(sizeof(char *) * 1024);
	token = strtok(path, ":");
	while (token != NULL)
	{
		strcpy(command_path, token);
		strcat(command_path, "/");
		strcat(command_path, command);
		if (access(command_path, X_OK) == 0)
			return (0);
		token = strtok(NULL, ":");
	}
	return (0);
}
