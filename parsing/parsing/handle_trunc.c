#include "../minishell.h"

void	open_outfile_trunc(t_in_out_fds *io, char *file, char *var_filename)
{
	io->filename = ft_strdup(file);
	if (!io->filename || io->filename[0] == '\0')
	{
		print_command_error(var_filename, NULL, "ambiguous redirect", false);
		return ;
	}
	io->fd = open(io->filename, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (io->fd == -1)
		print_command_error(io->filename, NULL, strerror(errno), false);
}

void	parse_trunc(t_cmd **last_cmd, t_separation **token_lst)
{
	t_separation	*current_token;
	t_cmd			*cmd;
	t_in_out_fds		*red;

	current_token = *token_lst;
	cmd = get_last_command(*last_cmd);
	init_cmd_in_out(cmd);
	red = new_node_redirection(REDIR_OUT);
	if(!red)
		return ;
	open_outfile_trunc(red, current_token->next->str,
		current_token->next->str_copy);
	link_node_redirection(&cmd->io_fds, red);
	if (current_token->next->next)
		current_token = current_token->next->next;
	else
		current_token = current_token->next;
	*token_lst = current_token;
}
