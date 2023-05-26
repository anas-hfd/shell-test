#include "shell.h"

/**
 * _env - prints the environment
 * @inf: Structure containing potential arguments
 * Return: Always 0
 */

int _env(inf_t *inf)
{
	print_list_str(inf->env);
	return (0);
}

/**
 * _getenvi - gets the value of an environ
 * @inf: Structure containing potential arguments
 * @name: env name
 * Return: the value
 */

char *_getenvi(inf_t *inf, const char *name)
{
	list_t *node = inf->env;
	char *c;

	while (node)
	{
		c = starts_with(node->str, name);
		if (c && *c)
			return (c);
		node = node->next;
	}
	return (NULL);
}

/**
 * _setenv - Initialize a new environment variable
 * @inf: Structure containing potential arguments
 *  Return: Always 0
 */

int _setenv(inf_t *inf)
{
	if (inf->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(inf, inf->argv[1], inf->argv[2]))
	{
		return (0);
	}
	return (1);
}

/**
 * _unsetenv - Remove an environment variable
 * @inf: Structure containing potential arguments
 *  Return: Always 0
 */

int _unsetenv(inf_t *inf)
{
	int x;

	if (inf->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (x = 1; x <= inf->argc; x++)
		_unsetenv(inf, inf->argv[i]);

	return (0);
}

/**
 * ppt_env_list - populates env linked list
 * @inf: Structure of arguments
 * Return: int 0
 */

int ppt_env_list(inf_t *inf)
{
	list_t *node = NULL;
	size_t x;

	for (x = 0; environ[x]; x++)
		add_node_end(&node, environ[x], 0);
	inf->env = node;
	return (0);
}
