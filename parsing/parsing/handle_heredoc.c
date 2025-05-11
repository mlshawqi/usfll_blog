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
			free_str_null(line);
			*success = false;
			return (false);
		}
	}
	return (true);
}

int	write_heredoc_input(t_data *data, t_in_out_fds *io, int fd)
{
	char	*line;
	bool	success;

	success = false;
	line = NULL;
	while (1)
	{
		line = readline(">");
		if (!check_heredoc_line(data, &line, io, &success))
			break ;
		ft_putendl_fd(line, fd);
		free_str_null(&line);
	}
	free_str_null(&line);
	exit (0);
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
	t_in_out_fds		*red;

	token = *token_lst;
	cmd = get_last_command(*last_cmd);
	init_cmd_in_out(cmd);
	red = new_node_redirection(REDIR_HEREDOC);
	if(!red)
		return ;
	red->heredoc_delimiter = get_delimiter(token->next->str, &(red->heredoc_quotes));
	fork_heredoc(data, red);
	link_node_redirection(&cmd->io_fds, red);
	if (token->next->next)
		token = token->next->next;
	else
		token = token->next;
	*token_lst = token;
}

