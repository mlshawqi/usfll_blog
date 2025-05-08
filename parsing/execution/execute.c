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

void    handle_redirections(t_data *data, t_cmd *cmd)
{
        int     saved_stdout;
        int     saved_stdin;
        t_in_out_fds    *tmp;

        saved_stdin = dup(STDIN_FILENO);
        saved_stdout = dup(STDOUT_FILENO);
        tmp = cmd->io_fds;
        while(tmp)
        {
                if(tmp->fd != -1 && (tmp->type == REDIR_OUT 
                                || tmp->type == REDIR_APPEND))
                {
                        dup2(tmp->fd, STDOUT_FILENO);
                        close(tmp->fd);
                }
                else if(tmp->fd != -1 && (tmp->type == REDIR_IN 
                                || tmp->type == REDIR_HEREDOC))
                {
                        dup2(tmp->fd, STDIN_FILENO);
                        close(tmp->fd);
                }
                tmp = tmp->next;
        }
        if(run_builtin_if_exists(data, cmd) == 1)
                g_last_exit_code = ft_execve(data, cmd);
        dup2(saved_stdout, STDOUT_FILENO);
        dup2(saved_stdin, STDIN_FILENO);
        close(saved_stdout);
        close(saved_stdin);
}

int     init_or_count_pipes(t_cmd *cmd, int hint)
{
        int     npipe;

        npipe = 0;
        if(hint == 1)
        {
                cmd->pipex = malloc(sizeof(t_pipex));
                if(!cmd->pipex)
                        return (-1);
                ft_memset(cmd->pipex, 0, sizeof(t_pipex));
        }
        else
        {
                while(cmd)
                {
                        if(cmd->pipe_output)
                                npipe++;
                        cmd = cmd->next;
                }
        }
        return (npipe);
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
        data->env_arr = env_to_array(data->env);
        if(!data->env_arr)
                return (malloc_error("t_data env_array"));
        copy_env(data->env_arr , &data->export);
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
        return (0);
}


int	malloc_error(const char *context)
{
	if (context)
	{
		write(2, "warning: failed to allocate ", 28);
		write(2, context, strlen(context));
		write(2, "\n", 1);
	}
	else
		write(2, "warning: malloc failed\n", 15);
        g_last_exit_code = 1;
	return (1);
}

void    print_cmd_error(const char *cmd, const char *msg, char *option)
{
        write(2, cmd, strlen(cmd));
        write(2, ": ", 2);
        if(option)
        {
                write(2, option, strlen(option));
                write(2, ": ", 2);
        }
        write(2, msg, strlen(msg));
        write(2, "\n", 1);
}
















// t_cmd *tmp = data->cmd;
// while(tmp)
// {
//         printf("cmd %s\n", tmp->command);
//         if(tmp->io_fds)
//         {
//                 if(tmp->io_fds->infile)
//                         printf("infile %s\n", tmp->io_fds->infile);
//                 if(tmp->io_fds->outfile)
//                         printf("outfile %s\n", tmp->io_fds->outfile);
//                 if(tmp->io_fds->heredoc_delimiter)
//                         printf("heredoc_delimiter %s\n", tmp->io_fds->heredoc_delimiter);
//                 if(tmp->io_fds->fd_in)
//                         printf("in_fd %d\n", tmp->io_fds->fd_in);
//                 if(tmp->io_fds->fd_out)
//                         printf("out_fd %d\n", tmp->io_fds->fd_out);
//         }
//         tmp = tmp->next;
// }



/*
int    execute_with_pipes(t_data *data, int npipe)
{
        t_cmd   *tmp;
        int     pipefd[npipe][2];//0 read 1 write
        int     i;

        tmp = data->cmd;
        i = 0;
        while(i < npipe)
        {
                if(pipe(pipefd[i]) == -1)
                {
                        perror("pipe failed");
                        exit(110);
                }
                i++;
        }
        i = 0;
        while(tmp)
        {
                tmp->fork_pid = fork();
                if(tmp->fork_pid == 0)
                {
                        printf("command %s\n", tmp->command);
                        if(!tmp->prev)
                        {
                                printf("!tmp.prev\n");
                                close(pipefd[i][0]);
                                dup2(pipefd[i][1], STDOUT_FILENO);
                                run_builtin_if_exists(data, tmp->command, tmp->args);
                                close(pipefd[i][1]);
                                printf("!tmp.prev---\n");
                        }
                        else if(!tmp->next)
                        {
                                printf("!tmp.next\n");
                                close(pipefd[i - 1][1]);
                                dup2(pipefd[i - 1][0], STDIN_FILENO);
                                run_builtin_if_exists(data, tmp->command, tmp->args);
                                close(pipefd[i - 1][0]);
                                printf("!tmp.next---\n");
                        }
                        else
                        {
                                printf("next _ prev\n");
                                dup2(pipefd[i - 1][0], STDIN_FILENO);
                                dup2(pipefd[i][1], STDOUT_FILENO);
                                run_builtin_if_exists(data, tmp->command, tmp->args);
                                close(pipefd[i][1]);
                                close(pipefd[i][0]);
                                close(pipefd[i - 1][1]);
                                close(pipefd[i - 1][0]);
                                printf("next _ prev----\n");
                        }
                        for (int j = 0; j < npipe; j++)
                        {
                            close(pipefd[j][0]);
                            close(pipefd[j][1]);
                        }
                }
                else
                        waitpid(tmp->fork_pid, &tmp->status, 0);
                tmp = tmp->next;
                i++;
        }
        printf("-----finish here\n");
        for (int j = 0; j < npipe; j++)
        {
            close(pipefd[j][0]);
            close(pipefd[j][1]);
        }
        return (0);
}
*/




// int     pipefd[2];//0 read 1 write
// int     pid1;
// int     pid2;
// int     status;

// if(pipe(pipefd) == -1)
// {
//         printf("pipe fail\n");
//         exit (1);
// }
// pid1 = fork();
// if(pid1 == 0)
// {
//         close(pipefd[0]);
//         dup2(pipefd[1], STDOUT_FILENO);
//         printf("first child\n");
//         close(pipefd[1]);
// }
// pid2 = fork();
// if(pid2 == 0)
// {
//         close(pipefd[1]);
//         dup2(pipefd[0], STDIN_FILENO);
//         printf("second child\n");
//         close(pipefd[0]);        
// }





// cc main.c -lreadline
// int g_last_exit_code = 0;

// void    handle_sigint(int sig)
// {
//         (void)sig;
//         rl_redisplay();
//         printf("\nMinishell~$ ");
// }
// void    manage_exenv(t_data *data, char **env)
// {
//         data->envrmnt = NULL;
//         data->export= NULL;
//         copy_env(env, &data->envrmnt);
//         copy_env(env, &data->export);
// }

// int main(int argc, char **argv, char **env)
// {
//         char *input;
//         (void)argc;
//         (void)argv;
//         t_data  data;

//         manage_exenv(&data, env);
//         signal(SIGINT, handle_sigint);
//         while (1)
//         {
//                 input = readline("Minishell~$ ");
//                 if (input == NULL)
//                 {
//                     printf("exit\n");
//                     free(input);
//                     break;
//                 }
//                 if (*input) {
//                     add_history(input);
//                 }
//                 if(ft_strcmp(input, "mkdir") == 0)
//                 {
//                         char *args[] = {"mkdir", "folder", NULL};
//                         if (ft_execve(data.envrmnt, input, args) == -1)
//                                 break;
//                 }
//                 else
//                 {
//                         char *args[] = {"ls", NULL};
//                         if (ft_execve(data.envrmnt, input, args) == -1)
//                                 break;
//                 }
// ;
//                 free(input);
//         }
//         rl_clear_history();
//         ft_lstclear(&data.export);
//         ft_lstclear(&data.envrmnt);
//         return 0;
// }


