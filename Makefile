SRCS = main.c ray_casting.c put_texture.c moves.c utils/ft_open.c utils/ft_safe_malloc.c \
		utils/ft_split.c utils/get_next_line.c utils/libft_utils_1.c utils/libft_utils_2.c \
		utils/libft_utils_3.c utils/libft_utils_4.c utils/libft_utils_5.c utils/libft_utils_6.c \
		utils/parsing_instructions_utils1.c utils/parsing_instructions_utils2.c utils/parsing_map_utils_1.c \
		utils/parsing_map_utils_2.c utils/parsing_map_utils_3.c ray_cast_utils.c utils/events_utils.c

OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror

NAME = cub3D

all: $(NAME)

%.o: %.c cub.h
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -lmlx -framework OpenGL -framework AppKit -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean
