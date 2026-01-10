/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_utils_1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenmoha <hbenmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 11:20:06 by hbenmoha          #+#    #+#             */
/*   Updated: 2025/11/17 13:36:55 by hbenmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

//* handle map lines ( instructions + map ... )
void	process_map_file(char *line, int fd, t_game *game)
{
	char	*cursor;

	while (line)
	{
		cursor = skip_white_spaces(line);
		if (!*cursor)
		{
			ft_safe_malloc(0, FREE_ONE, 1, line);
			line = get_next_line(fd);
			continue ;
		}
		else if (is_instruction(cursor))
			parse_instructions(game, cursor);
		else if (it_is_map(cursor))
		{
			check_all_instructions_are_before_map(game);
			parse_map_block(fd, line, game);
			ft_safe_malloc(0, FREE_ONE, 1, line);
			break ;
		}
		else
			error_exit("Error\nInstructions not correct\n");
		ft_safe_malloc(0, FREE_ONE, 1, line);
		line = get_next_line(fd);
	}
}

//* the main fun of parsing:
void	parse_map(int ac, char *av[], t_game *game)
{
	char	*line;
	int		fd;

	if (ac != 2)
		error_exit("Error\nNo config file found\n");
	check_map_extension(av[1]);
	fd = check_map_exists(av[1]);
	init_game_struct(game);
	line = get_next_line(fd);
	process_map_file(line, fd, game);
	check_all_instructions_and_map_are_set(game);
	close(fd);
}

//* Checks if the map file has a `.cub` extension.
void	check_map_extension(char *map_name)
{
	size_t	len;

	len = ft_strlen(map_name);
	if (len < 4 || ft_strcmp(map_name + len - 4, ".cub") != 0)
		error_exit("Error\nMap file must have a .cub extension\n");
}

//* check if *str == 0 or 1 (which means it's a map)
bool	it_is_map(char *str)
{
	return (*str == '0' || *str == '1');
}

//* increment player counter + repalce it with '0' + set position and direction
void	set_player_position(t_game *game, int *player_counter, int y, int x)
{
	(*player_counter)++;
	game->player.y = y * BLOCK_SIZE + BLOCK_SIZE / 2;
	game->player.x = x * BLOCK_SIZE + BLOCK_SIZE / 2;
	set_direction_vector(game, game->map.map_matrix[y][x]);
	game->map.map_matrix[y][x] = '0';
}
