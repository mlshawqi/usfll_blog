#include "../minishell.h"

bool	clean_up_old_file_ref(t_in_out_fds *io, bool is_input)
{
	if (is_input == true && io->infile)
	{
		if (io->fd_in == -1 || (io->outfile && io->fd_out == -1))
			return (false);
		if (io->heredoc_delimiter != NULL)
		{
			free_str(io->heredoc_delimiter);
			io->heredoc_delimiter = NULL;
			unlink(io->infile);
		}
		free_str(io->infile);
		close(io->fd_in);
	}
	else if (is_input == false && io->outfile)
	{
		if (io->fd_out == -1 || (io->infile && io->fd_in == -1))
			return (false);
		free_str(io->outfile);
		close(io->fd_out);
	}
	return (true);
}

void	open_input_file(t_in_out_fds *io, char *file, char *original_filename)
{
	bool	parse_success2 = true;
	if (!clean_up_old_file_ref(io, true))
		return ;
	io->infile = ft_strdup(file);
	if (io->infile && io->infile[0] == '\0')
	{
		print_command_error(original_filename, NULL,
			"ambiguous redirect", false);
		return ;
	}
	io->fd_in = open(io->infile, O_RDONLY);
	if (io->fd_in == -1)
		print_command_error(io->infile, NULL, strerror(errno), false);
}

void	handle_input_redirection(t_cmd **last_cmd, t_separation **token_lst)
{
	t_separation	*temp;
	t_cmd			*cmd;

	temp = *token_lst;
	cmd = get_last_command(*last_cmd);
	init_cmd_in_out(cmd);
	open_input_file(cmd->io_fds, temp->next->str, temp->next->str_copy);
	if (temp->next->next)
		temp = temp->next->next;
	else
		temp = temp->next;
	*token_lst = temp;
}
