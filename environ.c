#include "shell.h"

/**
 * _getenv - returns our environ
 * @inf: Structure containing potential arguments
 * Return: Always 0
 */

char **_getenv(inf_t *inf)
{
	if (!inf->environ || inf->env_changed)
	{
		inf->environ = list_to_strings(inf->env);
		inf->env_changed = 0;
	}

	return (inf->environ);
}

/**
 * _unsetenv - Remove an environment variable
 * @inf: Structure containing potential arguments
 *  Return: 1 on delete, 0 otherwise
 * @var: the string env var
 */
int _unsetenv(inf_t *inf, char *var)
{
	list_t *node = inf->env;
	size_t i = 0;
	char *c;

	if (!node || !var)
	{
		return (0);
	}

	while (node)
	{
		c = starts_with(node->str, var);
		if (c && *c == '=')
		{
			inf->env_changed = delete_node_at_index(&(inf->env), i);
			i = 0;
			node = inf->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (inf->env_changed);
}

/**
 * _setenv - Initialize a new environment variable
 * @inf: Structure containing potential arguments
 * @var: the string env var property
 * @value: the string env var value
 *  Return: Always 0
 */
int _setenv(inf_t *inf, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *c;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = inf->env;
	while (node)
	{
		c = starts_with(node->str, var);
		if (c && *c == '=')
		{
			free(node->str);
			node->str = buf;
			inf->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(inf->env), buf, 0);
	free(buf);
	inf->env_changed = 1;
	return (0);
}
