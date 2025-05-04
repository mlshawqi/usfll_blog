#include "../minishell.h"



void	init_cmd_in_out(t_cmd *cmd)
{
	if (!cmd->io_fds)
	{
		////////
		cmd->io_fds = malloc(sizeof *cmd->io_fds);
		if (!cmd->io_fds)
			return ;
		cmd->io_fds->infile = NULL;
		cmd->io_fds->outfile = NULL;
		cmd->io_fds->heredoc_delimiter = NULL;
		cmd->io_fds->heredoc_quotes = false;
		cmd->io_fds->fd_in = -1;
		cmd->io_fds->fd_out = -1;
		// cmd->io_fds->stdin_backup = -1;
		// cmd->io_fds->stdout_backup = -1;
	}
}

t_env *create_env_node(char *env_line)/////////////////ajout
{
    t_env *new_node;
    char *equal_sign;
    int name_len;

    new_node = malloc(sizeof(t_env));
    if (!new_node)
        return (NULL);
    equal_sign = ft_strchr(env_line, '=');
    if (!equal_sign)
    {
        free(new_node);
        return (NULL); // pas de "=" dans la ligne (rare)
    }
    name_len = equal_sign - env_line;
    new_node->name = ft_substr(env_line, 0, name_len);
    new_node->value = ft_strdup(equal_sign + 1);
    new_node->previous = NULL;
    new_node->next = NULL;
    return (new_node);
}

t_env *init_env_list(char **envp)///////////////////ajout
{
    t_env *head = NULL;
    t_env *current = NULL;
    t_env *new_node;
    int i = 0;

    while (envp[i])
    {
        new_node = create_env_node(envp[i]);
        if (!new_node)
            return (NULL);
        if (!head)
            head = new_node;
        else
        {
            current->next = new_node;
            new_node->previous = current;
        }
        current = new_node;
        i++;
    }
    return (head);
}

bool ft_initialise_env(t_data *data, char **env)
{
    data->env = NULL;
    data->export = NULL;
    copy_env(env, &data->env);
    if (!data->env)
        return (false);
    copy_env(env, &data->export);
    if (!data->export)
        return (false);
    return (true);
}


bool	ft_initialise_data(t_data *data, char **env)
{
	if (!ft_initialise_env(data, env))
	{
		print_command_error("Fatal", NULL,
			"Could not initialize environment", 1);
		return (false);
	}
	data->token = NULL;
	data->user_input = NULL;
	data->cmd = NULL;
	return (true);
}
