#include "../minishell.h"

void	free_in_out(t_in_out_fds *io)
{
	if (!io)
		return ;
	// redirecte_io(io);
	if (io->heredoc_delimiter)
	{
		unlink(io->infile);
		free_str(io->heredoc_delimiter);
	}
	if (io->infile)
		free_str(io->infile);
	if (io->outfile)
		free_str(io->outfile);
	free_str(io);
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
				free_str(array[i]);
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
	if (cmds->io_fds)
	{
		if (cmds->io_fds->fd_in != -1)
			close(cmds->io_fds->fd_in);
		if (cmds->io_fds->fd_out != -1)
			close(cmds->io_fds->fd_out);
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
        free(env_arr[i]);
        env_arr[i] = NULL;
        i++;
    }
    free(env_arr);
}

void	cleanup_shell_data(t_data *data, bool clear_history)
{
	if (!data)
		return ;
	free_str(data->user_input);
	data->user_input = NULL;
	free_env_list(&data->export);
	data->export = NULL;
	if(data->env_arr)
	{
		free_string_array(data->env_arr);
		data->env_arr = NULL;
	}
	clear_token_list(&data->token, &free_str);
	free_command_list(&data->cmd, &free_str);
	if (clear_history)
	{
		if(data->cmd)
			free_str(data->pwd);
		free_env_list(&data->env);
		rl_clear_history();
	}
}
