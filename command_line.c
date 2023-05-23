#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

/**
 * main - write a unix command line interpreter
 *
 * Return: 0
 */

int main(void)
{
	char *buffer = NULL;
	size_t buffer_size = 0;
	char *token;
	char **array;
	int nread, status;
	pid_t pid;

	while (1)
	{
		write(1, "> ", 2);
		nread = getline(&buffer, &buffer_size, stdin);
		if (nread == EOF)
			exit(1);
		buffer[nread - 1] = '\0';
		array = malloc(sizeof(char *) * 1024);
		*array = buffer;

		pid = fork();
		if (pid == 0)
		{
			if (execve(array[0], array, NULL) == -1)
			{
				perror("Command not found");
				exit(1);
			}
		}
		else
			wait(&status);

		free(array);
	}

	return (0);
}
