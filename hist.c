#include "shell.h"


/**
 * get_hist - gets the history file
 * @info: parameter struct
 * Return: history file
 */

char *get_hist(info_t *info)
{
	char *buff, *dirc;

	dirc = _getenviron(info, "HOME=");
	if (!dirc)
		return (NULL);
	buff = malloc(sizeof(char) * (_strlen(dirc) + _strlen(HIST_FILE) + 2));
	if (!buff)
		return (NULL);
	buff[0] = 0;
	_strcpy(buff, dirc);
	_strcat(buff, "/");
	_strcat(buff, HIST_FILE);
	return (buff);
}


/**
 * write_hist - creates a file hist
 * @info: the parameter struct
 * Return: 1 on success, else -1
 */

int write_hist(info_t *info)
{
	ssize_t fd;
	char *name = get_hist(info);
	list_t *node = NULL;

	if (!name)
		return (-1);

	fd = open(name, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(name);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}


/**
 * read_hist - reads history from file
 * @info: the parameter struct
 * Return: histcount on success, 0 otherwise
 */

int read_hist(info_t *info)
{
	int i, last = 0, count = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *name = get_hist(info);

	if (!name)
		return (0);

	fd = open(name, O_RDONLY);
	free(name);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			build_hist(info, buf + last, count++);
			last = i + 1;
		}
	if (last != i)
		build_hist(info, buf + last, count++);
	free(buf);
	info->histcount = count;
	while (info->histcount-- >= HIST_MAX)
		deletenode_index(&(info->history), 0);
	renumber_hist(info);
	return (info->histcount);
}


/**
 * build_hist - adds entry to a history list
 * @info: Structure containing potential arguments
 * @buf: buffer
 * @linecount: the history linecount, histcount
 * Return: Always 0
 */

int build_hist(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
	{
		node = info->history;
	}
	node_end(&node, buf, linecount);

	if (!info->history)
	{
		info->history = node;
	}
	return (0);
}


/**
 * renumber_hist - renumbers the history list after changes
 * @info: Structure containing potential arguments
 * Return: the new histcount
 */

int renumber_hist(info_t *info)
{
	list_t *node = info->history;
	int ind = 0;

	while (node)
	{
		node->num = ind++;
		node = node->next;
	}
	return (info->histcount = ind);
}
