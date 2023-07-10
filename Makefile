NAME = pipex

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
LFLAGS = -Llibft -lft 
SRCS = srcs/main.c 

OBJS = $(SRCS:.c=.o)

HEADER = includes/pipex.h

LIBFT = libft/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(HEADER) $(LIBFT) 
	$(CC) $(CFLAGS) $(OBJS) $(LFLAGS) -o $(NAME)

$(OBJS): %.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	make -C libft/

clean:
	rm -f $(OBJS)
	make -C libft/ clean

fclean: clean
	rm -f $(NAME)
	make -C libft/ fclean

re: fclean all

.PHONY: all clean fclean re
