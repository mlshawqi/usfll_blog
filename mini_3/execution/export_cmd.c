#include "../minishell.h"

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
                return (-1);
            }
            while(ft_isalpha(arg[i]) == 1 || ft_isdigit(arg[i]) == 1 || arg[i] == '_')
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

int    export_cmd(t_data *data, t_env **envrmnt, t_env **export, char **args)
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
                print_cmd_error("minishell\nexport", "invalid option", args[j]);
                if(j == 0) return (2);
            }
            if(valide_name(args[j]) == -1)
                print_cmd_error("minishell\nexport", "not a valid identifier", args[j]);
            else
            {
                if(export_fun(envrmnt, export, args[j], valide_name(args[j])))
                    return (2);
            }
            j++;           
        }
    }
    return (0);
}
