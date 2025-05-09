#include "../minishell.h"

int     run_builtin_if_exists(t_data *data, t_cmd *cmd)
{
        if(ft_strcmp(cmd->command, "pwd") == 0)
                g_last_exit_code = pwd_cmd(data, cmd->args + 1);
        else if(ft_strcmp(cmd->command, "echo") == 0)
                g_last_exit_code = echo_cmd(cmd->args + 1);
        else if(ft_strcmp(cmd->command, "cd") == 0)
                g_last_exit_code = cd_cmd(cmd->args + 1, &data->env, data);
        else if(ft_strcmp(cmd->command, "env") == 0)
                g_last_exit_code = env_cmd(data->env, cmd->args + 1);
        else if(ft_strcmp(cmd->command, "exit") == 0)
                g_last_exit_code = exit_cmd(cmd->args + 1);
        else if(ft_strcmp(cmd->command, "export") == 0)
                g_last_exit_code = export_cmd(data, &data->env, &data->export, cmd->args + 1);
        else if(ft_strcmp(cmd->command, "unset") == 0)
                g_last_exit_code = unset_cmd(&data->env, &data->export, cmd->args + 1);
        else
                return (1);
        return (0);
}

int    handle_redirections(t_data *data, t_cmd *cmd)
{
        int     saved_stdout;
        int     saved_stdin;
        t_in_out_fds    *tmp;

        saved_stdin = dup(STDIN_FILENO);
        saved_stdout = dup(STDOUT_FILENO);
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
                        g_last_exit_code = ft_execve(data, cmd);
        }
        dup2(saved_stdout, STDOUT_FILENO);
        dup2(saved_stdin, STDIN_FILENO);
        close(saved_stdout);
        close(saved_stdin);
        return (0);
}

int    execute_with_pipes(t_data *data, int npipe)
{
        t_cmd   *tmp;
        int     **pipefd;//0 read 1 write
        int     i;

        tmp = data->cmd;
        pipefd = allocate_pipes(npipe);
        if(!pipefd)
                return (malloc_error("pipes[][]"));;
        i = 0;
        while(tmp)
        {
                if(init_or_count_pipes(tmp, 1) == -1)
                        return (malloc_error("t_pipex pipex"));;
                tmp->pipex->fork_pid = fork();
                if(tmp->pipex->fork_pid == 0)
                {
                        signal(SIGINT, SIG_DFL);       
                        exit (handle_child_process(data, tmp, pipefd, i, npipe));
                }
                tmp = tmp->next;
                i++;
        }
        close_pipes(pipefd, npipe);
        free_tab(pipefd, npipe);
        return(wait_for_all(data));
}

int    execution(t_data *data)
{
        int     npipe;

        npipe = init_or_count_pipes(data->cmd, 0);
        if(init_env_arr(data) != 0)
                return (1);
        if(!npipe)
        {
                if(init_or_count_pipes(data->cmd, 1) == -1)
                        return (malloc_error("t_pipex pipex"));
                if(!data->cmd->io_fds)
                {
                        if(run_builtin_if_exists(data, data->cmd) == 1)
                                g_last_exit_code = ft_execve(data, data->cmd);
                }
                else
                        handle_redirections(data, data->cmd);
        }
        else
                g_last_exit_code = execute_with_pipes(data, npipe);

        // display_pipeline_commands(data);
        return (0);
}
