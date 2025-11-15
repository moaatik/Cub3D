/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaatik <moaatik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 16:57:56 by moaatik           #+#    #+#             */
/*   Updated: 2025/10/03 10:32:28 by moaatik          ###   ########.fr       */
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

void init_dda(t_game *game)
{
    game->cast.map_x = (int)(game->player.x / BLOCK_SIZE);
    game->cast.map_y = (int)(game->player.y / BLOCK_SIZE);

    if (game->ray.dir_x < 0)
        game->cast.map_x_step = -1;
    else
        game->cast.map_x_step = 1;

    if (game->ray.dir_y < 0)
        game->cast.map_y_step = -1;
    else
        game->cast.map_y_step = 1;

    game->cast.step_x = fabs(1.0f / game->ray.dir_x);
    game->cast.step_y = fabs(1.0f / game->ray.dir_y);

    float player_grid_x = game->player.x / BLOCK_SIZE;
    float player_grid_y = game->player.y / BLOCK_SIZE;

    if (game->ray.dir_x < 0)
    {
        float distance_to_left_edge = player_grid_x - game->cast.map_x;
        game->cast.side_dist_x = distance_to_left_edge * game->cast.step_x;
    }
    else
    {
        float distance_to_right_edge = (game->cast.map_x + 1.0f) - player_grid_x;
        game->cast.side_dist_x = distance_to_right_edge * game->cast.step_x;
    } 
    if (game->ray.dir_y < 0)
    {
        float distance_to_top_edge = player_grid_y - game->cast.map_y;
        game->cast.side_dist_y = distance_to_top_edge * game->cast.step_y;
    }
    else
    {
        float distance_to_bottom_edge = (game->cast.map_y + 1.0f) - player_grid_y;
        game->cast.side_dist_y = distance_to_bottom_edge * game->cast.step_y;
    }
}

int run_dda(t_game *game)
{
    while (1)
    {
        if (game->cast.side_dist_x < game->cast.side_dist_y)
        {
            game->cast.side_dist_x += game->cast.step_x;
            game->cast.map_x += game->cast.map_x_step;
            game->side = 0;
        }
        else
        {
            game->cast.side_dist_y += game->cast.step_y;
            game->cast.map_y += game->cast.map_y_step;
            game->side = 1;
        }

        if (game->cast.map_x < 0 || game->cast.map_x >= game->max_x ||
            game->cast.map_y < 0 || game->cast.map_y >= game->max_y)
            return 0;

        if (game->map[game->cast.map_y][game->cast.map_x] == '1')
            return 1;
    }
}

float distance(t_game *game)
{
    float wall_dist;
    
    if (game->side == 0)
        wall_dist = (game->cast.side_dist_x - game->cast.step_x);
    else
        wall_dist = (game->cast.side_dist_y - game->cast.step_y);
    
    wall_dist *= BLOCK_SIZE;
    
    game->ray.x = game->player.x + game->ray.dir_x * wall_dist;
    game->ray.y = game->player.y + game->ray.dir_y * wall_dist;

    wall_dist *= game->player.dir_x * game->ray.dir_x + game->player.dir_y * game->ray.dir_y;
    
    return (wall_dist);
}

float	cast_ray(t_game *game)
{
	init_dda(game);
	if (!run_dda(game))
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
