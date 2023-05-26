#include "shell.h"

/**
 * _history - displays the history list
 * @inf: Structure containing potential arguments
 *  Return: Always 0
 */
int _history(inf_t *inf)
{
	print_list(inf->history);
	return (0);
}

/**
 * no_alias - unsets alias to string
 * @inf: parameter
 * @str: the string
 * Return: Always 0 on success, 1 on error
 */
int no_alias(inf_t *inf, char *str)
{
	char *a, b;
	int result;

	a = _strchr(str, '=');
	if (!a)
		return (1);
	b = *a;
	*a = 0;
	result = delete_node_at_index(&(inf->alias),
	get_node_index(inf->alias, node_starts_with(inf->alias, str, -1)));
	*a = b;
	return (result);
}

/**
 * set_alias - sets alias to string
 * @inf: parameter
 * @str: the string
 * Return: Always 0 on success, 1 on error
 */
int set_alias(inf_t *inf, char *str)
{
	char *c;

	c = _strchr(str, '=');
	if (!c)
		return (1);
	if (!*++c)
		return (unset_alias(inf, str));

	unset_alias(inf, str);
	return (add_node_end(&(inf->alias), str, 0) == NULL);
}

/**
 * print_alias - prints an alias
 * @node: the alias
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	char *b = NULL, *a = NULL;

	if (node)
	{
		b = _strchr(node->str, '=');
		for (a = node->str; a <= b; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(b + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _alias - the alias builtin
 * @inf: Structure containing potential arguments
 *  Return: Always 0
 */
int _alias(inf_t *inf)
{
	int i = 0;
	char *c = NULL;
	list_t *node = NULL;

	if (inf->argc == 1)
	{
		node = inf->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; inf->argv[i]; i++)
	{
		c = _strchr(inf->argv[i], '=');
		if (c)
			set_alias(inf, inf->argv[i]);
		else
			print_alias(node_starts_with(inf->alias, inf->argv[i], '='));
	}

	return (0);
}
