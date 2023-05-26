#include "shell.h"

/**
 * _exit - exits the shell
 * @inf: Structure containing potential arguments
 *  Return: (0) if inf.argv[0] != "exit"
 */

int _fexit(info_t *inf)
{
	int check;

	if (inf->argv[1])
	{
		check = _erratoi(inf->argv[1]);
		if (check == -1)
		{
			inf->status = 2;
			print_error(inf, "Illegal number: ");
			_errputs(inf->argv[1]);
			_errputchar('\n');
			return (1);
		}
		inf->err_num = _erratoi(inf->argv[1]);
		return (-2);
	}
	inf->err_num = -1;
	return (-2);
}

/**
 * _cd - changes the directory
 * @inf: Structure containing potential arguments
 *  Return: Always 0
 */
int _cd(info_t *inf)
{
	char *s, *dir, buffer[1024];
	int cdret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!inf->argv[1])
	{
		dir = _getenviron(inf, "HOME=");
		if (!dir)
			cdret = /* TODO: what should this be? */
				chdir((dir = _getenviron(inf, "PWD=")) ? dir : "/");
		else
			cdret = chdir(dir);
	}
	else if (_strcmp(inf->argv[1], "-") == 0)
	{
		if (!_getenviron(inf, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenviron(inf, "OLDPWD=")), _putchar('\n');
			chdir((dir = _getenviron(inf, "OLDPWD=")) ? dir : "/");
	}
	else
		cdret = chdir(inf->argv[1]);
	if (cdret == -1)
	{
		print_error(inf, "can't cd to ");
		_errputs(inf->argv[1]), _errputchar('\n');
	}
	else
	{
		_setenv(inf, "OLDPWD", _getenviron(inf, "PWD="));
		_setenv(inf, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _help - changes the current directory of the process
 * @inf: Structure containing potential arguments.
 *  Return: Always 0
 */
int _help(info_t *inf)
{
	char **args;

	args = inf->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*args);
	return (0);
}
