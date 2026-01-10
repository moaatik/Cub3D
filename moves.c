/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaatik <moaatik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 18:18:37 by moaatik           #+#    #+#             */
/*   Updated: 2025/12/31 14:21:00 by moaatik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	move_forward(t_game *game)
{
	float	new_x;
	float	new_y;
	int		map_x;
	int		map_y;

	new_x = game->player.x + game->player.dir_x * SPEED * game->sprint;
	new_y = game->player.y + game->player.dir_y * SPEED * game->sprint;
	map_x = (int)(new_x) / BLOCK_SIZE;
	map_y = (int)(game->player.y) / BLOCK_SIZE;
	if (map_x < 0 || map_y < 0 || map_x >= game->map.width
		|| map_y >= game->map.height)
		return ;
	if (game->map.map_matrix[map_y][map_x] != '1')
		game->player.x = new_x;
	map_x = (int)(game->player.x) / BLOCK_SIZE;
	map_y = (int)(new_y) / BLOCK_SIZE;
	if (game->map.map_matrix[map_y][map_x] != '1')
		game->player.y = new_y;
}

void	move_backward(t_game *game)
{
	float	new_x;
	float	new_y;
	int		map_x;
	int		map_y;

	new_x = game->player.x - game->player.dir_x * SPEED * game->sprint;
	new_y = game->player.y - game->player.dir_y * SPEED * game->sprint;
	map_x = (int)(new_x) / BLOCK_SIZE;
	map_y = (int)(game->player.y) / BLOCK_SIZE;
	if (map_x < 0 || map_y < 0 || map_x >= game->map.width
		|| map_y >= game->map.height)
		return ;
	if (game->map.map_matrix[map_y][map_x] != '1')
		game->player.x = new_x;
	map_x = (int)(game->player.x) / BLOCK_SIZE;
	map_y = (int)(new_y) / BLOCK_SIZE;
	if (game->map.map_matrix[map_y][map_x] != '1')
		game->player.y = new_y;
}

void	move_right(t_game *game)
{
	float	new_x;
	float	new_y;
	int		map_y;
	int		map_x;

	new_x = game->player.x + game->player.dir_y * SPEED * game->sprint;
	new_y = game->player.y - game->player.dir_x * SPEED * game->sprint;
	map_x = (int)(new_x) / BLOCK_SIZE;
	map_y = (int)(game->player.y) / BLOCK_SIZE;
	if (map_x < 0 || map_y < 0 || map_x >= game->map.width
		|| map_y >= game->map.height)
		return ;
	if (game->map.map_matrix[map_y][map_x] != '1')
		game->player.x = new_x;
	map_x = (int)(game->player.x) / BLOCK_SIZE;
	map_y = (int)(new_y) / BLOCK_SIZE;
	if (game->map.map_matrix[map_y][map_x] != '1')
		game->player.y = new_y;
}

void	move_left(t_game *game)
{
	float	new_x;
	float	new_y;
	int		map_x;
	int		map_y;

	new_x = game->player.x - game->player.dir_y * SPEED * game->sprint;
	new_y = game->player.y + game->player.dir_x * SPEED * game->sprint;
	map_x = (int)(new_x) / BLOCK_SIZE;
	map_y = (int)(game->player.y) / BLOCK_SIZE;
	if (map_x < 0 || map_y < 0 || map_x >= game->map.width
		|| map_y >= game->map.height)
		return ;
	if (game->map.map_matrix[map_y][map_x] != '1')
		game->player.x = new_x;
	map_x = (int)(game->player.x) / BLOCK_SIZE;
	map_y = (int)(new_y) / BLOCK_SIZE;
	if (game->map.map_matrix[map_y][map_x] != '1')
		game->player.y = new_y;
}

void	rotate(t_game *game, int dir)
{
	float	rot_speed;
	float	old_dir_x;

	rot_speed = ROT_SPEED;
	if (!dir)
		rot_speed = -rot_speed;
	old_dir_x = game->player.dir_x;
	game->player.dir_x -= game->player.dir_y * rot_speed * game->sprint;
	game->player.dir_y += old_dir_x * rot_speed * game->sprint;
	if (game->player.dir_x > 1)
		game->player.dir_x = 1;
	if (game->player.dir_x < -1)
		game->player.dir_x = -1;
	if (game->player.dir_y > 1)
		game->player.dir_y = 1;
	if (game->player.dir_y < -1)
		game->player.dir_y = -1;
}
