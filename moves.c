/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaatik <moaatik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 18:18:37 by moaatik           #+#    #+#             */
/*   Updated: 2025/08/12 16:06:01 by moaatik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	move_forward(t_game *game)
{
	float new_x;
	float new_y;

	int map_x;
	int map_y;

	new_x = game->player_x + game->dir_x * SPEED;
	new_y = game->player_y + game->dir_y * SPEED;

	map_x = (int)(new_x) / BLOCK_SIZE;
	map_y = (int)(new_y) / BLOCK_SIZE;

	if (map_x < 0 || map_y < 0 || map_x >= game->max_x || map_y >= game->max_y)
		return ;

	if (game->map[map_y][map_x] != '1')
	{
		game->player_x = new_x;
		game->player_y = new_y;
	}
}

void	move_backward(t_game *game)
{
	float new_x;
	float new_y;

	int map_x;
	int map_y;;


	new_x = game->player_x - game->dir_x * SPEED;
	new_y = game->player_y - game->dir_y * SPEED;

	map_x = (int)(new_x) / BLOCK_SIZE;
	map_y = (int)(new_y) / BLOCK_SIZE;

	if (map_x < 0 || map_y < 0 || map_x >= game->max_x || map_y >= game->max_y)
		return ;
	
	if (game->map[map_y][map_x] != '1')
	{
		game->player_x = new_x;
		game->player_y = new_y;
	}
}

void move_right(t_game *game)
{
    float new_x;
    float new_y;

    int map_y;
    int map_x;

	new_x = game->player_x + game->dir_y * SPEED;
    new_y = game->player_y - game->dir_x * SPEED;

    map_x = (int)(new_x) / BLOCK_SIZE;
    map_y = (int)(new_y) / BLOCK_SIZE;

	if (map_x < 0 || map_y < 0 || map_x >= game->max_x || map_y >= game->max_y)
		return ;
	
    if (game->map[map_y][map_x] != '1')
    {
        game->player_x = new_x;
        game->player_y = new_y;
    }
}

void move_left(t_game *game)
{
    float new_x;
    float new_y;

    int map_x;
    int map_y;

	new_x = game->player_x - game->dir_y * SPEED;
    new_y = game->player_y + game->dir_x * SPEED;

    map_x = (int)(new_x) / BLOCK_SIZE;
    map_y = (int)(new_y) / BLOCK_SIZE;

	if (map_x < 0 || map_y < 0 || map_x >= game->max_x || map_y >= game->max_y)
		return ;

    if (game->map[map_y][map_x] != '1')
    {
        game->player_x = new_x;
        game->player_y = new_y;
    }
}

void	rotate_left(t_game *game)
{
	float	old_dir_x;
	float	angle;
	float	sin_angle;
	float	cos_angle;

	old_dir_x = game->dir_x;
	angle = -ROT_SPEED;

	sin_angle = sin(angle);
	cos_angle = cos(angle);

	game->dir_x = game->dir_x * cos_angle - game->dir_y * sin_angle;
	game->dir_y = old_dir_x * sin_angle + game->dir_y * cos_angle;
}

void	rotate_right(t_game *game)
{
	float	old_dir_x;
	float	angle;
	float	sin_angle;
	float	cos_angle;

	old_dir_x = game->dir_x;
	angle = ROT_SPEED;

	sin_angle = sin(angle);
	cos_angle = cos(angle);

	game->dir_x = game->dir_x * cos_angle - game->dir_y * sin_angle;
	game->dir_y = old_dir_x * sin_angle + game->dir_y * cos_angle;
}
