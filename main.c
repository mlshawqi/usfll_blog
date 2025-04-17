#include "minishell.h"

// cc main.c -lreadline


void    copy_env(char **env, t_env **list)
{
    int i;

    i = 0;
    while(env[i])
    {
        link_node(list, env[i]);
        i++;
    }
}

// void    handle_sigint(int sig)
// {
//     rl_redisplay();
//     printf("\nMinishell~$ ");
// }

int main(int argc, char **argv, char **env)
{
        char *input;
        t_env   *envrmnt;

        envrmnt = NULL;
        copy_env(env, &envrmnt);
        env_cmd(envrmnt);

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



char    *