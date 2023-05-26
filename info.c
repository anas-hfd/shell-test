#include "shell.h"

/**
 * clearinfo - initializes inf_t struct
 * @inf: struct address
 * Return: void
 */
void clearinfo(info_t *inf)
{
	inf->arg = NULL;
	inf->argv = NULL;
	inf->path = NULL;
	inf->argc = 0;
}

/**
 * setinfo - initializes inf_t struct
 * @inf: struct address
 * @av: argument vector
 * Return: Void
 */

void setinfo(info_t *inf, char **av)
{
	int x = 0;

	inf->fname = av[0];
	if (inf->arg)
	{
		inf->argv = str_wrd(inf->arg, " \t");
		if (!inf->argv)
		{

			inf->argv = malloc(sizeof(char *) * 2);
			if (inf->argv)
			{
				inf->argv[0] = _strdup(inf->arg);
				inf->argv[1] = NULL;
			}
		}
		for (x = 0; inf->argv && inf->argv[x]; x++)
			;
		inf->argc = x;

		replacealias(inf);
		replacevars(inf);
	}
}

/**
 * freeinfo - frees inf_t struct fields
 * @inf: struct address
 * @all: true if freeing all fields
 */
void freeinfo(info_t *inf, int all)
{
	_free(inf->argv);
	inf->argv = NULL;
	inf->path = NULL;
	if (all)
	{
		if (!inf->cmd_buf)
		{
			free(inf->arg);
		}
		if (inf->env)
		{
			freelist(&(inf->env));
		}
		if (inf->history)
		{
			freelist(&(inf->history));
		}
		if (inf->alias)
		{
			freelist(&(inf->alias));
		}
		_free(inf->environ);
		inf->environ = NULL;
		free((void **)inf->cmd_buf);
		if (inf->readfd > 2)
			close(inf->readfd);
		_putchar(BUF_FLUSH);
	}
}
