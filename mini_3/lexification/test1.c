#include "../minishell.h"

void	free_token_list(t_separation **token_list)
{
	t_separation	*tmp;

	while (*token_list)
	{
		tmp = *token_list;
		*token_list = (*token_list)->next;
		free(tmp->str);
		free(tmp->str_copy);
		free(tmp);
	}
	*token_list = NULL;
}

t_separation	*ft_new_token(char *str, char *str_backup,
		int type, int status)
{
	t_separation	*new_token;

	new_token = malloc(sizeof(t_separation));
	if (!new_token)
		return (NULL);
	new_token->str = str;
	new_token->str_copy = str_backup;
	new_token->is_var = false;
	new_token->type = type;
	new_token->status = status;
	new_token->join = false;
	new_token->prev = NULL;
	new_token->next = NULL;
	return (new_token);
}

void	add_token(t_separation **lst, t_separation *new_token)
{
	t_separation	*start;

	start = *lst;
	if (!start)
	{
		*lst = new_token;
		return ;
	}
	if (lst && *lst && new_token)
	{
		while (start->next != NULL)
			start = start->next;
		start->next = new_token;
		new_token->prev = start;
	}
}

char	*extract_separator(char *str, int index, int len)
{
	int		i;
	char	*sep;

	sep = malloc(sizeof(char) * (len + 1));
	if (!sep)
		return (NULL);
	i = 0;
	while (i < len)
	{
		sep[i] = str[index + i];
		i++;
	}
	sep[i] = '\0';
	return (sep);
}

int	malloc_separator(t_separation **token_lst,
	char *str, int index, int type)
{
	int				len;
	char			*sep;
	t_separation	*new_tok;

	len = 1;
	if (type == APPEND || type == HEREDOC)
		len = 2;
	sep = extract_separator(str, index, len);
	if (!sep)
		return (1);
	new_tok = ft_new_token(sep, NULL, type, DFLT);
	if (!new_tok)
	{
		free(sep);
		return (1);
	}
	add_token(token_lst, new_tok);
	return (0);
}

int	malloc_word(t_separation **token_lst,
	char *str, int index, int start)
{
	int		i;
	char	*word;

	i = 0;
	word = malloc(sizeof(char) * (index - start + 1));
	if (!word)
		return (1);
	while (start < index)
		word[i++] = str[start++];
	word[i] = '\0';
	add_token(token_lst,
		ft_new_token(word, ft_strdup(word), WORD, DFLT));
	return (0);
}

int	is_separator(char *str, int i)
{
	if ((str[i] > 8 && str[i] < 14) || str[i] == 32)
		return (SPACES);
	else if (str[i] == '|')
		return (PIPE);
	else if (str[i] == '<' && str[i + 1] == '<')
		return (HEREDOC);
	else if (str[i] == '>' && str[i + 1] == '>')
		return (APPEND);
	else if (str[i] == '<')
		return (INPUT);
	else if (str[i] == '>')
		return (TRUNC);
	else if (str[i] == '\0')
		return (END);
	else if (str[i] == '&')
		return (AMPER);
	return (0);
}

int	find_status(int status, char *str, int i)
{
	if (str[i] == '\'' && status == DFLT)
		status = SQUOTE;
	else if (str[i] == '\"' && status == DFLT)
		status = DQUOTE;
	else if (str[i] == '\'' && status == SQUOTE)
		status = DFLT;
	else if (str[i] == '\"' && status == DQUOTE)
		status = DFLT;
	return (status);
}

int	malloc_word_separator(int *i, char *str,
	int start, t_data *data)
{
	int	type;

	type = is_separator(str, *i);
	if (type)
	{
		if (*i != 0 && is_separator(str, *i - 1) == 0)
			malloc_word(&data->token, str, *i, start);
		if (type == APPEND || type == HEREDOC || type == PIPE
			|| type == INPUT || type == TRUNC || type == END || type == AMPER)
		{
			malloc_separator(&data->token, str, *i, type);
			if (type == APPEND || type == HEREDOC)
				(*i)++;
		}
		start = *i + 1;
	}
	return (start);
}

int	handle_unclosed_quotes(int status)
{
	if (status == DQUOTE)
		display_error_message("unclosed DQUOTES", "\"", true);
	else if (status == SQUOTE)
		display_error_message("unclosed SQUOTES", "\'", true);
	display_error_message("syntax error", "unexpected end of file", false);
	return (1);
}

int	tokenization(t_data *data, char *str)
{
	int	i;
	int	end;
	int	start;
	int	status;

	i = -1;
	end = ft_strlen(str);
	start = 0;
	status = DFLT;
	data->token = NULL;

	while (++i <= end)
	{
		status = find_status(status, str, i);
		if (status == DFLT)
			start = malloc_word_separator(&i, str, start, data);
	}

	if (status != DFLT)
		return (handle_unclosed_quotes(status));
	if (!data->token)
		return (1);

	return (0);
}