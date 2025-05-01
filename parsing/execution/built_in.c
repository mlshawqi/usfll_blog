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
