SRCS = main.c parsing/map_parsing.c parsing/parsing_utils.c parsing/ft_safe_malloc.c parsing/ft_open.c parsing/get_next_line.c parsing/ft_split.c

OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

NAME = cub3D

all: $(NAME)

%.o: %.c cub.h
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean
