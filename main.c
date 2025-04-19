#include "minishell.h"

// cc main.c -lreadline


void    copy_env(char **env, t_env **list, char hint)
{
    int i;

    i = 0;
    while(env[i])
    {
        link_node(list, env[i], hint);
        i++;
    }
}

// void    handle_sigint(int sig)
// {
//     rl_redisplay();
//     printf("\nMinishell~$ ");
// }

int	ft_lstsize(t_env *lst)
{
	int		len;
	t_env	*tmp;

	if (!lst)
		return (0);
	len = 0;
	tmp = lst;
	while (tmp != NULL)
	{
		tmp = tmp->next;
		len++;
	}
	return (len);
}

void    sort_env(t_env *env)
{
    t_env   *tmp;
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
                tmp = lst->next;
                lst->next = tmp->next;
                if (tmp->next)
                    tmp->next->previous = lst;
                
                tmp->previous = lst->previous;
                if (lst->previous)
                    lst->previous->next = tmp;
                else
                    env = tmp;
                tmp->next = lst;
                lst->previous = tmp;
            }
            else
                lst = lst->next;
        }
        len--;
    }
    env_cmd(env);
}
int main(int argc, char **argv, char **env)
{
        // char *input;
        (void)argc;
        (void)argv;
        t_env   *envrmnt;
        t_env   *envcpy;

        envrmnt = NULL;
        envcpy = NULL;
        copy_env(env, &envrmnt, 'r');
        copy_env(env, &envcpy, 'c');
        sort_env(envcpy);
        // printf("-----------------------------------------------\n");
        // env_cmd(envcpy);
        // env_cmd(envrmnt);

        // signal(SIGINT, handle_sigint);
        // while (1)
        // {
        //     input = readline("Minishell~$ ");
        //     if (input == NULL || (strcmp(input, "exit") == 0))
        //     {
        //         printf("exit\n");
        //         free(input);
        //         break;
        //     }
        //     if (*input) {
        //         add_history(input);
        //     }
        //     free(input);
        // }
        // rl_clear_history();
        return 0;
}


