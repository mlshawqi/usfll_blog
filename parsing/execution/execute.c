#include "../minishell.h"

int     run_builtin_if_exists(t_data *data, char *command, char **args)
{
        if(ft_strcmp(command, "pwd") == 0)
                g_last_exit_code = pwd_cmd(args + 1);
        else if(ft_strcmp(command, "echo") == 0)
                g_last_exit_code = echo_cmd(args + 1);
        else if(ft_strcmp(command, "cd") == 0)
                g_last_exit_code = cd_cmd(args + 1, &data->env);
        else if(ft_strcmp(command, "env") == 0)
                g_last_exit_code = env_cmd(data->env, args + 1);
        else if(ft_strcmp(command, "exit") == 0)
                g_last_exit_code = exit_cmd(args + 1);
        else if(ft_strcmp(command, "export") == 0)
                g_last_exit_code = export_cmd(&data->env, &data->export, args + 1);
        else if(ft_strcmp(command, "unset") == 0)
                g_last_exit_code = unset_cmd(&data->env, &data->export, args + 1);
        else
                return (1);
        return (0);
}

void    handle_redirections(t_data *data, t_cmd *tmp)
{
        int     saved_stdout;
        int     saved_stdin;

        saved_stdin = dup(STDIN_FILENO);
        saved_stdout = dup(STDOUT_FILENO);
        if(tmp->io_fds->fd_out != -1)
        {
                dup2(tmp->io_fds->fd_out, STDOUT_FILENO);
                close(tmp->io_fds->fd_out);
        }
        if(tmp->io_fds->fd_in != -1)
        {
                dup2(tmp->io_fds->fd_in, STDIN_FILENO);
                close(tmp->io_fds->fd_in);
        }
        if(run_builtin_if_exists(data, tmp->command, tmp->args) == 1)
                g_last_exit_code = ft_execve(data);
        dup2(saved_stdout, STDOUT_FILENO);
        dup2(saved_stdin, STDIN_FILENO);
        close(saved_stdout);
        close(saved_stdin);
}

int    execute_with_pipes(t_data *data, int npipe)
{
        t_cmd   *tmp;
        int     **pipefd;//0 read 1 write
        int     i;

        signal(SIGINT, SIG_IGN);
        signal(SIGQUIT, SIG_IGN);
        tmp = data->cmd;
        pipefd = allocate_pipes(npipe);
        if(!pipefd)
                return (1);
        i = 0;
        while(tmp)
        {
                tmp->fork_pid = fork();
                if(tmp->fork_pid == 0)
                {
                        signal(SIGINT, SIG_DFL);
                        signal(SIGQUIT, SIG_DFL);
                        return (handle_child_process(data, tmp, pipefd, i, npipe));
                }
                tmp = tmp->next;
                i++;
        }
        close_pipes(pipefd, npipe);
        free_tab(pipefd, npipe);
        return(wait_for_all(data));
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

static int     sipmle_fork(t_data *data)
{
        t_cmd   *cmd1, *cmd2;
        int     pipefd[2];
        int     pid1, pid2;

        cmd1 = data->cmd;
        cmd2 = data->cmd->next;
        if(pipe(pipefd) == -1)
                perror("pipe");
        pid1 = fork();
        if(pid1 == 0)
        {
                // printf("execute in pid1 \n");
                close(pipefd[0]);
                dup2(pipefd[1], STDOUT_FILENO);
                close(pipefd[1]);
                char **env_arr = env_to_array(data->env);
                char *path = find_program_path(data->env, cmd1->command);
                if(run_builtin_if_exists(data, cmd1->command, cmd1->args) == 1)
                {
                        if(execve(path,  cmd1->args, env_arr) == -1)
                                perror("execve");
                }
                exit(EXIT_FAILURE);
        }
        pid2 = fork();
        if(pid2 == 0)
        {
                close(pipefd[1]);
                dup2(pipefd[0], STDIN_FILENO);
                close(pipefd[0]);
                char **env_arr = env_to_array(data->env);
                char *path = find_program_path(data->env, cmd2->command);
                if(run_builtin_if_exists(data, cmd2->command, cmd2->args) == 1)
                {
                        if(execve(path,  cmd2->args, env_arr) == -1)
                                perror("execve");
                }
                exit(EXIT_FAILURE);
        }
        else
        {
                close(pipefd[0]);
                close(pipefd[1]);
                waitpid(pid1, &cmd1->status, 0);
                waitpid(pid2, &cmd2->status, 0);
                if (WIFEXITED(cmd1->status)) return WEXITSTATUS(cmd1->status);
                if (WIFEXITED(cmd2->status)) return WEXITSTATUS(cmd2->status);
                // printf("pid1 exited with %d\n", WEXITSTATUS(cmd1->status));
                // printf("pid2 exited with %d\n", WEXITSTATUS(cmd2->status));
        }
        return (0);
}


void    execution(t_data *data)
{
        int     npipe;

        npipe = n_pipeline(data->cmd);
        if(!npipe)
        {
                if(!data->cmd->io_fds)
                {
                        if(run_builtin_if_exists(data, data->cmd->command, data->cmd->args) == 1)
                                g_last_exit_code = ft_execve(data);
                }
                else
                        handle_redirections(data, data->cmd);
        }
        else
                g_last_exit_code = sipmle_fork(data);
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


