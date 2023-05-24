#include "shell.h"

/**
 * splitter - 2D ptr to func
 * @str: string arg
 * Return: string
 */

char **splitter(char *str)
{
	char **token = NULL, *tok;
	int i = 0;

	tok = strtok(str, " \t\n");
	while (tok != NULL)
	{
		i++;
		token = realloc(token, i * sizeof(char *));
		if (token == NULL)
		{
			perror("NULL");
			exit(EXIT_FAILURE);
		}
		else
		{
			token[i - 1] = tok;
			tok = strtok(NULL, " \t\n");
		}
	}
	return (token);
}

/* -------- splitter ------ */

/**
 * handle_args - handles the args passed to the main
 * @ac: args count (number of args)
 * @av: args vector (str of args)
 * Return: 0
 */

int handle_args(void)
{
	char *buffer;
	size_t size = 0;
	int chars = 0;

	buffer = NULL;
	chars = getline(&buffer, &size, stdin);
	if (chars == EOF)
	{
		perror("end of file");
	}
	else
	{
		buffer[chars - 1] = '\0';
		printf("%s\n", buffer);
	}
	return (0);
}

/* -------- handle_ args ------ */

/**
 * exit_shell - handles the exit status
 * Return: void
 */

void exit_shell(void)
{
	/* Terminate the program with exit status 0*/
	exit(0);
}

/* -------- exit_shell ------ */

