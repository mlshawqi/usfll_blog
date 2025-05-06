#include "../minishell.h"

int    pwd_cmd(t_data *data, char **args)
{
        char *cwd;

        if(args && args[0])
        {
            if(args && (ft_strlen(args[0]) > 1) && args[0][0] == '-')
            {
                printf("pwd: [%s]: invalid option\n", args[0]);
                return (2);
            }
        }
        cwd = getcwd(NULL, 0);
        if (cwd)
        {
            printf("%s\n", cwd);
            free_str(data->pwd);
            data->pwd = cwd;
        }
        else
        {
            if (data->pwd)
                printf("%s\n", data->pwd);
            else
                print_cmd_error("pwd", "getcwd failed"); return (1);
        }
        return (0);
}

int    env_cmd(t_env *lst, char **arg)
{
        if(arg && arg[0])
        {
            printf("env: usage: env [no options or arguments allowed]\n");
            return (2);
        }
        while(lst != NULL)
        {
            printf("%s=%s\n", lst->name, lst->value);
            lst = lst->next;
        }
        return (0);
}
