/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendring.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaatik <moaatik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 16:57:56 by moaatik           #+#    #+#             */
/*   Updated: 2025/08/12 19:06:21 by moaatik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

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

static void	init_ray(t_game *game, int ray_index, float start_angle, float angle_step, t_ray *ray)
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
		map_x = (int)(ray->x / (BLOCK_SIZE));
		map_y = (int)(ray->y / (BLOCK_SIZE));
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
	draw_vertical_line(game, ray_index, wall_start, wall_end, 0x005000);
}

void	render_game(t_game *game)
{
	t_ray	ray;
	float	fov;
	float	start_angle;
	float	angle_step;
	int		ray_index;

	fov = 60.0 / 180 * M_PI;
	start_angle = atan2(game->dir_y, game->dir_x) - fov / 2;
	angle_step = fov / SCREEN_WIDTH;
	ray_index = 0;
	draw_background(game);
	while (ray_index < SCREEN_WIDTH)
	{
		init_ray(game, ray_index, start_angle, angle_step, &ray);
		if (cast_ray(game, &ray))
			draw_wall_slice(game, &ray, ray_index);
		ray_index++;
	}
	mlx_put_image_to_window(game->mlx, game->window, game->img, 0, 0);
	render_map(game);
}
