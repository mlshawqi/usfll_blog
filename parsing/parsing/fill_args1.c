#include "../minishell.h"

int	count_token_args(t_separation *node)
{
	int	count;

	count = 0;
	while (node && (node->type == WORD || node->type == VAR))
	{
		count++;
		node = node->next;
	}
	return (count);
}

int	initialize_default_args(t_separation **token_node, t_cmd *cmd)
{
	int				i;
	int				nb_args;
	t_separation	*temp;

	i = 0;
	temp = *token_node;
	nb_args = count_token_args(temp);
	cmd->args = malloc(sizeof(char *) * (nb_args + 2));
	if (!cmd->args)
		return (FAILURE);
	temp = *token_node;
	i = 0;
	cmd->args[i] = ft_strdup(cmd->command);
	i++;
	while (temp->type == WORD || temp->type == VAR)
	{
		cmd->args[i] = ft_strdup(temp->str);
		i++;
		temp = temp->next;
	}
	cmd->args[i] = NULL;
	*token_node = temp;
	return (SUCCESS);
}

char	**extend_args_with_tokens(int existing_len, char **new_args,
	t_cmd *cmd, t_separation **token_node)
{
	t_separation	*current;
	int				i;

	i = 0;
	current = *token_node;
	while (i < existing_len)
	{
		new_args[i] = cmd->args[i];
		i++;
	}
	///////
	while (current->type == WORD || current->type == VAR)
	{
		new_args[i] = ft_strdup(current->str);
		i++;
		current = current->next;
	}
	new_args[i] = NULL;
	//
	return (new_args);
}

int	append_default_args(t_separation **token_node, t_cmd *cmd)
{
	printf("🧩 append_default_arguments called\n");
	int				arg_count;
	int				existing_len;
	char			**new_args;
	t_separation	*current;

	arg_count = 0;
	existing_len = 0;
	current = *token_node;
	/////
	while ((current->type == WORD || current->type == VAR))
	{
		arg_count++;
		current = current->next;
	}
	while (cmd->args[existing_len])
		existing_len++;
	new_args = malloc(sizeof(char *) * (arg_count + existing_len + 1));
	if (!new_args)
		return (FAILURE);
	new_args = extend_args_with_tokens(existing_len, new_args,
			cmd, token_node);
	free(cmd->args);
	cmd->args = new_args;
	*token_node = current;
	return (SUCCESS);
}

int	process_command_args(t_separation **token_node, t_cmd *last_cmd)
{
	if (ft_strcmp(last_cmd->command, "echo") == 0)
	{
		if (last_cmd->args == NULL)
			return(initialize_echo_arguments(token_node, last_cmd));
		else
			return(append_echo_arguments(token_node, last_cmd));
	}
	else
	{
		if (last_cmd != NULL && last_cmd->args == NULL)
			return(initialize_default_args(token_node, last_cmd));
		else
			return(append_default_args(token_node, last_cmd));
	}
	return (SUCCESS);
}
