/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaatik <moaatik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 18:18:37 by moaatik           #+#    #+#             */
/*   Updated: 2025/08/30 09:35:45 by moaatik          ###   ########.fr       */
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

void	rotate(t_game *game, int dir)
{
	float	rot_speed;

	rot_speed = ROT_SPEED;
	if (!dir)
		rot_speed = -rot_speed;
	game->dir_x -= game->dir_y * rot_speed;
	game->dir_y += game->dir_x * rot_speed;
	if (game->dir_x > 1)
		game->dir_x = 1;
	if (game->dir_x < -1)
		game->dir_x = -1;
	if (game->dir_y > 1)
		game->dir_y = 1;
	if (game->dir_y < -1)
		game->dir_y = -1;
}
