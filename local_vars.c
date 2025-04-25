#include "minishell.h"

int	calculate_new_length(char *str, int count)
{
	int	status;
        int     i;

	status = 0;
        i = 0;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '\"') && status == DFLT)
		{
			if (str[i] == '\'')
				status = SQUOTE;
			else
				status = DQUOTE;
		}
		else if ((str[i] == '\'' && status == SQUOTE)
			|| (str[i] == '\"' && status == DQUOTE))
			status = DFLT;
                else
		        count++;
		i++;
	}
        if(status != DFLT)
                return (-1);
	return (count);
}

bool	contains_quotes(char *str)
{
	int	i;

	i = 0;
        if(str[0] == '=')
                return (false);
	while (str[i] && str[i] != '=')
	{
		if (str[i] == '\'' || str[i] == '\"')
			return (false);
		i++;
	}
	return (true);
}

void    assigned_lvar(t_local **lvar, char *str)
{
        (void)lvar;

        printf("--- %s\n", str + (ft_strchr(str, '=') - str));
	if(ft_strchr(str, '=') && contains_quotes(str))
	        delete_quotes(str);
        else
                printf("wrong\n");
	// return (0);
}
static int     claculate_name_len(char *str)
{
        int     len;

        len = 0;
        while(str[len] && str[len] != '=')
                len++;
        return (len);
}

int	delete_quotes(char *str)
{
	// char	*value;
        // char    *name;
	int		len_name;
        int             len_value;

        len_name = claculate_name_len(str);
	len_value = calculate_new_length(str + ((ft_strchr(str, '=') - str)) + 1, 0);
        if(len_value == -1)
        {
                printf("syntax error missing Quotes");
                exit (1);
        }
	// new_str = malloc(sizeof(char) * len);
	// if (!new_str)
	// 	return (1);
        printf("len value %d %d\n", len_value, len_name);
	return (0);
}