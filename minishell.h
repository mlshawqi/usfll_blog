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
#include <errno.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft/libft.h"


typedef struct s_env{
        char    *line;
        struct s_env    *previous;
        struct s_env   *next;
}               t_env;

typedef struct s_local_var{
        char    *name;
        char    *value;
        struct s_local_var *prev;
        struct s_local_var *next;
}               t_local_var;

void    handle_sigint(int sig);

// built-in_functions
void    echo_cmd(char *str);
void    cd_cmd(char *path, t_env **env);
void    pwd_cmd();
void	link_node(t_env **head, char *line, char hint);
void    env_cmd(t_env *lst);
void    export_cmd(t_env **envrmnt, char *value);
void    unset_cmd(t_env **env, char *args);
void    update_pwd(t_env **env, char *path, char hint);

int	ft_lstsize(t_env *lst);
t_env	*ft_lstnew(char *content, char hint);
void	ft_lstadd_back(t_env **lst, t_env *new);
t_env	*ft_lstlast(t_env *lst);
void	ft_lstclear(t_env **lst);
void	ft_lstdelone(t_env *lst);
void	put_quotes_sign(char *line, char *env);
char	*manage_line(char *line);
int     ft_names(char *line, char *arg);

// export
void    copy_env(char **env, t_env **list, t_env *envr, char hint);
void    sort_env(t_env *env);
int     ft_same_variable(t_env *lst, char *value);
int     names_match(char *v1, char *v2);
void    swap_nodes(t_env *lst, t_env **env);

#endif