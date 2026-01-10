/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenmoha <hbenmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 11:04:16 by hbenmoha          #+#    #+#             */
/*   Updated: 2025/11/08 11:11:05 by hbenmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

//* parse north texture
void	parse_north_texture(char *cursor, t_game *game)
{
	if (game->n_wall.path != NULL)
		error_exit("Error\nDouble instructions\n");
	cursor += 2;
	if (is_not_space(cursor))
		error_exit("Error\nInvalid texture identifier format\n");
	game->n_wall.path = trim_spaces(cursor);
	check_path_exist(game->n_wall.path);
	game->n_wall.img = mlx_xpm_file_to_image(game->mlx, game->n_wall.path, \
		&game->n_wall.width, &game->n_wall.height);
	if (!game->n_wall.img)
		error_exit("mlx_xpm_file_to_image failed\n");
	game->n_wall.address = mlx_get_data_addr(game->n_wall.img, \
		&game->n_wall.bpp, &game->n_wall.size_line, &game->n_wall.endian);
	if (!game->n_wall.address)
		error_exit("mlx_get_data_addr failed\n");
}

//* parse south texture
void	parse_south_texture(char *cursor, t_game *game)
{
	if (game->s_wall.path != NULL)
		error_exit("Error\nDouble instructions\n");
	cursor += 2;
	if (is_not_space(cursor))
		error_exit("Error\nInvalid texture identifier format\n");
	game->s_wall.path = trim_spaces(cursor);
	check_path_exist(game->s_wall.path);
	game->s_wall.img = mlx_xpm_file_to_image(game->mlx, game->s_wall.path, \
		&game->s_wall.width, &game->s_wall.height);
	if (!game->s_wall.img)
		error_exit("mlx_xpm_file_to_image failed\n");
	game->s_wall.address = mlx_get_data_addr(game->s_wall.img, \
		&game->s_wall.bpp, &game->s_wall.size_line, &game->s_wall.endian);
	if (!game->s_wall.address)
		error_exit("mlx_get_data_addr failed\n");
}

//* parse west texture
void	parse_west_texture(char *cursor, t_game *game)
{
	if (game->w_wall.path != NULL)
		error_exit("Error\nDouble instructions\n");
	cursor += 2;
	if (is_not_space(cursor))
		error_exit("Error\nInvalid texture identifier format\n");
	game->w_wall.path = trim_spaces(cursor);
	check_path_exist(game->w_wall.path);
	game->w_wall.img = mlx_xpm_file_to_image(game->mlx, \
		game->w_wall.path, &game->w_wall.width, &game->w_wall.height);
	if (!game->w_wall.img)
		error_exit("mlx_xpm_file_to_image failed\n");
	game->w_wall.address = mlx_get_data_addr(game->w_wall.img, \
		&game->w_wall.bpp, &game->w_wall.size_line, &game->w_wall.endian);
	if (!game->w_wall.address)
		error_exit("mlx_get_data_addr failed\n");
}

//* parse east texture
void	parse_east_texture(char *cursor, t_game *game)
{
	if (game->e_wall.path != NULL)
		error_exit("Error\nDouble instructions\n");
	cursor += 2;
	if (is_not_space(cursor))
		error_exit("Error\nInvalid texture identifier format\n");
	game->e_wall.path = trim_spaces(cursor);
	check_path_exist(game->e_wall.path);
	game->e_wall.img = mlx_xpm_file_to_image(game->mlx, \
		game->e_wall.path, &game->e_wall.width, &game->e_wall.height);
	if (!game->e_wall.img)
		error_exit("mlx_xpm_file_to_image failed\n");
	game->e_wall.address = mlx_get_data_addr(game->e_wall.img, \
		&game->e_wall.bpp, &game->e_wall.size_line, &game->e_wall.endian);
	if (!game->e_wall.address)
		error_exit("mlx_get_data_addr failed\n");
}

//* parse instructions depends on its identifier
void	parse_instructions(t_game *game, char *cursor)
{
	if (!ft_strncmp(cursor, "NO", 2))
		parse_north_texture(cursor, game);
	else if (!ft_strncmp(cursor, "SO", 2))
		parse_south_texture(cursor, game);
	else if (!ft_strncmp(cursor, "WE", 2))
		parse_west_texture(cursor, game);
	else if (!ft_strncmp(cursor, "EA", 2))
		parse_east_texture(cursor, game);
	else if (!ft_strncmp(cursor, "F", 1))
		parse_floor_color(cursor, game);
	else if (!ft_strncmp(cursor, "C", 1))
		parse_ceiling_color(cursor, game);
}
