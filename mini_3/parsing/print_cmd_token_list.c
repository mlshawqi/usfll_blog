#include "../minishell.h"

void	display_command_arguments(t_cmd *cmd)
{
	int	i;

	if (!cmd || !cmd->args)
		return ;
	i = 0;
	while (cmd->args[i])
	{
		printf("\t- Argument[%d] : %s\n", i, cmd->args[i]);
		i++;
	}
}

const char *get_redirection_name(t_redirections type)
{
    if (type == REDIR_IN)
        return "REDIR_IN";
    else if (type == REDIR_OUT)
        return "REDIR_OUT";
    else if (type == REDIR_APPEND)
        return "REDIR_APPEND";
    else if (type == REDIR_HEREDOC)
        return "REDIR_HEREDOC";
    return "UNKNOWN";
}

void	display_command_redirections(t_cmd *cmd)
{
	t_in_out_fds *tmp;

	if (!cmd || !cmd->io_fds)
		return ;
	tmp = cmd->io_fds;
	while(tmp)
	{
		printf("type: %s\n", get_redirection_name(tmp->type));
		if (tmp->filename)
			printf("\t- file name       : %s\n", tmp->filename);
		if(tmp->fd)
			printf("\t  fd_in       : %d\n", tmp->fd);
		if (tmp->heredoc_delimiter)
			printf("\t- Heredoc delim : %s\n", tmp->heredoc_delimiter);
		// if (cmd->io_fds->outfile)
		// {
		// 	printf("\t- Outfile       : %s\n", cmd->io_fds->outfile);
		// 	printf("\t  > fd_out      : %d\n", cmd->io_fds->fd_out);
		// }
		tmp = tmp->next;
	}
}

void	display_pipeline_commands(t_data *data)
{
	t_cmd	*cmd;

	cmd = data->cmd;
	printf("\n========== COMMAND PIPELINE ==========\n");
	while (cmd)
	{
		printf("\n[ Command]: %s\n", cmd->command ? cmd->command : "(null)");
		display_command_arguments(cmd);
		printf("\t- Pipe output  : %d\n", cmd->pipe_output);
		display_command_redirections(cmd);

		printf("\t- Prev command : %s\n", cmd->prev ? cmd->prev->command : "NULL");
		printf("\t- Next command : %s\n", cmd->next ? cmd->next->command : "NULL");

		cmd = cmd->next;
	}
	printf("======================================\n\n");
}

void	display_token_type(t_separation *token, const char *prefix)
{
	printf("%s", prefix);
	if (token->type == SPACES)
		printf("SPACES\n");
	else if (token->type == WORD)
		printf("WORD\n");
	else if (token->type == VAR)
		printf("VAR\n");
	else if (token->type == PIPE)
		printf("PIPE\n");
	else if (token->type == INPUT)
		printf("INPUT\n");
	else if (token->type == TRUNC)
		printf("TRUNC\n");
	else if (token->type == HEREDOC)
		printf("HEREDOC\n");
	else if (token->type == APPEND)
		printf("APPEND\n");
	else if (token->type == END)
		printf("END\n");
	else
		printf("UNKNOWN\n");
}

void	display_token_list(t_separation **tokens)
{
	t_separation	*current;
	int				i;

	current = *tokens;
	printf("\n========== TOKEN LIST ==========\n");
	i = 0;
	while (current)
	{
		printf("\n[🔹 Token %d] @ %p\n", i, (void *)current);
		printf("\t- str        : [%s]\n", current->str);
		printf("\t- str_copy   : [%s]\n", current->str_copy);
		display_token_type(current, "\t- type       : ");
		printf("\t- status     : %d\n", current->status);
		printf("\t- prev       : %p\n", (void *)current->prev);
		printf("\t- next       : %p\n", (void *)current->next);
		current = current->next;
		i++;
	}
	printf("=================================\n\n");
}
