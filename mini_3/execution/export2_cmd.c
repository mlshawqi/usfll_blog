#include "../minishell.h"

int     appand_value(t_env *tmp, char *arg)
{
    char    *str;
    int     len;

    len = ft_strchr(arg, '+') - arg;
    while(tmp)
    {
        if(ft_strncmp(tmp->name, arg, len) == 0)
        {
            if(tmp->value)
            {
                str = tmp->value;
                tmp->value = ft_strjoin(str, (ft_strchr(arg, '=') + 1));
            }
            else
                tmp->value = ft_strdup(ft_strchr(arg, '=') + 1);
            free_str_null(&str);
            return (0);
        }
        tmp = tmp->next;         
    }
    return (-1);
}

void  export_var(t_env **lst, char *var)
{
    int     len;
    int     found;
    t_env   *tmp;

    found = 0;
    tmp = *lst;
    while(tmp)
    {
        if(ft_strncmp(tmp->name, var, (ft_strchr(var, '=') - var)) == 0)
        {
            len = ft_strlen(ft_strchr(var, '=') + 1);
            free_str_null(&tmp->value);
            tmp->value = malloc(sizeof(char) * len + 1);
            ft_strlcpy(tmp->value, ft_strchr(var, '=') + 1, len + 1); 
            found++;
            break;
        }
        tmp = tmp->next;
    }
    if(found == 0)
        ft_lstadd_back(lst, ft_lstnew(var));
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

static void    print_export(t_env *lst)
{
        while(lst != NULL)
        {
            if(lst->name)
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
            }
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
