#include "../minishell.h"

bool	has_space(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			return (true);
		i++;
	}
	return (false);
}

void	split_variable_command(t_cmd *last_cmd, const char *cmd_str)
{
	char			**tokens;
	t_separation	*token_list;
	t_separation	*tmp;
	t_separation	*new_token;
	t_separation	*end_token;
	int				i;

	token_list = NULL;
	tokens = ft_split(cmd_str, ' ');
	if (!tokens)
		return ;
	last_cmd->command = ft_strdup(tokens[0]);
	if (tokens[1])
		token_list = ft_new_token(ft_strdup(tokens[1]), NULL, WORD, DFLT);
	tmp = token_list;
	i = 1;
	while (tokens[++i])
	{
		new_token = ft_new_token(ft_strdup(tokens[i]), NULL, WORD, DFLT);
		add_token(&token_list, new_token);
	}
	end_token = ft_new_token(NULL, NULL, END, DFLT);
	add_token(&token_list, end_token);
	process_command_args(&token_list, last_cmd);
	clear_token_list(&tmp, &free_str);
	free_string_array(tokens);
}

void	parse_word_token(t_cmd **cmd, t_separation **token_lst)
{
	t_separation	*current_token;
	t_cmd			*last_cmd;

	current_token = *token_lst;
	while (current_token && (current_token->type == WORD
			|| current_token->type == VAR))
	{
		last_cmd = get_last_command(*cmd);
		if (current_token->prev == NULL
			|| (current_token->prev && current_token->prev->type == PIPE)
			|| last_cmd->command == NULL)
		{
			if (current_token->type == VAR
				&& has_space(current_token->str))
				split_variable_command(last_cmd, current_token->str);
			else
				last_cmd->command = ft_strdup(current_token->str);
			current_token = current_token->next;
		}
		else
			process_command_args(&current_token, last_cmd);
	}
	*token_lst = current_token;
}
