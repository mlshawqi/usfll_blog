#include "../minishell.h"

static t_env    *creat_node(char *name, char *value)
{
        t_env   *node;
        node = malloc(sizeof(t_env));
	if (!node)
		return (malloc_error("t_env"), NULL);
        ft_memset(node, 0, sizeof(t_env));
        if(name)
                node->name = ft_strdup(name);
        if(value)
                node->value = ft_strdup(value);
        return (node);
}

int	ft_atoi_env(const char *str)
{
	int	result;
	int		sign;
	int		i;

	result = 0;
	sign = 1;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			return (0);
		i++;
	}
        while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		if (result >= 1000)
			return (print_cmd_error("warning", "shell level (1001) too high, resetting to 1", NULL) , 0);
		i++;
	}
	return (result * sign);
}

void    set_shell_lvl(t_env *env)
{
        t_env   *tmp;
        int     nbr;

        tmp = env;
        while(tmp)
        {
                if (ft_strcmp(tmp->name, "SHLVL") == 0)
                {
                        if(tmp->value)
                        {
                                nbr = ft_atoi(tmp->value) + 1;
                                free(tmp->value);
                                tmp->value = ft_itoa(nbr);
                        }
                        break ;
                }
                tmp = tmp->next;
        }
}

void     init_env_defaults(t_data *data)
{
        char    *pwd;
        char    *path;

        pwd = getcwd(NULL, 0);
        if(!pwd)
                print_cmd_error("pwd", strerror(errno), NULL);
        link_node(&data->env, creat_node("PWD", pwd));
        link_node(&data->env, creat_node("SHLVL", "1"));
        path = ft_strdup("/home/machaouk/.local/bin"
                ":/usr/local/sbin:/usr/local/bin"
                ":/usr/sbin:/usr/bin:/sbin:/bin");
        link_node(&data->env, creat_node("PATH", path));
        link_node(&data->env, creat_node("OLDPWD", NULL));
}
