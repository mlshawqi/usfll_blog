#include "../minishell.h"

static int  change_home(t_env *env)
{
    int is_foud;

    is_foud = 0;
    while(env)
    {
        if(ft_strcmp(env->name, "HOME") == 0)
        {
            if(chdir(env->value) == -1)
            {
                perror("cd");
                return (-1);
            }
            is_foud++;
            break;
        }
        env = env->next;
    }
    if(is_foud == 0)
    {
        printf("cd: HOME not set\n");
        return (-1);
    }
    return (0);
}

static void    update_pwd(t_env **env, char *path, char hint)
{
    t_env   *lst;

    lst = *env;
    while(lst)
    {
        if((hint == 'P' && (ft_strcmp(lst->name, "PWD") == 0)) 
            || (hint == 'O' && (ft_strcmp(lst->name, "OLDPWD") == 0)))
        {
                if(lst->value)
                    free_str_null(&lst->value);
                if(!path)
                    lst->value = ft_strdup("");
                else
                    lst->value = ft_strdup(path);
                break;
        }
        lst = lst->next;
    }
}

static int    update_pwd2(t_data *data, t_env **env)
{
        char    *pwd;
        char    *tmp;

        pwd = NULL;
        pwd = getcwd(NULL, 0);
        if(!pwd)
        {
            if (data->pwd)
                pwd = ft_strjoin(data->pwd, "/..");
            print_cmd_error("cd",
                "error retrieving current directory: "
                "getcwd: cannot access parent directories: "
                "No such file or directory", NULL);
        }
        update_pwd(env, pwd, 'P');
        if(data->pwd)
        {
                free_str_null(&data->pwd);
                data->pwd = ft_strdup(pwd);
        }
        if(pwd)
            free_str_null(&pwd);
        return (0);
}

int    cd_cmd(char **args, t_env **env, t_data *data)
{
    char    *old;

    old = getcwd(NULL, 0);
    if(!old && data->pwd)
            old = ft_strdup(data->pwd);
    update_pwd(env, old, 'O');
    if(old)
        free_str_null(&old);
    if((!args || !args[0]) || (ft_strcmp(args[0], "~") == 0 && !args[1]))
    {
        if(change_home(*env) == -1)
            return (2);
    }
    else if(args[1])
    {
        print_cmd_error("cd", "too many arguments", NULL);
        return (2);
    }
    else if(chdir(*args) == -1)
    {
        perror("cd");
        return (2);
    }
    update_pwd2(data, env);
    return (0);
}
