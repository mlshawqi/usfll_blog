#include "../minishell.h"

static void    unset_var(t_env **head, char *variable)
{
    t_env   *lst;

    lst = *head;
    while(lst)
    {
        if(ft_strcmp(lst->name, variable) == 0)
        {
            if(!lst->previous)
                *head = lst->next;
            else
                lst->previous->next = lst->next;
            if(lst->next)
                lst->next->previous = lst->previous;
            free(lst->name);
            free(lst->value);
            free(lst);
            break;
        }
        lst = lst->next;
    }
}

int    unset_cmd(t_env **env, t_env **export, char **args)
{
        int     j;

        j = 0;
        if(args && args[0])
        {
            while(args[j])
            {
                if(args[0][0] == '-')
                {
                    printf("unset : invalid option\n");
                    return (-1);
                }
                else
                {
                    unset_var(env, args[j]);
                    unset_var(export, args[j]);
                }
                j++;
            }
        }
        return (0);
}
