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
int handle_args(int ac, char **av);
/*task 4*/
void exit_shell();

/* ---------- */

#endif
