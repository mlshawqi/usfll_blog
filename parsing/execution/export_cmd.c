#include "../minishell.h"

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

static int     appand_value(t_env *tmp, char *arg)
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
            free(str);
            return (0);
        }
        tmp = tmp->next;         
    }
    return (-1);
}
static t_env    *new_node(char *arg)
{
    t_env   *new;

    new = malloc(sizeof(t_env));
    if(!new)
        return NULL;
    ft_strlcpy(new->name, arg, (ft_strchr(arg, '+') - arg));
    new->value = ft_strdup(ft_strchr(arg, '=') + 1);
    new->next = NULL;
    new->previous = NULL;
    return (new);
}

static void     add_to_value(t_env **env, t_env **export, char *arg)
{
        if(appand_value(*env, arg) == -1)
            ft_lstadd_back(env, new_node(arg));
        if(appand_value(*export, arg) == -1)
                    ft_lstadd_back(export, new_node(arg));
}

static int     export_fun(t_env **env, t_env **export, char *arg, int hint)
{
    t_env   *new;;

    if(hint == 2)
        add_to_value(env, export, arg);
    else if(ft_strchr(arg, '=') != NULL)
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

static int     valide_name(char *arg)
{
        int i;

        i = 0;
        while(arg[i] != '=' && arg[i] != '\0')
        {
            if(ft_isdigit(arg[0]) == 1)
            {
                printf("minishell\nexport: not a valid identifier\n");
                return (-1);
            }
            while(ft_isalpha(arg[i]) == 1 || ft_isdigit(arg[i]) == 1)
                i++;
            if(arg[i] == '=' || arg[i] == '\0')
                return (0);
            else if(arg[i] == '+' && arg[i + 1] == '=')
                return (2);
            else
                return (-1);
        }
        return (0);
}

int    export_cmd(t_env **envrmnt, t_env **export, char **args)
{
    int     j;

    j = 0;
    if(!args || !args[0])
        sort_env(export);
    else
    {
        while(args[j])
        {
            if(args[j][0] == '-')
            {
                printf("export %s: invalid option\n", args[j]);
                if(j == 0) return (-1);
            }
            if(valide_name(args[j]) == -1)
                printf("minishell\n: export: '%s': not a valid identifier\n", args[j]);
            else
            {
                if(export_fun(envrmnt, export, args[j], valide_name(args[j])))
                    return (-1);
            }
            j++;           
        }
    }
    return (0);
}
