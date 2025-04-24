#include "minishell.h"

int    pwd_cmd(char **args)
{
        char *pwd;

        if(args[0] && (ft_strlen(args[0]) > 1) && args[0][0] == '-')
        {
            printf("pwd: [%s]: invalid option\n", args[0]);
            return (-1);
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

int    echo_cmd(char **arg)
{
    int hint;
    int j;

    j = 0;
    hint = 0;
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
    while(arg[j])
    {
        printf("%s", arg[j]);
        j++;
        if(arg[j])
            printf(" ");
    }
    if(hint == 0)
        printf("\n");
    return (0);
}
int    env_cmd(t_env *lst, char **arg)
{
        if(arg)
        {
            printf("env: usage: env [no options or arguments allowed]\n");
            return (-1);
        }
        while(lst != NULL)
        {
            printf("%s\n", lst->line);
            lst = lst->next;
        }
        return (0);
}

void    cd_cmd(char *path, t_env **env)
{
    char    *old;

    old = getcwd(NULL, 0);
    if(!old)
        perror(NULL);
    if(chdir(path) == -1)
        perror("cd");
    else
    {
        update_pwd(env, old, 'O');
            free(old);
        old = getcwd(NULL, 0);
        if(!old)
            perror(NULL);
        update_pwd(env, old, 'P');
        free(old);
    } 
}


void    export_cmd(t_env **envrmnt, char *value)
{
    t_env   *envcpy;
    t_env   *tmp;

    if(!value)
    {
        envcpy = NULL;
        copy_env(NULL, &envcpy, *envrmnt, 'c');
        sort_env(envcpy);
        ft_lstclear(&envcpy);
    }
    else
    {
        tmp = *envrmnt;
        while(tmp)
        {
            if(ft_strcmp(value, tmp->line) == 0)
                return;
            tmp = tmp->next;
        }
        if(ft_same_variable(*envrmnt, value) == -1)
            ft_lstadd_back(envrmnt, ft_lstnew(value, 'r'));
    }
}

void    unset_cmd(t_env **env, char *args)
{
    t_env   *lst;

    lst = *env;
    while(lst)
    {
        if(ft_strncmp(lst->line, args, ft_strlen(args)) == 0
            && ft_names(lst->line, args) == 0)
        {
            if(!lst->previous)
                *env = lst->next;
            else
                lst->previous->next = lst->next;
            if(lst->next)
                lst->next->previous = lst->previous;
            free(lst->line);
            free(lst);
            break;
        }
        lst = lst->next;
    }
}



// void    exit_cmd()
// {
//     exit;
// }
