#include "../minishell.h"

void	handle_pipe(t_cmd **cmd, t_separation **token_list)
{
	t_cmd	*last_command;

	last_command = get_last_command(*cmd);
	last_command->pipe_output = true;
	add_command_to_list(&last_command, create_command(false));
	*token_list = (*token_list)->next;
}
