/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils_6.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenmoha <hbenmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 08:30:58 by hbenmoha          #+#    #+#             */
/*   Updated: 2025/11/16 22:06:40 by hbenmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

//* get the color from map + convert it to (int)
int	get_color_from_map(char *line)
{
	char	*color_str;
	char	**rgb_strs;
	int		words_nb;
	int		i;

	i = 0;
	color_str = trim_spaces(line);
	while (color_str[i])
	{
		if ((color_str[i] < '0' || color_str[i] > '9') \
		&& color_str[i] != ',' && (color_str[i] < 9 \
		|| color_str[i] > 13) && color_str[i] != 32)
			error_exit("Error\nRGB is not correct!\n");
		i++;
	}
	rgb_strs = ft_split(color_str, ',', &words_nb);
	if (words_nb != 3 || ft_count_char(color_str, ',', 2))
		error_exit("Error\nRGB is not correct!\n");
	return (convert_rgb_from_str_to_int(rgb_strs));
}

//* check if the path exist + accessible
void	check_path_exist(char *path)
{
	int	path_fd;

	path_fd = ft_open(path, O_RDONLY, CREATE_FD);
	close(path_fd);
}

//* init t_game struct
void	init_game_struct(t_game *game)
{
	ft_bzero(game, sizeof(*game));
	game->ceiling_color = -1;
	game->floor_color = -1;
	game->sprint = 1;
	game->mlx = mlx_init();
	if (!game->mlx)
		error_exit("mlx_init failed\n");
}

//* init MLX ptr + window ptr + image ptr + get data addr
void	mlx_data_init(t_game *game)
{
	game->window = mlx_new_window(\
		game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D");
	if (!game->window)
		error_exit("mlx_new_window failed\n");
	game->img = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!game->img)
		error_exit("mlx_new_image failed\n");
	game->address = mlx_get_data_addr(game->img, \
		&game->bpp, &game->size_line, &game->endian);
	if (!game->address)
		error_exit("mlx_get_data_addr failed\n");
}

//* check current char ( neighboor ) if it's not a 32 nor  '\0'
void	check_current_neighboor(char current_char)
{
	if (current_char != 32 && current_char)
		error_exit("Error\nForbidden character in map\n");
	error_exit("Error\nMap is not closed\n");
}
