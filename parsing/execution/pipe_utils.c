#include "../minishell.h"

void    free_tab(int **arr, int i)
{
        if(!arr)
                return ;
        while (i >= 0)
        {
                free(arr[i]);
                i--;
        }
        free(arr);
}

int     **allocate_pipes(int count)
{
        int     **arr;
        int     i;

        arr = ft_calloc(count, sizeof(int *));
        if(!arr)
                return (NULL);
        i = 0;
        while(i < count)
        {
                arr[i] = ft_calloc(2, sizeof(int));
                if(!arr[i])
                {
                        free_tab(arr, i - 1);
                        return (NULL);
                }
                if(pipe(arr[i]) == -1)
                {
                        free_tab(arr, i);
                        perror("pipe failed");
                        return (NULL);
                }
                i++;
        }
        return (arr);
}

void    close_pipes(int **pipes,int count)
{
        int     i;

        i = 0;
        while (i < count)
        {
                close(pipes[i][0]);
                close(pipes[i][1]);
                i++;
        }
}

int    execute_command(t_data *data, t_cmd *cmd)
{
        char **env_arr;
        char *path;

        if(run_builtin_if_exists(data, cmd->command, cmd->args) == 1)
        {
                printf("________here execve\n");
                env_arr = env_to_array(data->env);
                path = find_program_path(data->env, cmd->command);
                if(path == NULL)
                {
                        printf("%s: command not found\n", data->cmd->command);
                        return (127);
                }        
                if(execve(path,  cmd->args, env_arr) == -1)
                        perror("execve");
                return (EXIT_FAILURE);
        }
        return (EXIT_SUCCESS);
}

void    handle_sigint_pipe(int sig)
{
        (void)sig;
        rl_redisplay();
        printf("\nMinishell~$ ");
}

int     wait_for_all(t_data *data)
{
        t_cmd   *tmp;
        int last_status;
        
        tmp = data->cmd;
        last_status= 0;    
        while (tmp)
        {
                waitpid(tmp->fork_pid, &tmp->status, 0);
                if (tmp->next == NULL && WIFEXITED(tmp->status))
                        last_status = WEXITSTATUS(tmp->status);
                tmp = tmp->next;
        }
        signal(SIGINT, handle_sigint_pipe);
        signal(SIGQUIT, handle_sigint_pipe);
        return (last_status);
}

int    handle_child_process(t_data *data, t_cmd *cmd, int **pipes, int i, int count)
{
        printf("--------here chiled process cmd %s\n", cmd->command);
        if(!cmd->prev)
        {
                dup2(pipes[i][1], STDOUT_FILENO);
                close_pipes(pipes, count);
                return (execute_command(data, cmd));
        }
        else if(!cmd->next)
        {
                dup2(pipes[i - 1][0], STDIN_FILENO);
                close_pipes(pipes, count);
                return (execute_command(data, cmd));
        }
        else
        {
                dup2(pipes[i - 1][0], STDIN_FILENO);
                dup2(pipes[i][1], STDOUT_FILENO);
                close_pipes(pipes, count);
                return (execute_command(data, cmd));
        }
        return (0);
}
