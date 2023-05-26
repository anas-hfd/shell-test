#include "shell.h"

/**
 * _eratoi - converts a string to number
 * @s: the string to be converted
 * Return: int
 */
int _erratoi(char *s)
{
	int i = 0;
	unsigned long int res = 0;

	if (*s == '+')
	{
		s++;
	}
	for (i = 0;  s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			res *= 10;
			res += (s[i] - '0');
			if (res > INT_MAX)
			{
				return (-1);
			}
		}
		else
		{
			return (-1);
		}
	}
	return (res);
}

/**
 * print_error - prints an error message
 * @inf: the parameter & return inf struct
 * @estr: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void print_error(inf_t *inf, char *estr)
{
	_errputs(inf->fname);
	_errputs(": ");
	print_d(inf->line_count, STDERR_FILENO);
	_errputs(": ");
	_errputs(inf->argv[0]);
	_errputs(": ");
	_errputs(estr);
}

/**
 * dec_print - function prints a decimal
 * @input: the input
 * @fd: the file descriptor 
 * Return: number of characters printed
 */
int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int abs, curr;

	if (fd == STDERR_FILENO)
		__putchar = _errputchar;
	if (input < 0)
	{
		abs = -input;
		__putchar('-');
		count++;
	}
	else
		abs = input;
	current = abs;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (abs / i)
		{
			__putchar('0' + curr / i);
			count++;
		}
		curr %= i;
	}
	__putchar('0' + curr);
	count++;

	return (count);
}

/**
 * conv_num - converter function, a clone of itoa
 * @num: number
 * @base: base
 * @flags: argument flags
 * Return: char
 */
char *conv_num(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char signs = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		signs = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (signs)
		*--ptr = signs;
	return (ptr);
}

/**
 * rm_comments - removes the #
 * @buf: address of the string to modify
 * Return: Always 0;
 */
void rm_comments(char *buf)
{
	int x;

	for (x = 0; buf[x] != '\0'; x++)
		if (buf[x] == '#' && (!x || buf[i - x] == ' '))
		{
			buf[x] = '\0';
			break;
		}
}
