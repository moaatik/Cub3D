/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendring_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaatik <moaatik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 17:00:06 by moaatik           #+#    #+#             */
/*   Updated: 2025/08/16 18:48:58 by moaatik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void my_mlx_pixel_put(t_game *game, int x, int y, int color)
{
    if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
        return;
    char *dst = game->img_data + (y * game->size_line + x * (game->bpp / 8));
    dst[0] = color & 0xFF;
    dst[1] = (color >> 8) & 0xFF;
    dst[2] = (color >> 16) & 0xFF;
}

void draw_vertical_line(t_game *game, int x, int start_y, int end_y, int color)
{
    while (start_y <= end_y)
        my_mlx_pixel_put(game, x, start_y++, color);
}

void *create_colored_tile(t_game *game, int r, int g, int b, int size)
{
	void    *img;
	char    *data;
	int     bpp;
	int     size_line;
	int     endian;
	int		y;
	int		x;

	img = mlx_new_image(game->mlx, size, size);
	data = mlx_get_data_addr(img, &bpp, &size_line, &endian);
	y = 0;
	while (y < size)
	{
		x = 0;
		while (x < size)
		{
			int i = y * size_line + x * (bpp / 8);
			data[i + 0] = b;
			data[i + 1] = g;
			data[i + 2] = r;
			x++;
		}
		y++;
	}
	return (img);
}

void draw_ray(t_game *game, float scale)
{
	float ray_x = game->player_x;
	float ray_y = game->player_y;


	int	i = 0;
	while (i < 50)
	{
		int map_x = (int)(ray_x / BLOCK_SIZE);
		int map_y = (int)(ray_y / BLOCK_SIZE);
		if (map_y < 0 || map_x < 0 || map_y >= game->max_y || map_x >= game->max_x)
			break;
		if (game->map[map_y][map_x] == '1')
			break;
		mlx_pixel_put(game->mlx, game->window, (int)(ray_x * scale), (int)(ray_y * scale), 0xFF0000);
		ray_x += game->dir_x;
		ray_y += game->dir_y;
		i++;
	}
}

void	render_map(t_game *game)
{
	int		i;
	int		j;
	void	*floor_img;
	void	*wall_img;
	void	*player_img;
	float	scale;

	scale = 8.0 / BLOCK_SIZE;

	floor_img = create_colored_tile(game, 0, 0, 0, 8);
	wall_img = create_colored_tile(game, 0, 208, 0, 8);
	player_img = create_colored_tile(game, 255, 0, 0, 3);
	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			char tile = game->map[i][j];
			if (tile == '0')
				mlx_put_image_to_window(game->mlx, game->window, floor_img, j * 8, i * 8);
			if (tile == '1')
				mlx_put_image_to_window(game->mlx, game->window, wall_img, j * 8, i * 8);
			j++;
		}
		i++;
	}

	int player_minimap_x = (int)(game->player_x * scale) - 1;
	int player_minimap_y = (int)(game->player_y * scale);

	mlx_put_image_to_window(game->mlx, game->window, player_img, player_minimap_x, player_minimap_y);
	mlx_destroy_image(game->mlx, floor_img);
	mlx_destroy_image(game->mlx, wall_img);
	mlx_destroy_image(game->mlx, player_img);
	draw_ray(game, scale);
}
