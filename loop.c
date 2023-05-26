#include "shell.h"

/**
 * _hsh - main shell loop
 * @info: the parameter & return info struct
 * @av: the argument vector from main()
 * Return: 0 on success, 1 on error, or error code
 */
int _hsh(info_t *info, char **av)
{
	ssize_t s = 0;
	int builtin_ret = 0;

	while (s != -1 && builtin_ret != -2)
	{
		clearinfo(info);
		if (interactive(info))
			_puts("$ ");
		_errputchar(BUF_FLUSH);
		s = get_inp(info);
		if (s != -1)
		{
			setinfo(info, av);
			builtin_ret = find_btin(info);
			if (builtin_ret == -1)
				findcmd(info);
		}
		else if (interactive(info))
			_putchar('\n');
		freeinfo(info, 0);
	}
	write_hist(info);
	freeinfo(info, 1);
	if (!interactive(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}

/**
 * find_btin - finds a builtin command
 * @info: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int find_btin(info_t *info)
{
	int ind, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _fexit},
		{"env", _environ},
		{"help", _help},
		{"history", get_hist},
		{"setenv", _setenviron},
		{"unsetenv", _unsetenviron},
		{"cd", _cd},
		{"alias", _alias},
		{NULL, NULL}
	};

	for (ind = 0; builtintbl[ind].type; ind++)
		if (_strcmp(info->argv[0], builtintbl[ind].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[ind].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * findcmd - finds a command in PATH
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void findcmd(info_t *info)
{
	char *p = NULL;
	int j, k;

	info->p = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (j = 0, k = 0; info->arg[j]; j++)
		if (!_delimeter(info->arg[j], " \t\n"))
			k++;
	if (!k)
		return;

	p = path_finder(info, _getenviron(info, "PATH="), info->argv[0]);
	if (p)
	{
		info->p = p;
		forkcmd(info);
	}
	else
	{
		if ((interactive(info) || _getenviron(info, "PATH=")
			|| info->argv[0][0] == '/') && _cmd(info, info->argv[0]))
			forkcmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * forkcmd - forks a an exec thread to run cmd
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void forkcmd(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, _getenviron(info)) == -1)
		{
			freeinfo(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}
