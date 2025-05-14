#include "../minishell.h"

void	initialize_no_arg_commands(t_data *data)
{
	t_cmd	*cmd;

	if (!data || !data->cmd)
		return ;
	cmd = data->cmd;
	while (cmd && cmd->command)
	{
		if (!cmd->args)
		{
			cmd->args = malloc(sizeof(*cmd->args) * 2);
			cmd->args[0] = ft_strdup(cmd->command);
			cmd->args[1] = NULL;
		}
		cmd = cmd->next;
	}
	cmd = get_last_command(data->cmd);
}

void	ft_create_commands(t_data *data, t_separation *token)
{
	t_separation	*cur;

	cur = token;
	if (cur->type == END)
		return ;
	while (cur->next != NULL)
	{
		if (cur == token)
			add_command_to_list(&data->cmd, create_command(false));
		if (cur->type == WORD || cur->type == VAR)
			parse_word_token(&data->cmd, &cur);
		else if (cur->type == INPUT)
			handle_input_redirection(&data->cmd, &cur);
		else if (cur->type == TRUNC)
			parse_trunc(&data->cmd, &cur);
		else if (cur->type == HEREDOC)
			process_heredoc(data, &data->cmd, &cur);
		else if (cur->type == APPEND)
			handle_append_redirection(&data->cmd, &cur);
		else if (cur->type == PIPE)
			handle_pipe(&data->cmd, &cur);
		else if (cur->type == END)
			break ;
	}
	initialize_no_arg_commands(data);
}
