#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

/* global variable for the environment */
extern char **environ;

/* environment utilities */
int _printenv(void);
char *_getenv(char *var);

/*command path */
char *command_path(char *cmd);

/* shell functions and commands */
int command_read(char *s[]);
int execute(char *cmd_arr[]);

#endif
