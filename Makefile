NAME = pipex

CC = gcc
CFLAGS = -Wall -Wextra -Werror 
SRCS = srcs/main.c \
       srcs/utils.c \
       srcs/utils_b.c \
       srcs/ft_split.c

OBJS = $(SRCS:.c=.o)

HEADER = includes/pipex.h


all: $(NAME)

$(NAME): $(OBJS) $(HEADER) 
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJS): %.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
