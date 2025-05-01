#include "../minishell.h"

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

static void    print_export(t_env *lst)
{
        while(lst != NULL)
        {
            printf("declare -x ");
            printf("%s", lst->name);
            if(lst->value)
            {
                printf("=\"");
                printf("%s", lst->value);
                printf("\"");
            }
            printf("\n");
            lst = lst->next;
        }
}

void    sort_env(t_env **env)
{
    t_env   *lst;
    int len;

    len = ft_lstsize(*env);
    while(len)
    {
        lst = *env;
        while(lst->next != NULL)
        {
            if(lst->next && (ft_strcmp(lst->name, lst->next->name) > 0))
            {
                swap_nodes(lst, env);
            }
            else
                lst = lst->next;
        }
        len--;
    }
    print_export(*env);
}
