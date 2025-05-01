#include "../minishell.h"

int    pwd_cmd(char **args)
{
        char *pwd;

        if(args && args[0])
        {
            if(args && (ft_strlen(args[0]) > 1) && args[0][0] == '-')
            {
                printf("pwd: [%s]: invalid option\n", args[0]);
                return (-1);
            }
        }
        pwd = getcwd(NULL, 0);
        if(!pwd)
        {
            perror("pwd");
            return (-1);
        }
        printf("%s\n", pwd);
        free(pwd);
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

int    env_cmd(t_env *lst, char **arg)
{
        if(arg && arg[0])
        {
            printf("env: usage: env [no options or arguments allowed]\n");
            return (-1);
        }
        while(lst != NULL)
        {
            printf("%s=%s\n", lst->name, lst->value);
            lst = lst->next;
        }
        return (0);
}


// void    exit_cmd()
// {
//     exit;
// }
