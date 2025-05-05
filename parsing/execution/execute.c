#include "../minishell.h"

int     run_builtin_if_exists(t_data *data, t_cmd *cmd)
{
        if(ft_strcmp(cmd->command, "pwd") == 0)
                g_last_exit_code = pwd_cmd(cmd->args + 1);
        else if(ft_strcmp(cmd->command, "echo") == 0)
                g_last_exit_code = echo_cmd(cmd->args + 1);
        else if(ft_strcmp(cmd->command, "cd") == 0)
                g_last_exit_code = cd_cmd(cmd->args + 1, &data->env);
        else if(ft_strcmp(cmd->command, "env") == 0)
                g_last_exit_code = env_cmd(data->env, cmd->args + 1);
        else if(ft_strcmp(cmd->command, "exit") == 0)
                g_last_exit_code = exit_cmd(cmd->args + 1);
        else if(ft_strcmp(cmd->command, "export") == 0)
                g_last_exit_code = export_cmd(&data->env, &data->export, cmd->args + 1);
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

        saved_stdin = dup(STDIN_FILENO);
        saved_stdout = dup(STDOUT_FILENO);
        if(cmd->io_fds->fd_out != -1)
        {
                dup2(cmd->io_fds->fd_out, STDOUT_FILENO);
                close(cmd->io_fds->fd_out);
        }
        if(cmd->io_fds->fd_in != -1)
        {
                dup2(cmd->io_fds->fd_in, STDIN_FILENO);
                close(cmd->io_fds->fd_in);
        }
        if(run_builtin_if_exists(data, cmd) == 1)
                g_last_exit_code = ft_execve(data, cmd);
        dup2(saved_stdout, STDOUT_FILENO);
        dup2(saved_stdin, STDIN_FILENO);
        close(saved_stdout);
        close(saved_stdin);
}

int     n_pipeline(t_cmd *cmd)
{
        int     npipe;

        npipe = 0;
        while(cmd)
        {
                if(cmd->pipe_output)
                        npipe++;
                cmd = cmd->next;
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
                return (1);
        i = 0;
        while(tmp)
        {
                tmp->pipex = malloc(sizeof(t_pipex));
                if(!tmp->pipex)
                        return (-1);
                ft_memset(tmp->pipex, 0, sizeof(t_pipex));
                tmp->pipex->fork_pid = fork();
                // fprintf(stderr,"        --execute cmd on main %s\n", tmp->command);
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


static int     sipmle_fork(t_data *data)
{
        t_cmd   *cmd1, *cmd2;
        int     pipefd[2];;

        cmd1 = data->cmd;
        cmd2 = data->cmd->next;
        if(pipe(pipefd) == -1)
                perror("pipe");
        cmd1->pipex = malloc(sizeof(t_pipex));
        if(!cmd1->pipex)
                return (-1);
        ft_memset(cmd1->pipex, 0, sizeof(t_pipex));
        cmd1->pipex->fork_pid = fork();
        if(cmd1->pipex->fork_pid == 0)
        {
                // printf("execute in pid1 \n");
                signal(SIGINT, SIG_DFL);
                close(pipefd[0]);
                dup2(pipefd[1], STDOUT_FILENO);
                close(pipefd[1]);
                exit(execute_command(data, cmd1));
        }
        cmd2->pipex = malloc(sizeof(t_pipex));
        if(!cmd2->pipex)
                return (-1);
        ft_memset(cmd2->pipex, 0, sizeof(t_pipex));
        cmd2->pipex->fork_pid = fork();
        if(cmd2->pipex->fork_pid == 0)
        {
                signal(SIGINT, SIG_DFL);
                close(pipefd[1]);
                dup2(pipefd[0], STDIN_FILENO);
                close(pipefd[0]);
                exit(execute_command(data, cmd2));
        }
        else
        {
                close(pipefd[0]);
                close(pipefd[1]);
                waitpid(cmd2->pipex->fork_pid, &cmd2->pipex->status, 0);
                waitpid(cmd1->pipex->fork_pid, &cmd1->pipex->status, 0);
                if (WIFSIGNALED(cmd1->pipex->status) || WIFSIGNALED(cmd2->pipex->status))
                {
                        if (WTERMSIG(cmd1->pipex->status) == SIGINT || WTERMSIG(cmd2->pipex->status) == SIGINT)
                                write(1, "\n", 1);  // Clean newline on Ctrl+C
	                else if (WTERMSIG(cmd1->pipex->status) == SIGQUIT || WTERMSIG(cmd2->pipex->status) == SIGQUIT)
                                write(1, "Quit: 3\n", 8);  // Like bash behavior
                }
                if (WIFEXITED(cmd1->pipex->status)) return WEXITSTATUS(cmd1->pipex->status);
                if (WIFEXITED(cmd2->pipex->status)) return WEXITSTATUS(cmd2->pipex->status);
                // printf("pid1 exited with %d\n", WEXITSTATUS(cmd1->status));
                // printf("pid2 exited with %d\n", WEXITSTATUS(cmd2->status));
        }
        return (0);
}


void    execution(t_data *data)
{
        int     npipe;

        npipe = n_pipeline(data->cmd);
        data->env_arr = env_to_array(data->env);
        if(!npipe)
        {
                data->cmd->pipex = malloc(sizeof(t_pipex));
                if(!data->cmd->pipex)
                        return;
                ft_memset(data->cmd->pipex, 0, sizeof(t_pipex));
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
}















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


