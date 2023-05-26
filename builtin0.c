#include "shell.h"

/**
 * _exit - exits the shell
 * @inf: Structure containing potential arguments
 *  Return: (0) if inf.argv[0] != "exit"
 */

int _exit(inf_t *inf)
{
	int check;

	if (inf->argv[1])
	{
		check = _erratoi(inf->argv[1]);
		if (tcheck == -1)
		{
			inf->status = 2;
			print_error(inf, "Illegal number: ");
			_eputs(inf->argv[1]);
			_eputchar('\n');
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
int _cd(inf_t *inf)
{
	char *s, *dir, buffer[1024];
	int cdret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!inf->argv[1])
	{
		dir = _getenv(inf, "HOME=");
		if (!dir)
				chdir((dir = _getenv(inf, "PWD=")) ? dir : "/");
		else
			cdret = chdir(dir);
	}
	else if (_strcmp(inf->argv[1], "-") == 0)
	{
		if (!_getenv(inf, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(inf, "OLDPWD=")), _putchar('\n');
			chdir((dir = _getenv(inf, "OLDPWD=")) ? dir : "/");
	}
	else
		cdret = chdir(inf->argv[1]);
	if (cdret == -1)
	{
		print_error(inf, "can't cd to ");
		_eputs(inf->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(inf, "OLDPWD", _getenv(inf, "PWD="));
		_setenv(inf, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelp - changes the current directory of the process
 * @inf: Structure containing potential arguments.
 *  Return: Always 0
 */
int _myhelp(inf_t *inf)
{
	char **argums;

	argums = inf->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*argums);
	return (0);
}
