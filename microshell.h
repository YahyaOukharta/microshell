#ifndef __MICROSHELL_H__
# define __MICROSHELL_H__
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

// Parsing 
int         count_tokens(char **cmd, int index, char *next_token);
int         get_next_command(char ***cmd, char **argv, char *next_token);

// Execution
void        redirect_io(int in, int out);
void        set_io(int *in, int *out, char next, char last, int *fd);
int         execute_command(char **args, int in, int out);
int         builtin_cd(char **args);

// Utils
void        ft_putstr_fd(char *str, int fd);
int         tab_len(char **tab);

# endif