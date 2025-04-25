#include "minishell.h"

static void  export_var(t_env **lst, char *var)
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
            free(tmp->value);
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

static int      export_exist(t_env *tmp, char *var)
{
    while(tmp)
    {
        if(ft_strcmp(tmp->name, var) == 0)
        {
            return (-1);
        }
        tmp = tmp->next;
    }
    return (0);
}

static int     export_fun(t_env **env, t_env **export, char *arg)
{
    t_env   *new;;

    if(ft_strchr(arg, '=') != NULL)
    {
        export_var(env, arg);
        export_var(export, arg);
    }
    else
    {
        if(export_exist(*export, arg) == 0)
        {
            new = malloc(sizeof(t_env));
            if(!new)
                return (-1);
            new->name = ft_strdup(arg);
            new->value = NULL;
            new->next = NULL;
            new->previous = NULL;
            ft_lstadd_back(export, new);
        }
    }
    return (0);
}

int    export_cmd(t_env **envrmnt, t_env **export, char **args)
{
    int     j;

    j = 0;
    if(!(*args))
        sort_env(export);
    else
    {
        while(args[j])
        {
            if(args[j][0] == '-')
            {
                printf("export %s: invalid option\n", args[j]);
                if(j == 0)
                    return (-1);
                j++;
                continue;
            }
            else
                if(export_fun(envrmnt, export, args[j])) return (-1);
            j++;           
        }
    }
    return (0);
}
