#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

typedef struct passinfo
{
	char *arg, *path, *fname;
	char **argv, **environ;
	unsigned int line_count;
	int linecount_flag, argc, status, env_changed, err_num;
	list_t *env;
	list_t *history;
	list_t *alias;

	char **cmd_buf;
	int cmd_buf_type, readfd, histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* loop.c */
int _hsh(info_t *info, char **av);
int find_btin(info_t *info);
void findcmd(info_t *info);
void forkcmd(info_t *info);

/* parser.c */
int _cmd(info_t *info, char *path);
char *duplicate_chars(char *pathstr, int start, int stop);
char *path_finder(info_t *info, char *pathstr, char *cmd);

/* loophsh.c */
int loophsh(char **);

/* errs0.c */
void _errputs(char *str);
int _errputchar(char c);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/* string0.c */
int _strlen(char *s);
int _strcmp(char *s1, char *s2);
char *startswith(const char *haystack, const char *needle);
char *_strcat(char *dest, char *src);

/* string1.c */
char *_strcpy(char *dest, char *src);
char *_strdup(const char *str);
void _puts(char *str);
int _putchar(char c);

/*exits.c */
char *_strncpy(char *dest, char *src, int n);
char *_strncat(char *dest, char *src, int n);
char *_strchr(char *s, char c);

/* token.c */
char **str_wrd(char *str, char *d);
char **str_wrd2(char *str, char d);

/* memoryset.c */
char *_memset(char *s, char b, unsigned int n);
void _free(char **pp);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);

/* mem.c */
int mfree(void **ptr);

/* _atoi.c */
int interactive(info_t *inf);
int _delimeter(char c, char *delim);
int _isalpha(int c);
int _atoi(char *s);

/* _errs1.c */
int _erratoi(char *s);
void print_error(info_t *inf, char *estr);
int dec_print(int input, int fd);
char *conv_num(long int num, int base, int flags);
void rm_comments(char *buf);

/* builtin0.c */
int _fexit(info_t *inf);
int _cd(info_t *inf);
int _help(info_t *inf);

/* _builtin1.c */
int _alias(info_t *inf);
int print_alias(list_t *node);
int set_alias(info_t *inf, char *str);
int no_alias(info_t *inf, char *str);
int _history(info_t *inf);
int _alias(info_t *inf);

/*line.c */
ssize_t input_buffer(info_t *info, char **buf, size_t *len);
ssize_t read_buffer(info_t *info, char *buf, size_t *i);
ssize_t get_inp(info_t *info);
int _line(info_t *info, char **ptr, size_t *length);
void sigHandler(__attribute__((unused))int sig_num);

/* info.c */
void clearinfo(info_t *inf);
void setinfo(info_t *inf, char **av);
void freeinfo(info_t *inf, int all);

/* environ1.c */
char *_getenviron(info_t *inf, const char *name);
int _environ(info_t *inf);
int _setenviron(info_t *inf);
int _unsetenviron(info_t *inf);
int ppt_environ(info_t *inf);

/* env.c */
char **get_env(info_t *inf);
int _unsetenv(info_t *inf, char *var);
int _setenv(info_t *inf, char *var, char *value);

/* hist.c */
char *get_hist(info_t *info);
int write_hist(info_t *info);
int read_hist(info_t *info);
int build_hist(info_t *info, char *buf, int linecount);
int renumber_hist(info_t *info);

/* lists0.c */
list_t *addnode(list_t **head, const char *str, int num);
list_t *node_end(list_t **head, const char *str, int num);
size_t print_list(const list_t *h);
int deletenode_index(list_t **head, unsigned int index);
void freelist(list_t **head_ptr);

/* lists1.c */
size_t listlen(const list_t *h);
char **list_strings(list_t *head);
size_t printlist(const list_t *h);
list_t *node_start(list_t *node, char *prefix, char c);
ssize_t getnode_index(list_t *head, list_t *node);

/* variables.c */
int _chain(info_t *info, char *buf, size_t *p);
void checkchain(info_t *info, char *buf, size_t *p, size_t i, size_t len);
int replacealias(info_t *info);
int replacevars(info_t *info);
int replacestring(char **old, char *new);

#endif
