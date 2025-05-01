#include "../minishell.h"


void	open_outfile_trunc(t_in_out_fds *io, char *file, char *var_filename)
{
	if (!clean_up_old_file_ref(io, false))
		return ;
	io->outfile = ft_strdup(file);
	if (!io->outfile || io->outfile[0] == '\0')
	{
		print_command_error(var_filename, NULL, "ambiguous redirect", false);
		return ;
	}
	io->fd_out = open(io->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (io->fd_out == -1)
		print_command_error(io->outfile, NULL, strerror(errno), false);
}

void	parse_trunc(t_cmd **last_cmd, t_separation **token_lst)
{
	t_separation	*current_token;
	t_cmd			*cmd;

	current_token = *token_lst;
	cmd = get_last_command(*last_cmd);
	init_cmd_in_out(cmd);
	open_outfile_trunc(cmd->io_fds,
		current_token->next->str,
		current_token->next->str_copy);
	if (current_token->next->next)
		current_token = current_token->next->next;
	else
		current_token = current_token->next;
	*token_lst = current_token;
}
