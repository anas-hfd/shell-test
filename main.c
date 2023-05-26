#include "shell.h"

<<<<<<< HEAD
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
=======
/**
 * main - entry point
 * @ac: argument count
 * @av: argument vector
 * Return: 0 on success, 1 on error
 */

int main(int ac, char **av)
{
	info_t info[] = { INFO_INIT };
	int i = 0, fd = 2;
>>>>>>> 5ed4b9caae0fa41097da182a64da5f6b9dad6e4a

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fd)
		: "r" (fd));

	if (ac == 2)
	{
<<<<<<< HEAD
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
=======
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
			{
				i++;
				exit(126);
			}
			if (errno == ENOENT)
			{
				i++;
				_errputs(av[0]);
				_errputs(": 0: Can't open ");
				_errputs(av[1]);
				_errputchar('\n');
				_errputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fd;
	}
	ppt_env_list(info);
	read_hist(info);
	hsh(info, av);
	return (EXIT_SUCCESS);
>>>>>>> 5ed4b9caae0fa41097da182a64da5f6b9dad6e4a
}
