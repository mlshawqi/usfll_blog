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

void free_env_list(t_env *env_list)////////////////ajout
{
    t_env *temp;

    while (env_list)
    {
        temp = env_list;
        env_list = env_list->next;
        // free_str(temp->key);   // Libère la clé (si allouée)
        free_str(temp->value); // Libère la valeur (si allouée)
        free(temp);            // Libère l'élément de la liste
    }
}

void	cleanup_shell_data(t_data *data, bool clear_history)
{
	if (!data)
		return ;
	free_str(data->user_input);
	data->user_input = NULL;
	clear_token_list(&data->token, &free_str);
	free_command_list(&data->cmd, &free_str);
	if (clear_history)
	{
		free_env_list(data->env);
		rl_clear_history();
	}
}
