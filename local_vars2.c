// #include <minishell.h>

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
                printf(str[i]);
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

int	process_quotes(t_local **data, char *str)
{

	contains_quotes(str);
		// delete_quotes(&current);
	return (0);
}

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

char	*copy_without_quotes(char *new_str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (new_str)
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

int	delete_quotes(t_local **lst, char *str)
{
	char	*new_str;
	int		len;
        char    *line;

	len = calculate_new_length(str, 0, 0);
	new_str = malloc(sizeof(char) * len);
	if (!new_str)
		return (1);
	line = copy_without_quotes(new_str);
	free_str((*token)->str);
	(*token)->str = new_str;
	(*token)->join = true;
	return (0);
}