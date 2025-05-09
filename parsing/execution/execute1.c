#include "../minishell.h"

char    **env_to_array(t_env *env)
{
        int     i;
        char    **array;
        char    *tmp;

        i = 0;
        array = malloc(sizeof(char *) * (ft_lstsize(env) + 1));
        if (!array)
                return (NULL);
        while(env)
        {
                tmp = ft_strjoin(env->name, "=");
                if(!tmp)
                        return (free_string_array(array), NULL);
                array[i] = ft_strjoin(tmp, env->value);
                free_str_null(&tmp);
                if (!array[i])
                        return (free_string_array(array), NULL);
                env = env->next;
                i++;
        }
        array[i] = NULL;
        return (array);
}

int     init_env_arr(t_data *data)
{
        data->env_arr = env_to_array(data->env);
        if(!data->env_arr)
                return (malloc_error("t_data env_array"));
        copy_env(data->env_arr , &data->export);
        return (0);
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

int     dup_redirect(t_in_out_fds *redirect)
{
        if(redirect->fd != -1 && (redirect->type == REDIR_OUT 
                        || redirect->type == REDIR_APPEND))
        {
                if(dup2(redirect->fd, STDOUT_FILENO) == -1)
                {
                        print_cmd_error("minishell", strerror(errno), NULL);
                        g_last_exit_code = 1;
                        return (1);
                }
                close(redirect->fd);
        }
        else if(redirect->fd != -1 && (redirect->type == REDIR_IN 
                        || redirect->type == REDIR_HEREDOC))
        {
                if(dup2(redirect->fd, STDIN_FILENO) == -1)
                {
                        print_cmd_error("minishell", strerror(errno), NULL);
                        g_last_exit_code = 1;
                        return (1);
                }
                close(redirect->fd);
        }
        return (0);
}

