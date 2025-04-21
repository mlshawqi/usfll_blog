#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <stdbool.h>
#include <errno.h>
#include <signal.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft/libft.h"


typedef struct s_env{
        char    *line;
        struct s_env    *previous;
        struct s_env   *next;
}               t_env;

// built-in_functions
void    echo_cmd(char *str);
void    cd_cmd(char *path);
void	link_node(t_env **head, char *line, char hint);
void    env_cmd(t_env *lst);
void    export_cmd(t_env **envrmnt, char *value);
void    unset_cmd(t_env **env, char *args);

int	ft_lstsize(t_env *lst);
t_env	*ft_lstnew(char *content, char hint);
void	ft_lstadd_back(t_env **lst, t_env *new);
t_env	*ft_lstlast(t_env *lst);
void	put_quotes_sign(char *line, char *env);
char	*manage_line(char *line);

// export
void    copy_env(char **env, t_env **list, t_env *envr, char hint);
void    sort_env(t_env *env);
int     ft_same_variable(t_env *lst, char *value);
int     names_match(char *v1, char *v2);
void    swap_nodes(t_env *lst, t_env **env);

#endif