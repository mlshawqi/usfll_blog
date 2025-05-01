#include "../minishell.h"

char	*concatenate_strings(char *base, const char *suffix)
{
	char	*result;

	if (!suffix)
		return (base);
	if (!base)
		return (ft_strdup(suffix));
	result = ft_strjoin(base, suffix);
	free_str(base);
	return (result);
}

static bool	needs_quotes(char *command)
{
	return (ft_strncmp(command, "export", 7) == 0
		|| ft_strncmp(command, "unset", 6) == 0);
}

int	print_command_error(char *command, char *detail,
		char *error_message, int error_code)
{
	char	*msg;
	bool	use_quotes;

	use_quotes = needs_quotes(command);
	msg = ft_strdup("minishell: ");
	if (command)
	{
		msg = concatenate_strings(msg, command);
		msg = concatenate_strings(msg, ": ");
	}
	if (detail)
	{
		if (use_quotes)
			msg = concatenate_strings(msg, "`");
		msg = concatenate_strings(msg, detail);
		if (use_quotes)
			msg = concatenate_strings(msg, "'");
		msg = concatenate_strings(msg, ": ");
	}
	msg = concatenate_strings(msg, error_message);
	ft_putendl_fd(msg, STDERR_FILENO);
	free_str(msg);
	return (error_code);
}

void	display_error_message(char *error_text,
		const char *info, int use_quotes)
{
	char	*msg;

	msg = ft_strdup("minishell: ");
	msg = concatenate_strings(msg, error_text);
	if (use_quotes)
		msg = concatenate_strings(msg, " `");
	else
		msg = concatenate_strings(msg, ": ");
	msg = concatenate_strings(msg, info);
	if (use_quotes)
		msg = concatenate_strings(msg, "'");
	ft_putendl_fd(msg, STDERR_FILENO);
	free_str(msg);
}

bool	usage_message(bool return_val)
{
	ft_putendl_fd("Usage: ./minishell", 2);
	ft_putendl_fd("Usage: ./minishell -c \"input line\"", 2);
	return (return_val);
}

