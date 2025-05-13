#include "../minishell.h"

int    pwd_cmd(t_data *data, char **args)
{
        char *cwd;

        if(args && args[0])
        {
            if(args && (ft_strlen(args[0]) > 1) && args[0][0] == '-')
            {
                print_cmd_error("minishell\npwd", "invalid option", args[0]);
                return (2);
            }
        }
        cwd = getcwd(NULL, 0);
        if (cwd)
        {
            printf("%s\n", cwd);
            if(data->pwd)
                free_str_null(&data->pwd);
            data->pwd = cwd;
        }
        else
        {
            if (data->pwd != NULL)
                printf("%s\n", data->pwd);
            else
            {
                print_cmd_error("pwd", "getcwd failed", NULL); return (1);
                return (1);
            }
        }
        return (0);
}


int    env_cmd(t_env *lst, char **arg)
{
        if(arg && arg[0])
        {
            print_cmd_error("minishell\nenv", "usage: env [no options or arguments allowed]", NULL);
            return (2);
        }
        while(lst != NULL)
        {
            if(lst->name && lst->value && (ft_strcmp(lst->name, "_") != 0))
            {
                printf("%s=%s\n", lst->name, lst->value);
            }
            lst = lst->next;
        }
        printf("_=/usr/bin/env\n");
        return (0);
}
