#include "../minishell.h"

void	free_in_out(t_in_out_fds *io)
{
	t_in_out_fds *tmp;

	tmp = io;
	while(tmp)
	{
		if (tmp->heredoc_delimiter)
		{
			unlink(tmp->filename);
			free_str_null(&tmp->heredoc_delimiter);
		}
		if (tmp->filename)
			free_str_null(&tmp->filename);
		if (tmp->fd != -1)
		{
			close(tmp->fd);
			tmp->fd = -1;
		}
		tmp = tmp->next;
	}
	free(tmp);
}

void	free_string_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	if (array)
	{
		while (array[i])
		{
			if (array[i])
			{
				free_str_null(&array[i]);
				array[i] = NULL;
			}
			i++;
		}
		free(array);
		array = NULL;
	}
}

void	close_files_descriptors(t_cmd *cmds, bool should_close)
{
	t_in_out_fds	*tmp;

	if (cmds->io_fds)
	{
		tmp = cmds->io_fds;
		while(tmp)
		{
			if (tmp->fd != -1)
			{
				close(tmp->fd);
				tmp->fd = -1;
			}
			tmp = tmp->next;
		}
	}
}

void	free_env_list(t_env **list)
{
	t_env *p;

	
	if (list == NULL || *list == NULL)
		return ;
	while (*list != NULL)
	{
		p = (*list)->next;
		if((*list)->name)
		{
			free((*list)->name);
			(*list)->name = NULL;
		}
		if((*list)->value)
		{
			free((*list)->value);
			(*list)->value = NULL;
		}
		free(*list);
		*list = p;
	}
	*list = NULL;
}

void free_env_array(char **env_arr)
{
    int i;

    if (!env_arr)
        return;

    i = 0;
    while (env_arr[i])
    {
        free_str_null(&env_arr[i]);
        env_arr[i] = NULL;
        i++;
    }
    free(env_arr);
}
void	execution_cleanup(t_data *data)
{
	if(data->export)
	{
		free_env_list(&data->export);
		data->export = NULL;
	}
	if(data->env_arr)
	{
		free_string_array(data->env_arr);
		data->env_arr = NULL;
	}
}

void	cleanup_shell_data(t_data *data, bool clear_history)
{
	if (!data)
		return ;
	free_str_null(&data->user_input);
	data->user_input = NULL;
	execution_cleanup(data);
	clear_token_list(&data->token, &free_str);
	free_command_list(&data->cmd, &free_str);
	if (clear_history)
	{
		if(data->cmd)
			free_str_null(&data->pwd);
		free_env_list(&data->env);
		rl_clear_history();
	}
}
