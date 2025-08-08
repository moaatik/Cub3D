/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaatik <moaatik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 18:18:37 by moaatik           #+#    #+#             */
/*   Updated: 2025/08/08 11:15:59 by moaatik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	move_forward(t_game *game)
{
	float new_x = game->player_x + game->dir_x * SPEED;
	float new_y = game->player_y + game->dir_y * SPEED;

	int map_x = (int)(new_x) / BLOCK_SIZE;
	int map_y = (int)(new_y) / BLOCK_SIZE;

	if (game->map[map_y][map_x] != '1')
	{
		game->player_x = new_x;
		game->player_y = new_y;
	}
}


void	move_backward(t_game *game)
{
	float new_x = game->player_x - game->dir_x * SPEED;
	float new_y = game->player_y - game->dir_y * SPEED;

	int map_x = (int)(new_x) / BLOCK_SIZE;
	int map_y = (int)(new_y) / BLOCK_SIZE;

	if (game->map[map_y][map_x] != '1')
	{
		game->player_x = new_x;
		game->player_y = new_y;
	}
}

void	rotate_left(t_game *game)
{
	float old_dir_x = game->dir_x;
	float angle = -game->rot_speed;

	game->dir_x = game->dir_x * cos(angle) - game->dir_y * sin(angle);
	game->dir_y = old_dir_x * sin(angle) + game->dir_y * cos(angle);
}

void	rotate_right(t_game *game)
{
	float old_dir_x = game->dir_x;
	float angle = game->rot_speed;

	game->dir_x = game->dir_x * cos(angle) - game->dir_y * sin(angle);
	game->dir_y = old_dir_x * sin(angle) + game->dir_y * cos(angle);
}

