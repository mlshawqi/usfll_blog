# SRC = libft/ft_lstnew_bonus.c libft/ft_lstsize_bonus.c libft/ft_lstadd_front_bonus.c \
# 	   libft/ft_lstadd_back_bonus.c libft/ft_lstlast_bonus.c libft/ft_lstclear_bonus.c \
# 	   libft/ft_lstiter_bonus.c libft/ft_lstdelone_bonus.c libft/ft_lstmap_bonus.c \
	  
SRC =	main.c linked_list.c built_in.c libft/ft_strcmp.c libft/ft_strlcpy.c \
	libft/ft_strlen.c libft/ft_strchr.c libft/ft_strjoin.c libft/ft_strdup.c \
	linked_list2.c libft/ft_strncmp.c export.c built_in2.c cd_cmd.c export2.c \
	libft/ft_isdigit.c libft/ft_atoi.c execve.c libft/ft_split.c

CC = cc
CFLAGS = -Wall -Wextra -Werror 
FLAGSS = -lreadline
NAME = minishelll

SRC_O = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(SRC_O)
	$(CC) $(CFLAGS) $(SRC_O) $(FLAGSS) -o $(NAME)

clean:
	rm -f $(SRC_O)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY : all clean fclean re
.SECONDARY : $(SRC_O)