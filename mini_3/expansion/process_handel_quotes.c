#include "../minishell.h"

int	calculate_new_length(char *str, int count, int i)
{
	int	status;

	status = 0;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '\"') && status == DFLT)
		{
			if (str[i] == '\'')
				status = SQUOTE;
			else
				status = DQUOTE;
			i++;
			continue ;
		}
		else if ((str[i] == '\'' && status == SQUOTE)
			|| (str[i] == '\"' && status == DQUOTE))
		{
			status = DFLT;
			i++;
			continue ;
		}
		count++;
		i++;
	}
	return (count + 1);
}

bool	contains_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			return (true);
		i++;
	}
	return (false);
}

int	process_quotes(t_data *data)
{
	t_separation	*current;

	current = data->token;
	while (current)
	{
		if (contains_quotes(current->str)
			&& (!current->prev || (current->prev
					&& current->prev->type != HEREDOC)))
			delete_quotes(&current);
		current = current->next;
	}
	return (0);
}
