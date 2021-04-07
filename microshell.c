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
    i = 0;
    n = count_tokens(argv, index, next_token);
    if (n == 0)
        return (0);
    output = (char **)malloc(sizeof(char *) * (n + 1));
    while (i < n)
    {
        output[i] = argv[index + i];
        i++;
    }
    output[i] = 0; 
    index += i + 1;
    cmd[0] = output;
    return (1);
}

void    print_tab(char **tab)
{
    while (*tab)
    {
        printf("%s ", *tab);
        tab++;
    }
    printf("\n");
}

void    free_tab(char **tab)
{
    int i = 0;

    while (tab[i])
    {
        free(tab[i]);
        i++;
    }
    free(tab[i]);
    free(tab);
}
int main(int argc, char **argv)
{
    char **cmd;
    char next_token = 'e';

    while (get_next_command(&cmd, argv + 1, &next_token))
    {
        print_tab(cmd);
        printf("next token : %c\n", (next_token ? next_token : 'x'));
        free(cmd);
    }
    return (0);
} 