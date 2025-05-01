# Nom de l'exécutable
NAME	= minishell

# Fichiers sources
SRCS	= 	./lexification/test1.c \
			./lexification/util1.c \
			./lexification/syntax_errors.c \
			./lexification/print_errors.c \
			./lexification/check_if_var.c \
			./lexification/lst_utils.c \
			./lexification/lst_utils2.c \
			./lexification/parsing_input.c \
			./expansion/delete_quotes.c \
			./expansion/expand_variable.c \
			./expansion/expand_variable1.c \
			./expansion/extract_variable.c \
			./expansion/get_value_var.c \
			./expansion/process_handel_quotes.c \
			./expansion/replace_heredoc_var.c \
			./parsing/cmd_free_utils.c \
			./parsing/handle_append.c \
			./parsing/handle_word.c \
			./parsing/create_cmd.c \
			./parsing/init_struct_cmd.c \
			./parsing/fill_args1.c \
			./parsing/handle_input.c \
			./parsing/preparing_lst_commande.c \
			./parsing/fill_args2.c \
			./parsing/handle_pipe.c \
			./parsing/free_utils1.c \
			./parsing/handle_trunc.c \
			./parsing/signal.c \
			./parsing/handle_heredoc.c \
			./parsing/exit.c \
			./parsing/validate_startup_argss.c \
			./parsing/main1.c \
			./parsing/print_cmd_token_list.c \
			./execution/built_in.c \
			./execution/built_in2.c \
			./execution/cd_cmd.c \
			./execution/export.c \
			./execution/export2.c \
			./execution/fork.c \
			./execution/linked_list.c \
			./execution/linked_list2.c \
			./execution/local_vars.c \
			./execution/local_vars2.c \
			./execution/main.c

# Objets
OBJS	= $(SRCS:.c=.o)

# Options de compilation
FLAGS	= -Wall -Wextra -Werror
CC		= cc

# Bibliothèque libft
LIBFT	= ./libft/libft.a

# Compilation principale
$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME) $(LIBFT) -lreadline

# Compilation de libft si nécessaire
$(LIBFT):
	make -C ./libft

# Compilation de tous les fichiers
all: $(NAME)

# Nettoyage des fichiers objets
clean:
	rm -rf $(OBJS)
	make -C ./libft clean

# Nettoyage total (exécutable + objets)
fclean: clean
	rm -rf $(NAME)
	make -C ./libft fclean

# Recompilation propre
re: fclean all

.PHONY: all clean fclean re
