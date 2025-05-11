#include "../minishell.h"

void	check_for_variable(t_separation **token)
{
	int	i;

	i = 0;
	while ((*token)->str[i])
	{
		if ((*token)->str[i] == '$')
		{
			if ((*token)->prev && (*token)->prev->type == HEREDOC)
				break ;
			(*token)->type = VAR;
			return ;
		}
		i++;
	}
}

int	var_checker(t_separation **token_list)
{
	t_separation	*current;

	current = *token_list;
	if (current && current->type == PIPE)
	{
		display_error_message(
			"syntax error near unexpected token",
			current->str,
			true);
		return (FAILURE);
	}
	while (current)
	{
		check_for_variable(&current);
		if (check_errors_rep(&current) == FAILURE)
			return (FAILURE);
		current = current->next;
	}
	return (SUCCESS);
}