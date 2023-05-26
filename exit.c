#include "shell.h"

/**
 **_strncpy - copies a string
 *@dest: destination string
 *@src: source string
 *@n: the amount of characters
 *Return: string
 */
char *_strncpy(char *dest, char *src, int n)
{
	int i, j;
	char *c = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (c);
}

/**
 **_strncat - concatenates two strings
 *@dest: first string
 *@src: second string
 *@n: num of bytes
 *Return: string
 */
char *_strncat(char *dest, char *src, int n)
{
	int k, j;
	char *c = dest;

	k = 0;
	j = 0;
	while (dest[k] != '\0')
	{
		k++;
	}
	while (src[j] != '\0' && j < n)
	{
		dest[k] = src[j];
		k++;
		j++;
	}
	if (j < n)
	{
		dest[k] = '\0';
	}
	return (c);
}

/**
 **_strchr - locates a character in a string
 *@s: string
 *@c: character
 *Return: char
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
		{
			return (s);
		}
	} while (*s++ != '\0');

	return (NULL);
}
