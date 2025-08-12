/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaatik <moaatik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 15:35:02 by moaatik           #+#    #+#             */
/*   Updated: 2025/08/12 16:04:43 by moaatik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

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

void clear_img_data(t_game *game, int color)
{
    int total_pixels;
    int bytes_per_pixel;
	int	i;

	total_pixels = SCREEN_WIDTH * SCREEN_HEIGHT;
    bytes_per_pixel = game->bpp / 8;
	i = 0;
    while (i < total_pixels * bytes_per_pixel)
    {
        game->img_data[i + 0] = color & 0xFF;
        game->img_data[i + 1] = (color >> 8) & 0xFF;
        game->img_data[i + 2] = (color >> 16) & 0xFF;
		i += bytes_per_pixel;
    }
}

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
    for (int y = start_y; y <= end_y; y++)
        my_mlx_pixel_put(game, x, y, color);
}

static void	init_ray_params(t_game *game, int ray_index, float start_angle, float angle_step, t_ray *ray)
{
	ray->angle = start_angle + ray_index * angle_step;
	ray->dir_x = cos(ray->angle);
	ray->dir_y = sin(ray->angle);
	ray->x = game->player_x;
	ray->y = game->player_y;
}

static int	cast_ray(t_game *game, t_ray *ray)
{
	int	map_x;
	int	map_y;

	while (1)
	{
		map_x = (int)(ray->x / BLOCK_SIZE);
		map_y = (int)(ray->y / BLOCK_SIZE);
		if (map_x < 0 || map_y < 0 || map_x >= game->max_x || map_y >= game->max_y)
			return (0);
		if (game->map[map_y][map_x] == '1')
			return (1);
		ray->x += ray->dir_x;
		ray->y += ray->dir_y;
	}
}

static void	draw_wall_slice(t_game *game, t_ray *ray, int ray_index)
{
	float	dist;
	int		wall_height;
	int		wall_start;
	int		wall_end;

	dist = sqrt((ray->x - game->player_x) * (ray->x - game->player_x)
			+ (ray->y - game->player_y) * (ray->y - game->player_y));
	wall_height = (int)(BLOCK_SIZE * SCREEN_HEIGHT / dist);
	wall_start = (SCREEN_HEIGHT - wall_height) / 2;
	wall_end = wall_start + wall_height;
	draw_vertical_line(game, ray_index, wall_start, wall_end, 0x006400);
}

void	draw_background(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < SCREEN_HEIGHT / 2)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
			my_mlx_pixel_put(game, x++, y, game->ceiling_color);
		y++;
	}
	y = SCREEN_HEIGHT / 2;
	while (y < SCREEN_HEIGHT)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
			my_mlx_pixel_put(game, x++, y, game->floor_color);
		y++;
	}
}


void	render_3d(t_game *game)
{
	t_ray	ray;
	float	fov;
	float	start_angle;
	float	angle_step;
	int		ray_index;

	fov = 60.0 / 180 * M_PI;
	start_angle = atan2(game->dir_y, game->dir_x) - fov / 2;
	angle_step = fov / SCREEN_WIDTH;
	clear_img_data(game, 0x000000);
	ray_index = 0;
	draw_background(game);
	while (ray_index < SCREEN_WIDTH)
	{
		init_ray_params(game, ray_index, start_angle, angle_step, &ray);
		if (cast_ray(game, &ray))
			draw_wall_slice(game, &ray, ray_index);
		ray_index++;
	}
	mlx_put_image_to_window(game->mlx, game->window, game->img, 0, 0);
	render_map(game);
}

int	key_press(int keycode, t_game *game)
{
	if (keycode == 53)
	{
		mlx_destroy_window(game->mlx, game->window);
		free_strs(game->map);
		exit(0);
	}
	else if (keycode == 13)
		move_forward(game);
	else if (keycode == 1)
		move_backward(game);
	else if (keycode == 123)
		rotate_left(game);
	else if (keycode == 124)
		rotate_right(game);
	else if (keycode == 0 )
		move_right(game);
	else if (keycode == 2)
		move_left(game);
	else
		return (0);
	render_3d(game);
	return (0);
}

int	handle_cross(t_game *game)
{
	mlx_destroy_window(game->mlx, game->window);
	free_strs(game->map);
	exit(0);
	return (0);
}

int main(int ac, char **av)
{
	t_game	game;

	(void)ac;

	game.map = input(av);
	if (!game.map)
		return (1);

	game.mlx = mlx_init();
	if (!game.mlx)
		return (1);

	get_map_info(&game);

	game.window = mlx_new_window(game.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D");
	if (!game.window)
		return (1);
	
	game.img = mlx_new_image(game.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	game.img_data = mlx_get_data_addr(game.img, &game.bpp, &game.size_line, &game.endian);

	render_3d(&game);

	mlx_hook(game.window, 2, 0, key_press, &game);
	mlx_hook(game.window, 17, 0, handle_cross, &game);
	mlx_loop(game.mlx);
	return (0);
}
