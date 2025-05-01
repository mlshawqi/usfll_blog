#include "../minishell.h"

static int     ft_isoption(char *str)
{
    int i;

    i = 1;
    while(str[i] != '\0')
    {
        if(str[0] == '-' && str[i] == 'n')
            i++;
        else
            return (1);
    }
    return (0);
}

static void     print_echo(char **arg)
{
    int j;

    j = 0;
    while(arg[j])
    {
        printf("%s", arg[j]);
        j++;
        if(arg[j])
            printf(" ");
    }   
}

int    echo_cmd(char **arg)
{
    int hint;
    int j;

    j = 0;
    hint = 0;
    if(arg && arg[0])
    {
        while(arg[j])
        {
            if(ft_strlen(arg[j]) > 1 && ft_isoption(arg[j]) == 0)
            {
                j++;
                hint++;
            }
            else
                break;
        }
        print_echo(arg + j);
    }
    if(hint == 0)
        printf("\n");
    return (0);
}
