#include "microshell.h"

extern char **environ;

void redirect_io(int in, int out)
{
    if (in != 0)
    {
        dup2(in, 0);
    }
    if (out != 1)
    {
        dup2(out, 1);
        close(in);
    }
}

void ft_putstr_fd(char *str, int fd)
{
    while (*str)
        write(fd, str++, 1);
}

int execute_command(char **args, int in, int out)
{
    int pid;
    int status = MAX_INT;

    pid = fork();
    if (pid == 0)
    {
        redirect_io(in, out);
        if(execve(args[0],args, environ) == -1)
        {
            ft_putstr_fd("error: cannot execute ", 2);
            ft_putstr_fd(args[0], 2);
            ft_putstr_fd("\n", 2);
            exit(0);
        }
    }
    else
        pid = waitpid(pid, &status, WUNTRACED);
    return (status);
}

void set_io(int *in, int *out, char next, char last, int *fd)
{
    *in = (last == '|' ? fd[0] : 0);
    if (next == '|')
        pipe(fd);
    *out = (next == '|' ? fd[1] : 1);
}

int tab_len(char **tab)
{
    int i = 0;
    while (tab[i])
        i++;
    return (i);
}

int builtin_cd(char **args)
{
    if (tab_len(args) != 2)
        ft_putstr_fd("error: cd: bad arguments\n", 2);
    else if ((chdir(args[1])) == -1)
    {
        ft_putstr_fd("error: cd: cannot change directory to ", 2);
        ft_putstr_fd(args[1], 2);
        ft_putstr_fd("\n", 2);
    }
    return (0);
}

int main(int argc, char **argv)
{
    char    **cmd;
    char    next_token,last_token = 'h';
    int     fd[2];
    int     in,out;
    int     status;

    (void)argc;
    while (get_next_command(&cmd, argv + 1, &next_token))
    {
        set_io(&in ,&out, next_token, last_token, fd);
        if (!strcmp("cd", cmd[0]))
            status = builtin_cd(cmd);
        else
            status = execute_command(cmd, in, out);
        if (out != 1)
            close(out);
        if (in != 0)
            close(in);
        last_token = next_token;
        free(cmd);
    }
    return (status);
}
