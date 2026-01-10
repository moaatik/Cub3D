/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_utils_3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenmoha <hbenmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 11:32:14 by hbenmoha          #+#    #+#             */
/*   Updated: 2025/11/18 14:28:33 by hbenmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

//* check if a char is player(N,S,W,E)
bool	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'W' || c == 'E');
}

//* set the player’s facing direction
void	set_direction_vector(t_game *game, char player_position)
{
	if (player_position == 'N')
	{
		game->player.dir_x = 0;
		game->player.dir_y = -1;
	}
	else if (player_position == 'S')
	{
		game->player.dir_x = 0;
		game->player.dir_y = 1;
	}
	else if (player_position == 'W')
	{
		game->player.dir_x = -1;
		game->player.dir_y = 0;
	}
	else if (player_position == 'E')
	{
		game->player.dir_x = 1;
		game->player.dir_y = 0;
	}
}

//* check if there is just 1 player
void	check_one_player(t_game *game)
{
	char	**map;
	int		y;
	int		x;
	int		player_counter;

	player_counter = 0;
	y = 0;
	map = game->map.map_matrix;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (is_player(map[y][x]))
				set_player_position(game, &player_counter, y, x);
			x++;
		}
		y++;
	}
	if (player_counter != 1)
		error_exit("Error\nMap must contain exactly one player\n");
}

//* check all 4 neighbors
void	check_all_4_neighbors(int y, int x, t_game *game)
{
	char	**map;

	map = game->map.map_matrix;
	if (y == 0 || !map[y + 1] || x == 0 || x >= ft_strlen(map[y]) - 1)
		error_exit("Error\nMap is not closed\n");
	if (x >= ft_strlen(map[y - 1]) \
		|| (map[y - 1][x] != '1' && map[y - 1][x] != '0'))
		check_current_neighboor(map[y - 1][x]);
	if (x >= ft_strlen(map[y + 1]) \
		|| (map[y + 1][x] != '1' && map[y + 1][x] != '0'))
		check_current_neighboor(map[y + 1][x]);
	if (x - 1 < 0 || (map[y][x - 1] != '1' && map[y][x - 1] != '0'))
		check_current_neighboor(map[y][x - 1]);
	if (x + 1 >= ft_strlen(map[y]) \
		|| (map[y][x + 1] != '1' && map[y][x + 1] != '0'))
		check_current_neighboor(map[y][x + 1]);
}

//* check neighboors
void	check_neigboors(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (game->map.map_matrix[y])
	{
		x = 0;
		while (game->map.map_matrix[y][x])
		{
			if (game->map.map_matrix[y][x] == '0')
				check_all_4_neighbors(y, x, game);
			x++;
		}
		y++;
	}
}
