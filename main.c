#include "shell.h"

/**
 * main - write a unix command line interpreter
 *
 * Return: 0
 */

int main(void)
{
	size_t buffer_size = 0;
	char **token, **array, *arg, *buffer = NULL;
	int nread, status, argc;
	pid_t pid;

	while (1)
	{
		write(1, "$ ", 2);
		nread = getline(&buffer, &buffer_size, stdin);
		if (nread == EOF)
			exit(1);
		buffer[nread - 1] = '\0';
		/* exit status */
		if (strcmp(buffer, "exit") == 0)
			exit_shell();
		array = malloc(sizeof(char *) * 1024);
		*array = buffer;
		/* Tokenize the command line arguments */
		argc = 0;
		arg = strtok(buffer, " ");
		while (arg != NULL)
		{
			array[argc++] = arg;
			arg = strtok(NULL, " ");
		}
		array[argc] = NULL;
		pid = fork();
		if (pid == 0)
		{
			if (execve(array[0], array, NULL) == -1)
				perror("Command not found");
				exit(1);
		}
		else
			wait(&status);
		free(array);
	}
	token = splitter(buffer);
	exit_shell();
	return (0);
}
