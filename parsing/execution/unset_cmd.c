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
            if(lst->name)
                free_str_null(&lst->name);
            lst->name = NULL;
            if(lst->value)
                free_str_null(&lst->value);
            lst->value = NULL;
            free(lst);
            lst = NULL;
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
                    print_cmd_error("unset", "invalid option", NULL);
                    return (2);
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
