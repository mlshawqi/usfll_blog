#include "minishell.h"

// cc main.c -lreadline

void    handle_sigint(int sig)
{
        (void)sig;
        rl_redisplay();
        printf("\nMinishell~$ ");
}

int main(int argc, char **argv, char **env)
{
        // char *input;
        (void)argc;
        (void)argv;
        t_env   *envrmnt;
        t_env   *envcpy;

        envrmnt = NULL;
        envcpy= NULL;
        copy_env(env, &envrmnt);
        copy_env(env, &envcpy);
        ft_lstclear(&envrmnt);
        ft_lstclear(&envcpy);
        // signal(SIGINT, handle_sigint);
        // while (1)
        // {
        //     input = readline("Minishell~$ ");
        //     if (input == NULL)
        //     {
        //         printf("exit\n");
        //         free(input);
        //         break;
        //     }
        //     if (*input) {
        //         add_history(input);
        //     }
        //     assigned_lvar(&l_var, input);
        //     free(input);
        // }
        // rl_clear_history();
        return 0;
}


