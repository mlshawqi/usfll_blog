#include "../minishell.h"

static bool	is_input_only_spaces(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (!ft_isspace(input[i]))
			return (false);
		i++;
	}
	return (true);
}

bool	process_user_input(t_data *data)
{
    if (ft_strcmp(data->user_input, "\0") == 0)
        return (false);
    if (is_input_only_spaces(data->user_input))
        return (true);
    
    add_history(data->user_input);
    if (tokenization(data, data->user_input) == FAILURE)
        return (false);
    if (data->token->type == END)
        return (false);

    if (var_checker(&data->token) == FAILURE)
        return (false);
    expand_variables(data, &data->token);
    process_quotes(data);
    ft_create_commands(data, data->token);
    return (true);
}