/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_instructions_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenmoha <hbenmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 11:14:38 by hbenmoha          #+#    #+#             */
/*   Updated: 2025/11/08 11:15:54 by hbenmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

//* parse floor color
void	parse_floor_color(char *cursor, t_game *game)
{
	if (game->floor_color != -1)
		error_exit("Error\nDouble instructions\n");
	cursor++;
	if (is_not_space(cursor))
		error_exit("Error\nRGB is not correct!\n");
	game->floor_color = get_color_from_map(cursor);
}

//* parse ceiling color
void	parse_ceiling_color(char *cursor, t_game *game)
{
	if (game->ceiling_color != -1)
		error_exit("Error\nDouble instructions\n");
	cursor++;
	if (is_not_space(cursor))
		error_exit("Error\nRGB is not correct!\n");
	game->ceiling_color = get_color_from_map(cursor);
}

//* check that all instructions are set before the map
void	check_all_instructions_are_before_map(t_game *game)
{
	if (!game->n_wall.path
		|| !game->s_wall.path
		|| !game->w_wall.path
		|| !game->e_wall.path
		|| game->floor_color == -1
		|| game->ceiling_color == -1)
		error_exit("Error\nInstructions not found\n");
}

//* check that all instructions are set
void	check_all_instructions_and_map_are_set(t_game *game)
{
	if (!game->n_wall.path
		|| !game->s_wall.path
		|| !game->w_wall.path
		|| !game->e_wall.path
		|| game->floor_color == -1
		|| game->ceiling_color == -1
		|| !game->map.map_matrix)
		error_exit("Error\nInstructions or map are not found\n");
}

//* returns true if starts with NO, SO, WE, EA, F, or C.
bool	is_instruction(char *str)
{
	return (
		!ft_strncmp(str, "NO", 2)
		|| !ft_strncmp(str, "SO", 2)
		|| !ft_strncmp(str, "WE", 2)
		|| !ft_strncmp(str, "EA", 2)
		|| !ft_strncmp(str, "F", 1)
		|| !ft_strncmp(str, "C", 1)
	);
}
