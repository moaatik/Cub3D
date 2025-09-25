/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaatik <moaatik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 16:57:56 by moaatik           #+#    #+#             */
/*   Updated: 2025/09/22 15:49:57 by moaatik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	init_ray(t_game *game, int ray_index, float start_angle,
	float angle_step)
{
	game->ray.angle = start_angle + ray_index * angle_step;
	game->ray.dir_x = cos(game->ray.angle);
	game->ray.dir_y = sin(game->ray.angle);
	game->ray.x = game->player.x;
	game->ray.y = game->player.y;
}

void	init_step(t_game *game)
{
	if (game->ray.dir_x < 0)
	{
		game->cast.step_x = -1;
		game->cast.side_dist_x = (game->player.x / BLOCK_SIZE - game->cast.map_x) * (game->cast.dist_x);
	}
	else
	{
		game->cast.step_x = 1;
		game->cast.side_dist_x = (game->cast.map_x + 1.0f - game->player.x / BLOCK_SIZE) * (game->cast.dist_x);
	}
	if (game->ray.dir_y < 0)
	{
		game->cast.step_y = -1;
		game->cast.side_dist_y = (game->player.y / BLOCK_SIZE - game->cast.map_y) * (game->cast.dist_y);
	}
	else
	{
		game->cast.step_y = 1;
		game->cast.side_dist_y = (game->cast.map_y + 1.0f - game->player.y / BLOCK_SIZE) * (game->cast.dist_y);
	}
}

void	init_dda(t_game *game)
{
	game->cast.map_x = (int)(game->player.x / BLOCK_SIZE);
	game->cast.map_y = (int)(game->player.y / BLOCK_SIZE);
	game->cast.dist_x = fabs(1.0f / game->ray.dir_x);
	game->cast.dist_y = fabs(1.0f / game->ray.dir_y);
	init_step(game);
}

int	perform_dda(t_game *game)
{
	game->side = 0;
	while (1)
	{
		if (game->cast.side_dist_x < game->cast.side_dist_y)
		{
			game->cast.side_dist_x += game->cast.dist_x;
			game->cast.map_x += game->cast.step_x;
			game->side = 0;
		}
		else
		{
			game->cast.side_dist_y += game->cast.dist_y;
			game->cast.map_y += game->cast.step_y;
			game->side = 1;
		}
		if (game->cast.map_x < 0 || game->cast.map_y < 0
			|| game->cast.map_x >= game->max_x
			|| game->cast.map_y >= game->max_y)
			return (0);
		if (game->map[game->cast.map_y][game->cast.map_x] == '1')
			return (1);
	}
}

float	distance(t_game *game)
{
	float	dist;
	float	player_cell_x;
	float	player_cell_y;
	float	dist_world;

	if (game->side == 0)
	{
		player_cell_x = game->player.x / BLOCK_SIZE;
		dist = (game->cast.map_x - player_cell_x + (1 - game->cast.step_x) / 2)
			/ game->ray.dir_x;
	}
	else
	{
		player_cell_y = game->player.y / BLOCK_SIZE;
		dist = (game->cast.map_y - player_cell_y + (1 - game->cast.step_y) / 2)
			/ game->ray.dir_y;
	}
	dist_world = dist * BLOCK_SIZE;
	game->ray.x = game->player.x + game->ray.dir_x * dist_world;
	game->ray.y = game->player.y + game->ray.dir_y * dist_world;
	dist_world *= game->player.dir_x * game->ray.dir_x + game->player.dir_y
		* game->ray.dir_y;
	return (dist_world);
}

float	cast_ray(t_game *game)
{
	init_dda(game);
	if (!perform_dda(game))
		return (-1);
	return (distance(game));
}

void	render_game(t_game *game)
{
	float	fov;
	float	start_angle;
	float	angle_step;
	int		ray_index;
	float	dist;

	fov = 60.0f * (M_PI / 180.0f);
	start_angle = atan2f(game->player.dir_y, game->player.dir_x) - fov / 2.0f;
	angle_step = fov / (float)SCREEN_WIDTH;
	ray_index = 0;
	while (ray_index < SCREEN_WIDTH)
	{
		init_ray(game, ray_index, start_angle, angle_step);
		dist = cast_ray(game);
		if (dist > 0)
			draw_wall_slice(game, ray_index, dist);
		ray_index++;
	}
	mlx_put_image_to_window(game->mlx, game->window, game->img, 0, 0);
}
