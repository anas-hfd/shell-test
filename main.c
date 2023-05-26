#include "shell.h"

char **get_string(char *buffer, char *delim)
{
	char **arrays;
	char *arg;
	int argc = 0;

	arrays = malloc(sizeof(char *) * 1024);
	arg = strtok(buffer, delim);
	while (arg)
	{
		arrays[argc] = arg;
		arg = strtok(NULL, delim);
		argc++;
	}
	arrays[argc] = NULL;
	return (arrays);
}

int main(int ac, char **av, char **env)
{
	size_t buffer_size = 0;
	char **token, **array, *buffer = NULL,  *command;
	int status, nread;
	pid_t pid;
	(void) ac;
	(void) av;

	while (1)
	{
		write (1, "> ", 2);
		nread = getline(&buffer, &buffer_size, stdin);
		if (nread == -1)
		{
			free(buffer);
			exit (EXIT_SUCCESS);
		}
		buffer[nread - 1] = '\0';
		token = get_string(buffer, " \t\n");
		if (strcmp(token[0], "exit") == 0)
			exit(1);

		pid = fork();
		if (pid == 0)
		{
			array = malloc(sizeof(char *) * 1024);
			*array = buffer;
			execve(array[0], array, NULL);
			command = get_path(token[0]);
			if (command)
				execve(command, token, env);
			else
				printf("Command not found\n");
			exit(0);
		}
		else
			wait(&status);
	}
	return (0);
}
