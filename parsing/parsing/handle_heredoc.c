#include "../minishell.h"

char	*build_string_from_array(char **array)
{
	char	*result;
	char	*temp;
	int		i;

	i = -1;
	result = NULL;
	while (array[++i])
	{
		temp = result;
		if (i == 0)
			result = ft_strdup(array[0]);
		else
		{
			result = ft_strjoin(temp, array[i]);
			free_str(temp);
		}
		if (array[i + 1])
		{
			temp = result;
			result = ft_strjoin(temp, " ");
			free_str(temp);
		}
	}
	free_string_array(array);
	return (result);
}

char	*expand_variable_in_line(t_data *data, char *line)
{
	char	**words;
	int		i;

	words = ft_split(line, ' ');
	if (!words)
		return (NULL);
	i = 0;
	while (words[i])
	{
		if (ft_strchr(words[i], '$'))
		{
			words[i] = expand_heredoc_variables(data, words[i]);
			if (!words[i])
				return (NULL);
		}
		i++;
	}
	return (build_string_from_array(words));
}

bool	check_heredoc_line(t_data *data, char **line,
	t_in_out_fds *io, bool *success)
{
	if (*line == NULL)
	{
		display_error_message(
			"warning: here-document delimited by end-of-file: wanted",
			io->heredoc_delimiter, true);
		*success = true;
		return (false);
	}
	if (ft_strcmp(*line, io->heredoc_delimiter) == 0)
	{
		*success = true;
		return (false);
	}
	if (!io->heredoc_quotes && ft_strchr(*line, '$'))
	{
		*line = expand_variable_in_line(data, *line);
		if (!(*line))
		{
			free_str(*line);
			*success = false;
			return (false);
		}
	}
	return (true);
}

bool	write_heredoc_input(t_data *data, t_in_out_fds *io, int fd)
{
	char	*line;
	bool	success;

	success = false;
	line = NULL;
	while (1)
	{
		configure_interactive_signals();
		line = readline(">");
		configure_noninteractive_signals();
		if (!check_heredoc_line(data, &line, io, &success))
			break ;
		ft_putendl_fd(line, fd);
		free_str(line);
	}
	free_str(line);
	return (success);
}

bool	activate_heredoc(t_data *data, t_in_out_fds *io)
{
	int		tmp_fd;
	bool	success;

	success = true;
	tmp_fd = open(io->infile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	success = write_heredoc_input(data, io, tmp_fd);
	close(tmp_fd);
	return (success);
}

char	*generate_heredoc_name(void)
{
	static int	count = 0;
	char		*name;
	char		*index;

	index = ft_itoa(count);
	if (!index)
		return (NULL);
	name = ft_strjoin(HEREDOC_NAME, index);
	free(index);
	count++;
	return (name);
}

char	*get_delimiter(char *delim, bool *quotes)
{
	int	length;

	length = ft_strlen(delim) - 1;
	if ((delim[0] == '\"' && delim[length] == '\"')
		|| (delim[0] == '\'' && delim[length] == '\''))
	{
		*quotes = true;
		return (ft_strtrim(delim, "\'\""));
	}
	return (ft_strdup(delim));
}

void	process_heredoc(t_data *data, t_cmd **last_cmd,
	t_separation **token_lst)
{
	t_separation	*token;
	t_cmd			*cmd;
	t_in_out_fds	*io;

	token = *token_lst;
	cmd = get_last_command(*last_cmd);
	init_cmd_in_out(cmd);
	io = cmd->io_fds;
	if (!clean_up_old_file_ref(io, true))
		return ;
	io->infile = generate_heredoc_name();
	io->heredoc_delimiter = get_delimiter(token->next->str,
			&(io->heredoc_quotes));
	if (activate_heredoc(data, io))
		io->fd_in = open(io->infile, O_RDONLY);
	else
		io->fd_in = -1;
	if (token->next->next)
		token = token->next->next;
	else
		token = token->next;
	*token_lst = token;
}
