/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_utils_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenmoha <hbenmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 11:27:50 by hbenmoha          #+#    #+#             */
/*   Updated: 2025/11/08 14:17:50 by hbenmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

//* check if the map file exist & open the fd
int	check_map_exists(char *map_file)
{
	int	fd;

	fd = ft_open(map_file, O_RDONLY, CREATE_FD);
	return (fd);
}

//* parse map block
void	parse_map_block(int fd, char *line, t_game *game)
{
	t_list	*map_list;

	map_list = convert_map_from_file_to_linked_list(fd, line);
	game->map.map_matrix = convert_linked_list_to_matrix(map_list, game);
	validate_map(game);
}

//* check if map is valid (check neigboors)
void	validate_map(t_game *game)
{
	check_map_border(game);
	check_one_player(game);
	check_neigboors(game);
	convert_map_to_rectangular(game);
}

//* convert map to rectangular
void	convert_map_to_rectangular(t_game *game)
{
	char	**map;
	char	**rectangular_map;
	int		y;
	int		x;

	map = game->map.map_matrix;
	rectangular_map = ft_safe_malloc(\
		sizeof(char *) * (game->map.height + 1), ALLOCATE, 1, NULL);
	y = -1;
	while (++y < game->map.height)
	{
		rectangular_map[y] = ft_safe_malloc(\
			sizeof(char) * (game->map.width + 1), ALLOCATE, 1, NULL);
		x = -1;
		while (++x < game->map.width)
		{
			if (x < ft_strlen(map[y]) && (map[y][x] == '1' || map[y][x] == '0'))
				rectangular_map[y][x] = map[y][x];
			else
				rectangular_map[y][x] = '1';
		}
	}
	free_matrix(game->map.map_matrix);
	game->map.map_matrix = rectangular_map;
}

//* check the first + last line => they must be '1' or space
void	check_map_border(t_game *game)
{
	char	**map;
	int		y;
	int		x;

	y = 0;
	x = 0;
	map = game->map.map_matrix;
	while (map[y][x])
	{
		if (map[y][x] != '1' && map[y][x] != 32)
			error_exit("Errro\nmap border are not correct\n");
		x++;
	}
	while (map[y + 1])
		y++;
	x = 0;
	while (map[y][x])
	{
		if (map[y][x] != '1' && map[y][x] != 32)
			error_exit("Errro\nmap border are not correct\n");
		x++;
	}
}
