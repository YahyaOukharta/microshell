#include "microshell.h"

extern char **environ;

void redirect_io(int in, int out)
{
    if (in != 0)
    {
        dup2(in, 0);
        close(in);
    }
    if (out != 1)
        dup2(out, 1);
}

void ft_putstr_fd(char *str, int fd)
{
    while (*str)
        write(fd, str++, 1);
}

int execute_command(char **args, int in, int out)
{
    int pid;
    int status;

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
    *out = (next == '|' ? fd[1] : 1);
    *in = (last == '|' ? fd[0] : 0);
}

int main(int argc, char **argv)
{
    char    **cmd;
    char    next_token,last_token = 'h';
    int     fd[2];
    int     in,out;
    int     status;

    (void)argc;
    pipe(fd);
    while (get_next_command(&cmd, argv + 1, &next_token))
    {
        set_io(&in ,&out, next_token, last_token, fd);
        status = execute_command(cmd, in, out);
        if (out != 1)
            close(out);
        last_token = next_token;
        free(cmd);
    }
    return (status);
} 
