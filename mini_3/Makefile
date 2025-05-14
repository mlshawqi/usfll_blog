NAME	= minishell

# Fichiers sources
SRCS	= 	./lexification/test1.c \
			./lexification/util1.c \
			./lexification/syntax_errors.c \
			./lexification/print_errors.c \
			./lexification/check_if_var.c \
			./lexification/lst_utils.c \
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

SRC_EXECUTION = ./execution/linked_list.c ./execution/linked_list2.c ./execution/built_in.c \
	./execution/export_cmd.c ./execution/echo_cmd.c ./execution/cd_cmd.c ./execution/execve.c \
	./execution/export2_cmd.c ./execution/exit_cmd.c ./execution/unset_cmd.c  ./execution/execute1.c\
	./execution/ft_atoi2.c  ./execution/execute.c ./execution/pipe_utils.c ./execution/pipe_utils1.c\
	./execution/error_print.c ./execution/heredoc2.c ./execution/empty_env.c\
	# ./execution/libft/ft_strcmp.c ./execution/libft/ft_strlcpy.c ./execution/libft/ft_isdigit.c \
	# ./execution/libft/ft_strchr.c ./execution/libft/ft_split.c \
	# .execution/libft/ft_strjoin.c ./execution/libft/ft_strdup.c./execution/libft/ft_strlen.c

# Objets
OBJS	= $(SRCS:.c=.o)
OBJS_EXECUTION = $(SRC_EXECUTION:.c=.o)

# Options de compilation
FLAGS	= -Wall -Wextra -Werror #-g3 -fsanitize=address
CC		= cc

# Bibliothèque libft
LIBFT	= ./libft/libft.a

# Compilation principale
$(NAME): $(LIBFT) $(OBJS) $(OBJS_EXECUTION)
	$(CC) $(FLAGS) $(OBJS) $(OBJS_EXECUTION) -o $(NAME) $(LIBFT) -lreadline

# Compilation de libft si nécessaire
$(LIBFT):
	make -C ./libft

# Compilation de tous les fichiers
all: $(NAME)

# Nettoyage des fichiers objets
clean:
	rm -rf $(OBJS)
	rm -rf $(OBJS_EXECUTION)
	make -C ./libft clean

# Nettoyage total (exécutable + objets)
fclean: clean
	rm -rf $(NAME)
	make -C ./libft fclean

# Recompilation propre
re: fclean all

.PHONY: all clean fclean re