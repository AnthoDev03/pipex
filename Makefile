NAME = pipex

CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRCS = srcs/main.c \
       srcs/find_path.c \
       srcs/out_in.c

OBJS = $(SRCS:.c=.o)

HEADER = includes/pipex.h

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(HEADER)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L$(LIBFT_DIR) -lft

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(OBJS): %.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -Iincludes -c $< -o $@

clean:
	rm -f $(OBJS)
	@make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re

