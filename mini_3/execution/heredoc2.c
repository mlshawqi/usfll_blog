#include "../minishell.h"

void    handle_sigint_heredoc(int sig)
{
        if(sig == SIGINT)
	{
		write(1, "\n", 1);
		exit (130);
	}
}

int     handle_parent(int *fdpipe, t_in_out_fds *io, int pid)
{
        int	status;

	close(fdpipe[1]);
	waitpid(pid, &status, 0);
        if (WIFSIGNALED(status) || (WIFEXITED(status) && WEXITSTATUS(status) == 130))
        {
		// print_cmd_error("in heredoc", "ctrl c", NULL);
                close(fdpipe[0]);
		if (WTERMSIG(status) == SIGINT) 
			write(1, "\n", 1);
		io->fd = -1;
		g_last_exit_code = 128 + WTERMSIG(status);
                return (g_last_exit_code);
        }
	else
	{
		io->fd = fdpipe[0];
		if (WIFEXITED(status))
			return WEXITSTATUS(status);
	}
        return (0);
}

int	fork_heredoc(t_data *data, t_in_out_fds *io)
{
	int	pid;
	int	fdpipe[2];

	if(pipe(fdpipe) == -1)
	{
		perror("pipe failed");
                return (-1);
	}
	signal(SIGINT, SIG_IGN);
	pid = fork();
        if(pid < 0)
                return (print_cmd_error("fork", "heredoc fork fail", NULL), 1);
	else if(pid == 0)
	{
		signal(SIGINT, handle_sigint_heredoc);
		close(fdpipe[0]);
		exit(write_heredoc_input(data, io, fdpipe[1]));
	}
	else
                return (handle_parent(fdpipe, io, pid));
	return (0);
}
