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
#include <errno.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft/libft.h"

extern int g_last_exit_code;

typedef struct s_env{
        char    *name;
        char    *value;
        struct s_env    *previous;
        struct s_env   *next;
}               t_env;


// void    handle_sigint(int sig);

// built-in_functions
int    echo_cmd(char **arg);
int    cd_cmd(char **args, t_env **env);
int    pwd_cmd(char **args);
int    env_cmd(t_env *lst, char **arg);
int    export_cmd(t_env **envrmnt, t_env **export, char **args);
int    unset_cmd(t_env **env, t_env **export, char **args);
int    exit_cmd(char **arg);

void    copy_env(char **env, t_env **list);
void    sort_env(t_env **env);
void    swap_nodes(t_env *lst, t_env **env);

void	link_node(t_env **head, char *line);
int	ft_lstsize(t_env *lst);
t_env	*ft_lstnew(char *line);
void	ft_lstadd_back(t_env **lst, t_env *new);
t_env	*ft_lstlast(t_env *lst);
void	ft_lstclear(t_env **lst);
void	ft_lstdelone(t_env *lst);

//execve
// int    ft_execve(t_env *env, char *cmd, char **args);
// char     *find_program_path(t_env *env, char *cmd);
// char    **env_to_array(t_env *env);

// void	put_quotes_sign(char *line, char *env);
// char	*manage_line(char *line);
// int     ft_names(char *line, char *arg);

// export
// int     ft_same_variable(t_env *lst, char *value);
// int     names_match(char *v1, char *v2);

#endif