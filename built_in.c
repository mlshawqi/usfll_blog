#include "minishell.h"

void    pwd_cmd()
{
        char *pwd;

        pwd = getcwd(NULL, 0);
        printf("%s\n", pwd);
        free(pwd);
}


void    echo_cmd(char *str)
{
    printf("%s", str);
}
void    env_cmd(t_env *lst)
{
        while(lst != NULL)
        {
            printf("%s\n", lst->line);
            lst = lst->next;
        }
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
