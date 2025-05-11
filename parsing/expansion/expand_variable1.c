#include "../minishell.h"

void	insert_var_value(char *new_str, char *var_value, int *pos)
{
	int	k;

	k = 0;
	while (var_value[k])
	{
		new_str[*pos] = var_value[k];
		k++;
		(*pos)++;
	}
}

char	*construct_new_string(char *old_str, char *var_value,
			int new_size, int index)
{
	int		i;
	int		j;
	char	*new_str;

	i = 0;
	j = 0;
	new_str = malloc(sizeof(char) * new_size);
	if (!new_str)
		return (NULL);
	while (old_str[i])
	{
		if (old_str[i] == '$' && i == index)
		{
			insert_var_value(new_str, var_value, &j);
			i += get_var_length(old_str + index) + 1;
			if (!old_str[i])
				break ;
		}
		new_str[j++] = old_str[i++];
	}
	new_str[j] = '\0';
	return (new_str);
}
