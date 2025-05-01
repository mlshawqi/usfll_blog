NAME = libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
RM = rm -f

FILES = ft_memset \
		ft_bzero \
		ft_memcpy \
		ft_memmove \
		ft_memchr \
		ft_memcmp \
		ft_strlen \
		ft_strlcpy \
		ft_strlcat \
		ft_strchr \
		ft_strrchr \
		ft_strnstr \
		ft_strncmp \
		ft_atoi \
		ft_isalpha \
		ft_isdigit \
		ft_isalnum \
		ft_isascii \
		ft_isprint \
		ft_toupper \
		ft_tolower \
		ft_calloc \
		ft_substr \
		ft_strjoin \
		ft_strtrim \
		ft_striteri \
		ft_split \
		ft_itoa \
		ft_strmapi \
		ft_putchar_fd \
		ft_putstr_fd \
		ft_putendl_fd \
		ft_putnbr_fd \
		ft_strdup \
		ft_isspace \
		ft_strcmp

FILES_B = 	ft_lstnew_bonus \
	  		ft_lstadd_front_bonus \
	  		ft_lstsize_bonus \
	  		ft_lstlast_bonus \
	  		ft_lstadd_back_bonus \
	  		ft_lstdelone_bonus \
	  		ft_lstclear_bonus \
	  		ft_lstiter_bonus \
	  		ft_lstmap_bonus

SRCS = $(addsuffix .c, $(FILES))
SRCS_B = $(addsuffix .c, $(FILES_B))

OBJS = $(addsuffix .o, $(FILES))
OBJS_B = $(addsuffix .o, $(FILES_B))

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $@ $^

bonus: $(OBJS_B)
	$(AR) $(NAME) $^

clean:
	$(RM) $(OBJS) $(OBJS_B)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: bonus all clean fclean re
