#include "../minishell.h"

bool	is_valid_var_char(char c)
{
	if (ft_isalnum(c) == 0 && c != '_')
		return (false);
	else
		return (true);
}

int get_var_length(char *str)
{
	if (!str || str[0] != '$')
		return (0);

	if (str[1] == '?' || (str[1] >= '0' && str[1] <= '9'))
		return (2);

	int i = 1;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;

	return (i);
}


char *extract_variable(char *str)
{
	if (!str || str[0] != '$')
		return (NULL);

	int len = get_var_length(str);
	if (len <= 1)
		return (NULL);
	return ft_substr(str, 1, len - 1);
}
