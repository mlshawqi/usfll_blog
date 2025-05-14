#include "../minishell.h"

bool	is_valid_var_char(char c)
{
	if (ft_isalnum(c) == 0 && c != '_')
		return (false);
	else
		return (true);
}

int	get_var_length(char *str)
{
	int	i;
	int	length;

	i = 0;
	length = 0;
	while (str[i] != '$' && str[i])
		i++;
	i++;
	if ((str[i] >= '0' && str[i] <= '9') || str[i] == '?' || str[i] == '*')
	// if (str[i] == '?')
		return (1);
	while (str[i])
	{
		if (is_valid_var_char(str[i]) == false)
			break ;
		length++;
		i++;
	}
	return (length);
}

char	*extract_variable(char *str)
{
	char	*var;
	char	*tmp;
	int		start;
	int		len;
	int		i;

	start = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			start = i + 1;
			break ;
		}
		i++;
	}
	len = get_var_length(str);
	var = ft_substr(str, start, len);
	if (!var)
		return (NULL);
	return (var);
}
