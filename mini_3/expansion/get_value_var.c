#include "../minishell.h"


static int does_var_exist(t_env *env, char *var)
{
    while (env)
    {
        if (ft_strcmp(env->name, var) == 0)
            return (0);
        env = env->next;
    }
    return (1);
}

static char *find_env_var(t_env *env, char *var)
{
    while (env)
    {
        if (ft_strcmp(env->name, var) == 0)
            return (ft_strdup(env->value));
        env = env->next;
    }
    return (NULL);
}

char *get_value(t_separation *token, char *str, t_env *env_list)
{
    char *value;
    char *var;

    var = extract_variable(str);
    if (var && does_var_exist(env_list, var) == 0)
    {
        if (token != NULL)
            token->is_var = true;
        value = find_env_var(env_list, var);
    }
    else if (var && ft_strcmp(var, "?") == 0)
        value = ft_itoa(g_last_exit_code);
    else
        value = NULL;
    free_str(var);
    return (value);
}


