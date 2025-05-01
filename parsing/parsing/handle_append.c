#include "../minishell.h"

void	open_output_file_append(t_in_out_fds *io,
		char *file, char *original_filename)
{
	// bool	parse_success1 = true;
	if (!clean_up_old_file_ref(io, false))
		return ;
	io->outfile = ft_strdup(file);
	if (io->outfile && io->outfile[0] == '\0' && original_filename)
	{
		print_command_error(original_filename, NULL,
			"ambiguous redirect", false);
		return ;
	}
	io->fd_out = open(io->outfile, O_WRONLY | O_CREAT | O_APPEND, 0664);
	if (io->fd_out == -1)
		print_command_error(io->outfile, NULL, strerror(errno), false);
}

void	handle_append_redirection(t_cmd **last_cmd, t_separation **token_lst)
{
	t_separation	*temp;
	t_cmd			*cmd;

	temp = *token_lst;
	cmd = get_last_command(*last_cmd);
	init_cmd_in_out(cmd);
	open_output_file_append(cmd->io_fds,
		temp->next->str, temp->next->str_copy);
	if (temp->next->next)
		temp = temp->next->next;
	else
		temp = temp->next;
	*token_lst = temp;
}
