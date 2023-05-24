#include "shell.h"

/**
 * main - creates a simple shell
 *
 * Return: 0
 */

int main(void)
{
	size_t buffer_size = 0;
	char **array, *arg, *buffer = NULL, *command;
	int nread, status, argc;
	pid_t pid;

	while (1)
	{
		write(1, "$ ", 2);
		nread = getline(&buffer, &buffer_size, stdin);
		if (nread == EOF)
			exit(1);
		buffer[nread - 1] = '\0';
		if (strcmp(buffer, "exit") == 0)/* exit status */
			exit_shell();
		array = malloc(sizeof(char *) * 1024);
		argc = 0;/* Tokenize the command line arguments */
		arg = strtok(buffer, " ");
		while (arg != NULL)
		{
			array[argc++] = arg;
			arg = strtok(NULL, " ");
		}
		array[argc] = NULL;
		pid = fork();
		if (pid == 0)
		{/* Checks if the command exits in the PATH */
			command = get_path(array[0]);
			if (command)
				execve(array[0], array, NULL);
			else
				perror("Command not found");
			exit(1);
		}
		else
			wait(&status);
		free(array);
	}
	splitter(buffer);
	return (0);
}
