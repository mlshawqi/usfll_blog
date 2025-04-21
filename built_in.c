#include "minishell.h"

void    pwd_cmd()
{
        char *pwd;

        pwd = getcwd(NULL, 0);
        printf("pwd: %s\n", pwd);
}


void    echo_cmd(char *str)
{
        printf("%s", str);
}

void    cd_cmd(char *path)
{
    if(chdir(path) == -1)
        printf("cd fail\n");
}

void    env_cmd(t_env *lst)
{
        while(lst != NULL)
        {
            printf("%s\n", lst->line);
            lst = lst->next;
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
        if(ft_strncmp(lst->line, args, ft_strlen(args)) == 0)
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