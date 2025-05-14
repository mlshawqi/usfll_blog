#include "../minishell.h"

void    kill_all_child(t_data *data, char sig)
{
        t_cmd   *cmd;

        cmd = data->cmd;
        while(cmd)
        {
                // fprintf(stderr, "at least here in out kill_all_child\n");
                if(!WIFEXITED(cmd->pipex->status) && !WIFSIGNALED(cmd->pipex->status))
                {
                        // fprintf(stderr, "at least here inside kill_all_child\n");
                        if(sig == 'c')
                                kill(cmd->pipex->fork_pid, SIGINT);
                        else if(sig == 'q')
                                kill(cmd->pipex->fork_pid, SIGQUIT);
                }
                cmd = cmd->next;
        }
}

int     wait_for_all(t_data *data)
{
        t_cmd   *tmp;
        
        tmp = data->cmd; 
        while (tmp)
        {
                waitpid(tmp->pipex->fork_pid, &tmp->pipex->status, 0);
                if (!tmp->next)
                {
                        if(WIFEXITED(tmp->pipex->status))
                                g_last_exit_code = WEXITSTATUS(tmp->pipex->status);
                        return (g_last_exit_code);
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
                        ft_execve_pipe(data, cmd);
        }
        return (g_last_exit_code);
}

int    ft_execve_pipe(t_data *data, t_cmd *cmd)
{
        cmd->pipex->path = find_program_path(data->env, cmd->command);
        if(!cmd->pipex->path)
                return (g_last_exit_code);
        if(execve(cmd->pipex->path,  cmd->args, data->env_arr) == -1)
                perror("execve");
        print_cmd_error("here after execve", "---", NULL);
        return (EXIT_FAILURE);       
}


int    execute_command(t_data *data, t_cmd *cmd)
{
        // int status;
        if(!cmd->io_fds)
        {
                if(cmd->command)
                {
                        if(run_builtin_if_exists(data, cmd) == 1)
                        {
                                return (ft_execve_pipe(data, cmd));
                        }
                }
        }
        else if(cmd->io_fds)
                handle_pipe_redirections(data, cmd);
        // print_cmd_error("lst_g\n", g_last_exit_code, NULL);
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
