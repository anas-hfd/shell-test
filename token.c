#include "shell.h"

/**
 * **str_wrd - splits a string into words. Repeat delimiters are ignored
 * @str: the input string
 * @d: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **str_wrd(char *str, char *d)
{
	int i, j, k, x, nwords = 0;
	char **c;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!_delimeter(str[i], d) && (_delimeter(str[i + 1], d) || !str[i + 1]))
			nwords++;

	if (nwords == 0)
		return (NULL);
	c = malloc((1 + nwords) * sizeof(char *));
	if (!c)
		return (NULL);
	for (i = 0, j = 0; j < nwords; j++)
	{
		while (_delimeter(str[i], d))
			i++;
		k = 0;
		while (!_delimeter(str[i + k], d) && str[i + k])
			k++;
		c[j] = malloc((k + 1) * sizeof(char));
		if (!c[j])
		{
			for (k = 0; k < j; k++)
				free(c[k]);
			free(c);
			return (NULL);
		}
		for (x = 0; x < k; x++)
			c[j][x] = str[i++];
		c[j][x] = 0;
	}
	c[j] = NULL;
	return (c);
}

/**
 * **str_wrd2 - splits a string into words
 * @str: the input string
 * @d: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **str_wrd2(char *str, char d)
{
	int i, j, k, x, nwords = 0;
	char **c;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != d && str[i + 1] == d) ||
		    (str[i] != d && !str[i + 1]) || str[i + 1] == d)
			nwords++;
	if (nwords == 0)
		return (NULL);
	c = malloc((1 + nwords) * sizeof(char *));
	if (!c)
		return (NULL);
	for (i = 0, j = 0; j < nwords; j++)
	{
		while (str[i] == d && str[i] != d)
			i++;
		k = 0;
		while (str[i + k] != d && str[i + k] && str[i + k] != d)
			k++;
		c[j] = malloc((k + 1) * sizeof(char));
		if (!c[j])
		{
			for (k = 0; k < j; k++)
				free(c[k]);
			free(c);
			return (NULL);
		}
		for (x = 0; x < k; x++)
			c[j][x] = str[i++];
		c[j][x] = 0;
	}
	c[j] = NULL;
	return (c);
}
