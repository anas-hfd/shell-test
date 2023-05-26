#include "shell.h"

/**
 * input_buffer - buffers commands
 * @info: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 * Return: bytes read
 */
ssize_t input_buffer(info_t *info, char **buf, size_t *len)
{
	ssize_t s = 0;
	size_t length = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigHandler);
#if USE_GETLINE
		s = getline(buf, &length, stdin);
#else
		s = getline(buf, &length, info);
#endif
		if (s > 0)
		{
			if ((*buf)[s - 1] == '\n')
			{
				(*buf)[s - 1] = '\0';
				s--;
			}
			info->linecount_flag = 1;
			rm_comments(*buf);
			build_hist(info, *buf, info->histcount++);
			{
				*len = s;
				info->cmd_buf = buf;
			}
		}
	}
	return (s);
}

/**
 * get_inp - gets a line minus the newline
 * @info: parameter struct
 * Return: bytes
 */
ssize_t get_inp(info_t *info)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t j, k, len;
	ssize_t s = 0;
	char **buf_p = &(info->arg), *c;

	_putchar(BUF_FLUSH);
	s = input_buffer(info, &buf, &len);
	if (s == -1) /* EOF */
		return (-1);
	if (len)
	{
		j = k;
		c = buf + k;
		checkchain(info, buf, &j, k, len);
		while (j < len)
		{
			if (_chain(info, buf, &j))
				break;
			j++;
		}
		k = j + 1;
		if (k >= len)
		{
			k = len = 0;
			info->cmd_buf_type = CMD_NORM;
		}
		*buf_p = c;
		return (_strlen(c));
	}
	*buf_p = buf;
	return (s);
}

/**
 * read_buffer - reads a buffer
 * @info: parameter struct
 * @buf: buffer
 * @i: size
 * Return: buffer
 */

ssize_t read_buffer(info_t *info, char *buf, size_t *i)
{
	ssize_t s = 0;

	if (*i)
		return (0);
	s = read(info->readfd, buf, READ_BUF_SIZE);
	if (s >= 0)
		*i = s;
	return (s);
}

/**
 * _line - gets the next line of input
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 * Return: s
 */
int _line(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t ind, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (ind == len)
		ind = len = 0;

	r = read_buffer(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + ind, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + ind, k - ind);
	else
		_strncpy(new_p, buf + ind, k - ind + 1);

	s += k - ind;
	ind = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigHandler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void sigHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
