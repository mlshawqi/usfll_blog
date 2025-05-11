#include "../minishell.h"

char	*combine_vars(t_separation **token_node)
{
	t_separation	*current_token;
	char			*result;

	current_token = *token_node;
	result = ft_strdup(current_token->str);
	while (current_token->type == VAR
		&& current_token->next->type == VAR
		&& current_token->next->join == true)
	{
		result = ft_strjoin(result, current_token->next->str);
		current_token = current_token->next;
	}
	*token_node = current_token;
	return (result);
}

int	count_arguments(t_separation *current_token)
{
	int	count;

	count = 0;
	while (current_token && (current_token->type == WORD
			|| current_token->type == VAR))
	{
		if (current_token->type == VAR && current_token->join == true)
		{
			while (current_token->type == VAR
				&& current_token->join == true)
				current_token = current_token->next;
			count++;
		}
		else
		{
			count++;
			current_token = current_token->next;
		}
	}
	return (count);
}

char	**copy_args_to_new_tab(int existing_len, char **new_args,
	t_cmd *last_cmd, t_separation *current_token)
{
	int	i;

	i = 0;
	while (i < existing_len)
	{
		new_args[i] = last_cmd->args[i];
		i++;
	}
	while (current_token->type == WORD || current_token->type == VAR)
	{
		if (current_token->join == true)
			new_args[i] = combine_vars(&current_token);
		else
			new_args[i] = ft_strdup(current_token->str);
		i++;
		current_token = current_token->next;
	}
	new_args[i] = NULL;
	return (new_args);
}

void	remove_empty_variables(t_separation **tokens)
{
	t_separation	*current_token;

	current_token = *tokens;
	///////
	while ((current_token->type == WORD
			|| current_token->type == VAR))
	{
		if (current_token->type == VAR && current_token->str[0] == '\0'
			&& current_token->is_var == false)
		{
			current_token = current_token->next;
			if (current_token == (*tokens)->next)
				(*tokens) = (*tokens)->next;
			delete_token(current_token->prev, free_str);
		}
		else
			current_token = current_token->next;
	}
}

int	initialize_echo_arguments(t_separation **token_node, t_cmd *last_cmd)
{
	int				nb_args;
	t_separation	*current_token;
	int				i;

	i = 0;
	remove_empty_variables(token_node);
	current_token = *token_node;
	nb_args = count_arguments(current_token);
	last_cmd->args = malloc(sizeof(char *) * (nb_args + 2));
	if (!last_cmd->args)
		return (FAILURE);
	last_cmd->args[i] = ft_strdup(last_cmd->command);
	i++;
	while (current_token->type == WORD || current_token->type == VAR)
	{
		if (current_token->join == true)
			last_cmd->args[i] = combine_vars(&current_token);
		else
			last_cmd->args[i] = ft_strdup(current_token->str);
		i++;
		current_token = current_token->next;
	}
	last_cmd->args[i] = NULL;
	*token_node = current_token;
	return (SUCCESS);
}

int	append_echo_arguments(t_separation **token_node, t_cmd *last_cmd)
{
	printf("🧩 append_echo_arguments called\n");
	int				nb_args;
	int				len;
	char			**new_tab;
	t_separation	*current_token;

	remove_empty_variables(token_node);
	current_token = *token_node;
	nb_args = count_arguments(current_token);
	len = 0;
	while (last_cmd->args[len])
		len++;
	new_tab = malloc(sizeof(char *) * (nb_args + len + 1));
	if (!new_tab)
		return (FAILURE);
	new_tab = copy_args_to_new_tab(len, new_tab, last_cmd, current_token);
	free(last_cmd->args);
	last_cmd->args = new_tab;
	while (current_token->type == WORD || current_token->type == VAR)
		current_token = current_token->next;
	*token_node = current_token;
	return (SUCCESS);
}
