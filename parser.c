#include "microshell.h"

int count_tokens(char **cmd, int index, char *next_token)
{
    int n = 0;
    while (cmd[index])
    {
        if (!strcmp(cmd[index], "|") || !strcmp(cmd[index], ";"))
        {
            *next_token = cmd[index][0];
            break;
        }
        n++;
        index++;
    }
    if (!cmd[index] || !cmd[index + 1])
        *next_token = 'x';
    return (n);
}

int get_next_command(char ***cmd, char **argv, char *next_token)
{
    static int  index;
    int         n;
    char        **output;
    int         i;

    if(*next_token == 'x')
        return (0);
    if ((n = count_tokens(argv, index, next_token)) == 0)
        return (0);
    if (!(output = (char **)malloc(sizeof(char *) * (n + 1))))
        return (0);
    i = -1;
    while (++i < n)
        output[i] = argv[index + i];
    output[i] = 0;
    index += i + 1;
    cmd[0] = output;
    return (1);
}
