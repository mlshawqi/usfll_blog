#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <errno.h>
#include <signal.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>
# include <sys/types.h>
#include "./libft/libft.h"
#include <sys/stat.h>


#define SUCCESS 0
#define FAILURE 1
// # define HEREDOC_NAME "/temporary_"

# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

# define MAX_LONG 9223372036854775807ULL
# define MIN_LONG 9223372036854775808ULL

extern int g_last_exit_code;

typedef struct s_separation
{	
	char			*str;
	char			*str_copy;
	// bool			var_exists;
	bool			is_var;
	int				type;
	int				status;
	bool			join;
	struct s_separation	*prev;
	struct s_separation	*next;
}	t_separation;

typedef enum s_redirection
{
	REDIR_IN,     // <
	REDIR_OUT,    // >
	REDIR_APPEND, // >>
	REDIR_HEREDOC // <<
}		t_redirections;

typedef struct s_in_out_fds
{
	t_redirections		type;
	int			fd;
	char			*heredoc_delimiter;
	bool			heredoc_quotes;
	struct s_in_out_fds	*next;
	char	*filename;

	// char	*outfile;
	// int		fd_heredoc;
	// int		fd_in;
	// int		fd_out;
}	t_in_out_fds;

typedef	struct s_pipex
{
	int		fork_pid;
	int		status;
	char		*path;
}		t_pipex;

typedef struct s_cmd
{
	char				*command;
	char				**args;
	bool				pipe_output;
	t_in_out_fds			*io_fds;
	t_pipex		*pipex;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

typedef struct s_env {
    char *name;            // Nom de la variable (ex: "PATH")
    char *value;           // Valeur de la variable (ex: "/usr/bin:/bin")
    struct s_env *previous;
    struct s_env *next;
} t_env;

typedef struct s_data
{
	bool		interactive;
	t_separation		*token;
	char		*user_input;
	t_env		*export;
	t_env		*env;
	char		**env_arr;
	char		*pwd;
	// char		*working_dir;
	// char		*old_working_dir;
	t_cmd	*cmd;
}	t_data;



enum e_token_types {
	SPACES = 1,
	WORD,
	VAR,
	PIPE,
	INPUT,
	TRUNC,
	HEREDOC,
	APPEND,
	END,
	AMPER
};

enum e_quoting_status {
	DFLT,
	SQUOTE,
	DQUOTE
};
//util1.c
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s);
void	ft_putendl_fd(char *s, int fd);
void	ft_putstr_fd(char *s, int fd);
char	*ft_strjoin(char const *s1, char const *s2);
void	free_str(void *str);

//test1.c
t_separation	*ft_new_token(char *str, char *str_backup, int type, int status);
void	add_token(t_separation **lst, t_separation *new_token);
int	malloc_separator(t_separation **token_lst, char *str, int index, int type);
int	malloc_word(t_separation **token_lst, char *str, int index, int start);
int	is_separator(char *str, int i);
int	find_status(int status, char *str, int i);
int	malloc_word_separator(int *i, char *str, int start, t_data *data);
int	tokenization(t_data *data, char *str);
void print_tokens(t_separation *token_lst);
void free_token_list(t_separation **token_list);

//// print_errors
char *concatenate_strings(char *base, const char *suffix);
void display_error_message(char *error_text, const char *info, int use_quotes);
int print_command_error(char *command, char *detail, char *error_message, int error_code);
bool	usage_message(bool return_val);

////syntax_errors
bool	has_consecutive_ops(t_separation *node);
int	check_errors_rep(t_separation **token_lst);

/////////check_if_var
void	check_for_variable(t_separation **token);
int	var_checker(t_separation **token_list);

///////////lst_utils
void	delete_token(t_separation *token, void (*del)(void *));
void	clear_token_list(t_separation **list, void (*del)(void *));

/////////lst_utils2
void	connect_nodes(t_separation *to_remove, t_separation *current, t_separation *new_nodes);
t_separation *replace_in_list(t_separation **head, t_separation *to_remove, t_separation *new_nodes);

///////////parising_input 
bool	process_user_input(t_data *data);

////////expansion
int delete_quotes(t_separation **token);
int expand_variables(t_data *data, t_separation **tokens);
char *expand_heredoc_variables(t_data *data, char *str);
void insert_var_value(char *new_str, char *var_value, int *pos);
char *construct_new_string(char *old_str, char *var_value, int new_size, int index);
bool is_valid_var_char(char c);
int get_var_length(char *str);
char *extract_variable(char *str);
// char *get_value(t_separation *token, char *str, t_data *data);
char *get_value(t_separation *token, char *str, t_env *env_list);
int calculate_new_length(char *str, int count, int i);
bool contains_quotes(char *str);
int process_quotes(t_data *data);
int replace_variable(t_separation **token, char *value, int idx);
char *replace_heredoc_var(char *str, char *value, int idx);

////////////////////Parsing
bool	process_user_input(t_data *data);
void free_command(t_cmd *cmd);
void free_command_list(t_cmd **cmd_list);
void	initialize_no_arg_commands(t_data *data);
void	ft_create_commands(t_data *data, t_separation *token);
int count_token_args(t_separation *node);
int initialize_default_args(t_separation **token_node, t_cmd *cmd);
char **extend_args_with_tokens(int existing_len, char **new_args, t_cmd *cmd, t_separation **token_node);
int append_default_args(t_separation **token_node, t_cmd *cmd);
int process_command_args(t_separation **token_node, t_cmd *last_cmd);
char *combine_vars(t_separation **token_node);
int count_arguments(t_separation *current_token);
char **copy_args_to_new_tab(int existing_len, char **new_args, t_cmd *last_cmd, t_separation *current_token);
void remove_empty_variables(t_separation **tokens);
int initialize_echo_arguments(t_separation **token_node, t_cmd *last_cmd);
int append_echo_arguments(t_separation **token_node, t_cmd *last_cmd);
void free_in_out(t_in_out_fds *io);
void free_string_array(char **array);
void	open_output_file_append(t_in_out_fds *io, char *file, char *original_filename);
void	handle_append_redirection(t_cmd **last_cmd, t_separation **token_lst);
char	*build_string_from_array(char **array);
char	*expand_variable_in_line(t_data *data, char *line);
bool	check_heredoc_line(t_data *data, char **line, t_in_out_fds *io, bool *success);
int	write_heredoc_input(t_data *data, t_in_out_fds *io, int fd);
bool	activate_heredoc(t_data *data, t_in_out_fds *io);
char	*generate_heredoc_name(void);
char	*get_delimiter(char *delim, bool *quotes);
void	process_heredoc(t_data *data, t_cmd **last_cmd, t_separation **token_lst);
bool	clean_up_old_file_ref(t_in_out_fds *io, bool is_input);
void	open_input_file(t_in_out_fds *io, char *file, char *original_filename);
void	handle_input_redirection(t_cmd **last_cmd, t_separation **token_lst);
void handle_pipe(t_cmd **cmd, t_separation **token_list);
char	*get_relative_path(char *file_to_open);
void	open_outfile_trunc(t_in_out_fds *io, char *file, char *var_filename);
void	parse_trunc(t_cmd **last_cmd, t_separation **token_lst);
bool has_space(const char *str);
void split_variable_command(t_cmd *last_cmd, const char *cmd_str);
void parse_word_token(t_cmd **cmd, t_separation **token_lst);
void	init_cmd_in_out(t_cmd *cmd);
void	init_command(t_cmd **cmd);
t_cmd	*create_command(bool pipe_output);
void	add_command_to_list(t_cmd **list, t_cmd *new_cmd);
t_cmd	*get_last_command(t_cmd *cmd);
// bool redirecte_io(t_in_out_fds *io);
bool apply_io_redirection(t_in_out_fds *io);
bool validate_io_files(t_in_out_fds *io);
void	reset_input_prompt(int signo);
void	configure_interactive_signals(void);
void	handle_signal_newline(int signo);
void	configure_noninteractive_signals(void);
void	ignore_quit_signal(void);
int	ft_counter_env(char **env);
bool	ft_initialise_env(t_data *data, char **env);
char	*gft_env_value(char **env, char *var);
// int	ft_env_index(char **env, char *var);
// bool	ft_initialise_wds(t_data *data);
bool	ft_initialise_data(t_data *data, char **env);
// void	close_pipe_fds(t_cmd *cmds, t_cmd *skip_cmd);
void	close_files_descriptors(t_cmd *cmds, bool close);
void	cleanup_shell_data(t_data *data, bool clear_history);
void	exit_shell(t_data *data, int exno);
bool	validate_startup_args(t_data *data, int ac, char **av);
void	display_command_arguments(t_cmd *cmd);
void	display_command_redirections(t_cmd *cmd);
void	display_pipeline_commands(t_data *data);
void	display_token_type(t_separation *token, const char *prefix);
void	display_token_list(t_separation **tokens);
void	configure_interactive_signals_herdoc(void);


//execution
// built-in_functions
int    echo_cmd(char **arg);
int    cd_cmd(char **args, t_env **env, t_data *data);
int    pwd_cmd(t_data *data, char **args);
int    env_cmd(t_env *lst, char **arg);
int    export_cmd(t_data *data, t_env **envrmnt, t_env **export, char **args);
int    unset_cmd(t_env **env, t_env **export, char **args);
int    exit_cmd(t_data *data, char **arg);

int	fork_heredoc(t_data *data, t_in_out_fds *io);
void    handle_sigint_heredoc(int sig);
void	link_node_redirection(t_in_out_fds **head, t_in_out_fds	*new_node);
t_in_out_fds    *new_node_redirection(t_redirections type);

void    copy_env(char **env, t_env **list);
void    sort_env(t_env **env);
void    swap_nodes(t_env *lst, t_env **env);
void  export_var(t_env **lst, char *var);
int     appand_value(t_env *tmp, char *arg);
t_env    *new_node(char *arg);

void	link_node(t_env **head, t_env *new_node);
int	ft_lstsize(t_env *lst);
t_env	*ft_lstnew(char *line);
void	ft_lstadd_back(t_env **lst, t_env *new);
t_env	*ft_lstlast(t_env *lst);
void	ft_lstclear(t_env **lst);
void	ft_lstdelone(t_env *lst);
long long	ft_atoii(const char *str);

void	execution_cleanup(t_data *data);

//execve
int     run_builtin_if_exists(t_data *data, t_cmd *cmd);
char     *find_program_path(t_env *env, char *cmd);
char    **env_to_array(t_env *env);
int    execution(t_data *data);
int    ft_execve(t_data *data, t_cmd *cmd);
int    handle_redirections(t_data *data, t_cmd *tmp);
int     dup_redirect(t_in_out_fds *redirect);
int     init_env_arr(t_data *data);
int    execute_with_pipes(t_data *data, int npipe);
int     **allocate_pipes(int count);
void    free_tab(int **arr, int i);
int    handle_child_process(t_data *data, t_cmd *cmd, int **pipes, int i, int count);
int    execute_command(t_data *data, t_cmd *cmd);
void    close_pipes(int **pipes,int count);
int     wait_for_all(t_data *data);
void    handle_sigint_pipe(int sig);
int    ft_execve_pipe(t_data *data, t_cmd *cmd);
int    handle_pipe_redirections(t_data *data, t_cmd *cmd);
int     init_or_count_pipes(t_cmd *cmd, int hint);
int	malloc_error(const char *context);
void    print_cmd_error(const char *cmd, const char *msg, char *option);
char    *valid_path(char *str, char *cmd);
char     *relative_path(t_env *env, char *cmd);
void    free_str_null(char **str);
void	set_signals(void);
void    free_pipes(int **arr);
void    init_env_defaults(t_data *data);
void    set_shell_lvl(t_env *env);
void    handle_fork_sig(int sig);


#endif