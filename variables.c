#include "shell.h"

/**
 * _chain - checks  if current char in buffer is a chain delimeter
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * Return: 1 if chain delimeter, 0 otherwise
 */
int _chain(info_t *info, char *buf, size_t *p)
{
	size_t s = *p;

	if (buf[s] == '|' && buf[s + 1] == '|')
	{
		buf[s] = 0;
		s++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[s] == '&' && buf[s + 1] == '&')
	{
		buf[s] = 0;
		s++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[s] == ';')
	{
		buf[s] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = s;
	return (1);
}

/**
 * checkchain - checks if we continue chaining based on last status
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 * Return: Void
 */
void checkchain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t s = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			s = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			s = len;
		}
	}

	*p = s;
}

/**
 * replacealias - replaces an aliases in the tokenized string
 * @info: the parameter struct
 * Return: 1 if replaced, 0 otherwise
 */
int replacealias(info_t *info)
{
	int ind;
	list_t *node;
	char *c;

	for (ind = 0; ind < 10; ind++)
	{
		node = node_start(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		c = _strchr(node->str, '=');
		if (!c)
			return (0);
		c = _strdup(c + 1);
		if (!c)
			return (0);
		info->argv[0] = c;
	}
	return (1);
}

/**
 * replacevars - replaces vars in the tokenized string
 * @info: the parameter struct
 * Return: 1 if replaced, 0 otherwise
 */
int replacevars(info_t *info)
{
	int ind = 0;
	list_t *node;

	for (ind = 0; info->argv[ind]; ind++)
	{
		if (info->argv[ind][0] != '$' || !info->argv[ind][1])
			continue;

		if (!_strcmp(info->argv[ind], "$?"))
		{
			replacestring(&(info->argv[ind]),
				_strdup(conv_num(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[ind], "$$"))
		{
			replacestring(&(info->argv[ind]),
				_strdup(conv_num(getpid(), 10, 0)));
			continue;
		}
		node = node_start(info->env, &info->argv[ind][1], '=');
		if (node)
		{
			replacestring(&(info->argv[ind]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replacestring(&info->argv[ind], _strdup(""));

	}
	return (0);
}

/**
 * replacestring - replaces string
 * @old: address of old string
 * @new: new string
 * Return: 1 if replaced, 0 otherwise
 */
int replacestring(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
