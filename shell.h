#ifndef SHELL_H
#define SHELL_H

/* libraries */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

/* ---------- */


/* functions */
/*task 2*/
char **splitter(char *str);
int handle_args(void);
/*task 3*/
char *get_path(char *command);
/*task 4*/
void exit_shell(void);
/*task 5*/
char *_getenv(const char *env_name);

/* ---------- */

#endif
