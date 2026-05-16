CC = cc
CFLAGS = -Wall -Wextra -Werror

NAME = cub3D

SRCS = main.c ray_casting.c put_texture.c moves.c utils/ft_open.c utils/ft_safe_malloc.c \
		utils/ft_split.c utils/get_next_line.c utils/libft_utils_1.c utils/libft_utils_2.c \
		utils/libft_utils_3.c utils/libft_utils_4.c utils/libft_utils_5.c utils/libft_utils_6.c \
		utils/parsing_instructions_utils1.c utils/parsing_instructions_utils2.c utils/parsing_map_utils_1.c \
		utils/parsing_map_utils_2.c utils/parsing_map_utils_3.c ray_cast_utils.c utils/events_utils.c

OBJ = $(SRCS:.c=.o)

MLX_DIR = mlx
MLX = $(MLX_DIR)/libmlx.a
LIBS = -Lmlx -lmlx -lXext -lX11 -lm

all: $(NAME)

$(MLX):
	make -C $(MLX_DIR)

%.o: %.c cub.h
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(MLX) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(MLX) $(LIBS) -o $(NAME)

clean:
	rm -f $(OBJ)
	make clean -C $(MLX_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean
