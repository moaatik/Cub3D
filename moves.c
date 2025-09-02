/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaatik <moaatik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 18:18:37 by moaatik           #+#    #+#             */
/*   Updated: 2025/09/02 00:58:33 by moaatik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	move_forward(t_game *game)
{
	float new_x;
	float new_y;
	int new_map_x;
	int new_map_y;

	new_x = game->player.x + game->player.dir_x * SPEED;
	new_y = game->player.y + game->player.dir_y * SPEED;
	new_map_x = (int)(new_x) / BLOCK_SIZE;
	new_map_y = (int)(new_y) / BLOCK_SIZE;
	if (new_map_x < 0 || new_map_y < 0 || new_map_x >= game->max_x || new_map_y >= game->max_y)
		return ;
	if(game->map[new_map_y][new_map_x] != '1')
	    return (game->player.x = new_x, game->player.y = new_y, (void)new_x);
	if(game->map[(int)(game->player.y) / BLOCK_SIZE][new_map_x] != '1')
	    game->player.x = new_x;
	else if (game->map[new_map_y][(int)(game->player.x) / BLOCK_SIZE] != '1')
	    game->player.y = new_y;
}

void	move_backward(t_game *game)
{
	float new_x;
	float new_y;
	int new_map_x;
	int new_map_y;

	new_x = game->player.x - game->player.dir_x * SPEED;
	new_y = game->player.y - game->player.dir_y * SPEED;
	new_map_x = (int)(new_x) / BLOCK_SIZE;
	new_map_y = (int)(new_y) / BLOCK_SIZE;
	if (new_map_x < 0 || new_map_y < 0 || new_map_x >= game->max_x || new_map_y >= game->max_y)
		return ;
	if(game->map[new_map_y][new_map_x] != '1')
	    return (game->player.x = new_x, game->player.y = new_y, (void)new_x);
	if(game->map[(int)(game->player.y) / BLOCK_SIZE][new_map_x] != '1')
	    game->player.x = new_x;
	else if (game->map[new_map_y][(int)(game->player.x) / BLOCK_SIZE] != '1')
	    game->player.y = new_y;
}

void move_right(t_game *game)
{
    float new_x;
    float new_y;

    int map_y;
    int map_x;

	new_x = game->player.x + game->player.dir_y * SPEED;
    new_y = game->player.y - game->player.dir_x * SPEED;

    map_x = (int)(new_x) / BLOCK_SIZE;
    map_y = (int)(new_y) / BLOCK_SIZE;

	if (map_x < 0 || map_y < 0 || map_x >= game->max_x || map_y >= game->max_y)
		return ;
	
    if (game->map[map_y][map_x] != '1')
    {
        game->player.x = new_x;
        game->player.y = new_y;
    }
}

void move_left(t_game *game)
{
    float new_x;
    float new_y;

    int map_x;
    int map_y;

	new_x = game->player.x - game->player.dir_y * SPEED;
    new_y = game->player.y + game->player.dir_x * SPEED;

    map_x = (int)(new_x) / BLOCK_SIZE;
    map_y = (int)(new_y) / BLOCK_SIZE;

	if (map_x < 0 || map_y < 0 || map_x >= game->max_x || map_y >= game->max_y)
		return ;

    if (game->map[map_y][map_x] != '1')
    {
        game->player.x = new_x;
        game->player.y = new_y;
    }
}

void	rotate(t_game *game, int dir)
{
	float	rot_speed;

	rot_speed = ROT_SPEED;
	if (!dir)
		rot_speed = -rot_speed;
	game->player.dir_x -= game->player.dir_y * rot_speed;
	game->player.dir_y += game->player.dir_x * rot_speed;
	if (game->player.dir_x > 1)
		game->player.dir_x = 1;
	if (game->player.dir_x < -1)
		game->player.dir_x = -1;
	if (game->player.dir_y > 1)
		game->player.dir_y = 1;
	if (game->player.dir_y < -1)
		game->player.dir_y = -1;
}
