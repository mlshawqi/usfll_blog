#include "../minishell.h"

static void	update_quote_status(t_separation **token, int *i)
{
	char	c;

	c = (*token)->str[*i];
	if (c == '\'')
		(*token)->status = SQUOTE;
	else if (c == '\"')
		(*token)->status = DQUOTE;
	(*i)++;
}

static bool	is_quote_in_default_state(t_separation **token, int i)
{
	char	c;

	c = (*token)->str[i];
	return ((c == '\'' || c == '\"') && (*token)->status == DFLT);
}

static bool	reset_status_if_matching_quote(t_separation **token, int *i)
{
	char	c;

	c = (*token)->str[*i];
	if ((c == '\'' && (*token)->status == SQUOTE)
		|| (c == '\"' && (*token)->status == DQUOTE))
	{
		(*token)->status = DFLT;
		(*i)++;
		return (true);
	}
	return (false);
}

static void	copy_without_quotes(t_separation **token, char *new_str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while ((*token)->str[i])
	{
		if (is_quote_in_default_state(token, i))
		{
			update_quote_status(token, &i);
			continue ;
		}
		if (reset_status_if_matching_quote(token, &i))
			continue ;
		new_str[j++] = (*token)->str[i++];
	}
	new_str[j] = '\0';
}

int	delete_quotes(t_separation **token)
{
	char	*new_str;
	int		len;

	len = calculate_new_length((*token)->str, 0, 0);
	new_str = malloc(sizeof(char) * len);
	if (!new_str)
		return (1);
	copy_without_quotes(token, new_str);
	free_str((*token)->str);
	(*token)->str = new_str;
	(*token)->join = true;
	return (0);
}
