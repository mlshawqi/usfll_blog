#include "minishell.h"

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

static int  invalid_numeric_input(char *str)
{
        int i;

        i = 0;
        while (str[i] == '\t' || str[i] == '\n' || str[i] == ' ')
		    i++;
	    if ((str[i] == '-' || str[i] == '+') && (ft_isdigit(str[i + 1]) == 1)) 
		    i++;
        while(str[i])
        {
            if(ft_isdigit(str[i]) == 1)
                i++;
            else
                break;
        }
        if(str[i] == '\0' || str[i] == '\t' || str[i] == '\n' || str[i] == ' ')
        {
            while (str[i] == '\t' || str[i] == '\n' || str[i] == ' ')
                i++;
        }
        if(str[i] != '\0')
            return (1);
        return (0);
}

static int      is_longlong(char *str)
{
        int i;
        int len;
        int sign;

        i = 0;
        len = 0;
        sign = 0;
        while(str[i])
        {
            if(str[i] == '-' || str[i] == '+')
                sign++;
            if(ft_isdigit(str[i]) == 1)
                len++;
            i++;
        }
        if(len > 19)
            return (-1);
        return (0);
}

int    exit_cmd(char **arg)
{
        printf("exit\n");
        if (!arg || !arg[0])
        {
            g_last_exit_code = 0;
            exit (0);
        }
        if (arg[1])
        {
            printf("minishell: exit: too many arguments\n");
            return (1);
        }
        if ((invalid_numeric_input(arg[0]) == 1) || (is_longlong(arg[0]) == -1))
        {
            printf("minishell: exit: %s: numeric argument required\n", arg[0]);
            g_last_exit_code = 2;
            exit (2);
        }
        g_last_exit_code = ft_atoi(arg[0]);
        exit (g_last_exit_code);
}
