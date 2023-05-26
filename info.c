#include "shell.h"

/**
 * clearinfo - initializes inf_t struct
 * @inf: struct address
 * Return: void
 */
void clearinfo(inf_t *inf)
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

void setinfo(inf_t *inf, char **av)
{
	int x = 0;

	inf->fname = av[0];
	if (inf->arg)
	{
		inf->argv = strtow(inf->arg, " \t");
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

		replace_alias(inf);
		replace_vars(inf);
	}
}

/**
 * freeinfo - frees inf_t struct fields
 * @inf: struct address
 * @all: true if freeing all fields
 */
void freeinfo(inf_t *inf, int all)
{
	ffree(inf->argv);
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
			free_list(&(inf->env));
		}
		if (inf->history)
		{
			free_list(&(inf->history));
		}
		if (inf->alias)
		{
			free_list(&(inf->alias));
		}
		ffree(inf->environ);
		inf->environ = NULL;
		bfree((void **)inf->cmd_buf);
		if (inf->readfd > 2)
			close(inf->readfd);
		_putchar(BUF_FLUSH);
	}
}
