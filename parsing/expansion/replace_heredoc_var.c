#include "../minishell.h"

static int	remove_variable(t_separation **token, char *str, int idx)
{
	int		len;
	char	*new_str;
	int		i;
	int		j;

	len = ft_strlen(str) - get_var_length(str + idx);
	new_str = (char *)malloc(sizeof(char) * (len + 1));
	if (!new_str)
		return (1);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '$' && i == idx)
		{
			i = i + get_var_length(str + idx) + 1;
			if (str[i] == '\0')
				break ;
		}
		new_str[j++] = str[i++];
	}
	new_str[j] = '\0';
	free_str((*token)->str);
	(*token)->str = new_str;
	return (0);
}

static char	*replace_and_update(t_separation **token_node,
		char *str, char *var_value, int index)
{
	char	*newstr;
	int		newstr_len;

	newstr_len = ft_strlen(str) - get_var_length(str + index)
		+ ft_strlen(var_value);
	newstr = construct_new_string(str, var_value, newstr_len, index);
	if (token_node && *token_node)
	{
		free_str((*token_node)->str);
		(*token_node)->str = newstr;
	}
	return (newstr);
}

int	replace_variable(t_separation **token, char *value, int idx)
{
	if (!value)
	{
		if (remove_variable(token, (*token)->str, idx) == 1)
		{
			free_str(value);
			return (1);
		}
	}
	else
	{
		if (!replace_and_update(token, (*token)->str, value, idx))
		{
			free_str(value);
			return (1);
		}
	}
	free_str(value);
	return (0);
}

char	*replace_heredoc_var(char *str, char *value, int idx)
{
	char	*tmp;

	if (!value)
		value = ft_strdup("");

	if (!value)
		return (NULL);

	tmp = str;
	str = replace_and_update(NULL, str, value, idx);
	free_str(tmp);
	free_str(value);
	return (str);
}