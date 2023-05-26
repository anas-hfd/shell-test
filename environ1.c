#include "shell.h"

/**
 * _environ - prints the environment
 * @inf: Structure containing potential arguments
 * Return: Always 0
 */

int _environ(info_t *inf)
{
	print_list(inf->env);
	return (0);
}

/**
 * _getenviron - gets the value of an environ
 * @inf: Structure containing potential arguments
 * @name: env name
 * Return: the value
 */

char *_getenviron(info_t *inf, const char *name)
{
	list_t *node = inf->env;
	char *c;

	while (node)
	{
		c = startswith(node->str, name);
		if (c && *c)
			return (c);
		node = node->next;
	}
	return (NULL);
}

/**
 * _setenviron - Initialize a new environment variable
 * @inf: Structure containing potential arguments
 *  Return: Always 0
 */

int _setenviron(info_t *inf)
{
	if (inf->argc != 3)
	{
		_errputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(inf, inf->argv[1], inf->argv[2]))
	{
		return (0);
	}
	return (1);
}

/**
 * _unsetenviron - Remove an environment variable
 * @inf: Structure containing potential arguments
 *  Return: Always 0
 */

int _unsetenviron(info_t *inf)
{
	int x;

	if (inf->argc == 1)
	{
		_errputs("Too few arguements.\n");
		return (1);
	}
	for (x = 1; x <= inf->argc; x++)
		_unsetenv(inf, inf->argv[x]);

	return (0);
}

/**
 * ppt_environ - populates env linked list
 * @inf: Structure of arguments
 * Return: int 0
 */

int ppt_environ(info_t *inf)
{
	list_t *node = NULL;
	size_t x;

	for (x = 0; environ[x]; x++)
		node_end(&node, environ[x], 0);
	inf->env = node;
	return (0);
}
