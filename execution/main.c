#include "minishell.h"

// cc main.c -lreadline
int g_last_exit_code = 0;

void    handle_sigint(int sig)
{
        (void)sig;
        rl_redisplay();
        printf("\nMinishell~$ ");
}
void    manage_exenv(t_data *data, char **env)
{
        data->envrmnt = NULL;
        data->export= NULL;
        copy_env(env, &data->envrmnt);
        copy_env(env, &data->export);
}

int main(int argc, char **argv, char **env)
{
        char *input;
        (void)argc;
        (void)argv;
        t_data  data;

        manage_exenv(&data, env);
        signal(SIGINT, handle_sigint);
        while (1)
        {
                input = readline("Minishell~$ ");
                if (input == NULL)
                {
                    printf("exit\n");
                    free(input);
                    break;
                }
                if (*input) {
                    add_history(input);
                }
                if(ft_strcmp(input, "mkdir") == 0)
                {
                        char *args[] = {"mkdir", "folder", NULL};
                        if (ft_execve(data.envrmnt, input, args) == -1)
                                break;
                }
                else
                {
                        char *args[] = {"ls", NULL};
                        if (ft_execve(data.envrmnt, input, args) == -1)
                                break;
                }
;
                free(input);
        }
        rl_clear_history();
        ft_lstclear(&data.export);
        ft_lstclear(&data.envrmnt);
        return 0;
}


