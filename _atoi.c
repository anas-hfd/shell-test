#include "shell.h"

/**
 * interactive - checks if shell is interactive mode
 * @inf: struct address
 * Return: 1 if interactive, 0 otherwise
 */

int interactive(inf_t *inf)
{
	return (isatty(STDIN_FILENO) && inf->readfd <= 2);
}

/*-----------------------------*/

/**
 * _delimeter - checks if character is a delimeter
 * @c: the char to check
 * @delim: the delimeter string
 * Return: 1 if true, 0 if false
 */
int _delimeter(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 *_isalpha - checks alphabetic characters
 *@c: input
 *Return: 1 if c is alphabetic, 0 otherwise
 */

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_atoi - converts a string to number
 *@s: the string
 *Return: 0 if no numbers in string, converted number otherwise
 */

int _atoi(char *s)
{
	int i, sgn = 1, flag = 0, out;
	unsigned int result = 0;

	for (i = 0;  s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sgn *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
		{
			flag = 2;
		}
	}

	if (sgn == -1)
	{
		out = -result;
	}
	else
	{
		out = result;
	}

	return (out);
}
