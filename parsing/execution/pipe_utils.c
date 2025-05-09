#include "../minishell.h"

int     wait_for_all(t_data *data)
{
        t_cmd   *tmp;
        
        tmp = data->cmd;   
        while (tmp)
        {
                waitpid(tmp->pipex->fork_pid, &tmp->pipex->status, 0);
                if (WIFSIGNALED(tmp->pipex->status))
                {
                        if (WTERMSIG(tmp->pipex->status) == SIGINT)
                                write(1, "\n", 1);
                        else if (WTERMSIG(tmp->pipex->status) == SIGQUIT)
                                write(1, "Quit: 3\n", 8);
                }
                if (!tmp->next)
                {
                    if (WIFSIGNALED(tmp->pipex->status))
                        return  (128 + WTERMSIG(tmp->pipex->status));
                    else if (WIFEXITED(tmp->pipex->status))
                        return (WEXITSTATUS(tmp->pipex->status));
                }
                tmp = tmp->next;
        }
        return (0);
}

int    handle_pipe_redirections(t_data *data, t_cmd *cmd)
{
        t_in_out_fds    *tmp;

        tmp = cmd->io_fds;
        while(tmp)
        {
                if(dup_redirect(tmp) == 1)
                        return (1);
                tmp = tmp->next;
        }
        if(cmd->command)
        {
                if(run_builtin_if_exists(data, cmd) == 1)
                        g_last_exit_code = ft_execve_pipe(data, cmd);
        }
        return (0);
}

int    ft_execve_pipe(t_data *data, t_cmd *cmd)
{
        cmd->pipex->path = find_program_path(data->env, cmd->command);
        if(!cmd->pipex->path)
                return (g_last_exit_code);
        if(execve(cmd->pipex->path,  cmd->args, data->env_arr) == -1)
                perror("execve");
        return (EXIT_FAILURE);       
}


int    execute_command(t_data *data, t_cmd *cmd)
{
        int status;
        if(!cmd->io_fds)
        {
                if(cmd->command)
                {
                        if(run_builtin_if_exists(data, cmd) == 1)
                                return (ft_execve_pipe(data, cmd));
                }
        }
        else if(cmd->io_fds)
                handle_pipe_redirections(data, cmd);
        return (g_last_exit_code);
}

int    handle_child_process(t_data *data, t_cmd *cmd, int **pipes, int i, int count)
{
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
