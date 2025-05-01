#include "../minishell.h"

bool	has_consecutive_ops(t_separation *token_node)
{
	t_separation	*prev;

	if (!token_node)
		return (false);
	prev = token_node->prev;
	if (!prev)
		return (false);
	if (token_node->type == PIPE && prev->type == PIPE)
		return (true);
	if ((token_node->type >= INPUT && token_node->type <= APPEND)
		&& (prev->type >= INPUT && prev->type <= APPEND))
		return (true);
	if ((token_node->type >= INPUT && token_node->type <= APPEND
			&& prev->type == PIPE)
		|| (token_node->type == PIPE
			&& prev->type >= INPUT && prev->type <= APPEND))
		return (true);
	return (false);
}

static int	check_errors_part_one(t_separation *temp)
{
	if (temp->type == PIPE && temp->prev
		&& temp->prev->type == INPUT)
	{
		if (temp->next == NULL || temp->next->type == END)
		{
			display_error_message(
				"bash: syntax error near unexpected token",
				"|", true);
			return (FAILURE);
		}
	}
	if ((temp->type >= INPUT && temp->type <= APPEND)
		|| temp->type == PIPE)
	{
		if (temp->next == NULL || temp->next->type == END)
		{
			display_error_message(
				"bash: syntax error near unexpected token",
				"newline", true);
			return (FAILURE);
		}
	}
	if (temp->type == AMPER)
	{
		t_separation *curr = temp;
		int count = 0;
		while (curr && curr->type == AMPER)
		{
			count++;
			curr = curr->next;
		}
		if (count == 1)
		{
			if (temp->next == NULL || temp->next->type == END)
				display_error_message("bash: syntax error near unexpected token", "newline", true);
			else
				display_error_message("bash: syntax error near unexpected token", "&", true);
			return (FAILURE);
		}
		if (count >= 2)
		{
			display_error_message("bash: syntax error near unexpected token", "&", true);
			return (FAILURE);
		}
	}
	return (SUCCESS);
}

int	check_errors_rep(t_separation **token_lst)
{
	t_separation	*temp;

	temp = *token_lst;
	while (temp)
	{
		if (check_errors_part_one(temp) == FAILURE)
			return (FAILURE);
		// if (temp && temp->type == PIPE)
		// {
		// 	display_error_message(
		// 		"syntax error near unexpected token",
		// 		temp->str,
		// 		true);
		// 	return (FAILURE);
		// }
		if (has_consecutive_ops(temp))
		{
			display_error_message(
				"bash: syntax error near unexpected token",
				temp->str, true);
			return (FAILURE);
		}
		temp = temp->next;
	}
	return (SUCCESS);
}
