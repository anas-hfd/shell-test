#include "shell.h"

/**
 * listlen - length of  list
 * @h: pointer to first node
 * Return: size of list
 */
size_t listlen(const list_t *h)
{
	size_t len = 0;

	while (h)
	{
		h = h->next;
		len++;
	}
	return (len);
}

/**
 * list_strings - returns an array of strings of the list->str
 * @head: pointer to first node
 *
 * Return: array of strings
 */
char **list_strings(list_t *head)
{
	list_t *node = head;
	size_t s = listlen(head), j;
	char **strs;
	char *ptr;

	if (!head || !s)
		return (NULL);
	strs = malloc(sizeof(char *) * (s + 1));
	if (!strs)
		return (NULL);
	for (s = 0; node; node = node->next, s++)
	{
		ptr = malloc(_strlen(node->str) + 1);
		if (!ptr)
		{
			for (j = 0; j < s; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		ptr = _strcpy(ptr, node->str);
		strs[s] = ptr;
	}
	strs[s] = NULL;
	return (strs);
}


/**
 * printlist - prints all elements
 * @h: pointer to first node
 * Return: size of list
 */
size_t printlist(const list_t *h)
{
	size_t s = 0;

	while (h)
	{
		_puts(conv_num(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_putchar('\n');
		h = h->next;
		s++;
	}
	return (s);
}

/**
 * node_start - returns node whose string starts with
 * @node: pointer to list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 * Return: match node or null
 */
list_t *node_start(list_t *node, char *prefix, char c)
{
	char *n = NULL;

	while (node)
	{
		n = startswith(node->str, prefix);
		if (n && ((c == -1) || (*n == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * getnode_index - gets the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 * Return: index of node or -1
 */
ssize_t getnode_index(list_t *head, list_t *node)
{
	size_t s = 0;

	while (head)
	{
		if (head == node)
			return (s);
		head = head->next;
		s++;
	}
	return (-1);
}
