#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdbool.h>

extern int errno;
extern char **environ;
extern char *cmdline_copy;
extern char **argv;
extern int argc;
extern char *commandline;
extern char *prog;
extern int execution_count;

/**
 * struct builtin_s - defines builtin commands
 * @name: The name of the builtin command.
 * @f: A function pointer to the builtin command's function.
 */
typedef struct builtin_s
{
	char *name;
	int (*f)(char **argv, char **front);
} builtin_t;

int count_tokens(char *commandline);
void store_tokens(char *cmdline_copy, char **argv);
int execute_cmd(char **argv);
char *get_cmd_path(char *command);
void handle_env(void);
void handle_exit(void);
void print_error_to_stdout(void);

#endif /* end ifndef */
