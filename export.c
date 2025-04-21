#include "minishell.h"

void    copy_env(char **env, t_env **list, t_env *envr, char hint)
{
    int i;

    i = 0;
    if(hint == 'c')
    {
        while(envr != NULL)
        {
            link_node(list, envr->line, hint);
            envr = envr->next;
        }
    }
    else
    {
        while(env[i])
        {
            link_node(list, env[i], hint);
            i++;
        }
    }
}

void    swap_nodes(t_env *lst, t_env **env)
{
    t_env   *tmp;

    tmp = lst->next;
    lst->next = tmp->next;
    if (tmp->next)
        tmp->next->previous = lst;
    tmp->previous = lst->previous;
    if (lst->previous)
        lst->previous->next = tmp;
    else
        *env = tmp;
    tmp->next = lst;
    lst->previous = tmp;
}

void    sort_env(t_env *env)
{
    t_env   *lst;
    int len;

    len = ft_lstsize(env);
    while(len)
    {
        lst = env;
        while(lst->next != NULL)
        {
            if(lst->next && (ft_strcmp(lst->line, lst->next->line) > 0))
            {
                swap_nodes(lst, &env);
            }
            else
                lst = lst->next;
        }
        len--;
    }
    env_cmd(env);
}

int names_match(char *v1, char *v2)
{
    char *equal1;
    char *equal2;
    size_t len1;
    size_t len2;
    
    equal2 = strchr(v2, '=');
    equal1 = strchr(v1, '=');
    if (!equal1 || !equal2)
        return 1;

    len1 = equal1 - v1;
    len2 = equal2 - v2;

    if (len1 != len2)
        return 1;

    return (ft_strncmp(v1, v2, len1));
}

int     ft_same_variable(t_env *lst, char *value)
{
    int     is_variable;

    is_variable = 0;
    while(lst)
    {
        if(names_match(lst->line, value) != 1)
        {
            free(lst->line);
            lst->line = ft_strdup(value);
            is_variable++;
            break;
        }
        lst = lst->next;
    }
    if(is_variable == 0)
        return (-1);
    return (0);
}