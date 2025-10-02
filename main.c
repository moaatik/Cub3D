/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenmoha <hbenmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 15:35:02 by moaatik           #+#    #+#             */
/*   Updated: 2025/09/26 10:54:55 by hbenmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

// int	ft_exit(t_game *game)
// {
// 	mlx_destroy_window(game->mlx, game->window);
// 	mlx_destroy_image(game->mlx, game->img);
// 	mlx_destroy_image(game->mlx, game->n_wall.img);
// 	mlx_destroy_image(game->mlx, game->s_wall.img);
// 	mlx_destroy_image(game->mlx, game->e_wall.img);
// 	mlx_destroy_image(game->mlx, game->w_wall.img);
// 	free_strs(game->map);
// 	exit(0);
// 	return (0);
// }

// int	key_press(int keycode, t_game *game)
// {
// 	if (keycode == 53)
// 		ft_exit(game);
// 	else if (keycode == 13)
// 		move_forward(game);
// 	else if (keycode == 1)
// 		move_backward(game);
// 	else if (keycode == 123)
// 		rotate(game, 0);
// 	else if (keycode == 124)
// 		rotate(game, 1);
// 	else if (keycode == 0)
// 		move_right(game);
// 	else if (keycode == 2)
// 		move_left(game);
// 	else
// 		return (0);
// 	render_game(game);
// 	return (0);
// }

// void load_texture(t_game *game, t_texture *texture, char *path)
// {
//     texture->img = mlx_xpm_file_to_image(game->mlx, path, &texture->width, &texture->height);
//     texture->address = mlx_get_data_addr(texture->img, &texture->bpp, &texture->size_line, &texture->endian);
// }

// int	init(t_game *game)
// {
// 	load_texture(game, &game->n_wall, "textures/SKSPINE1.xpm");
// 	load_texture(game, &game->s_wall, "textures/MARBFAC3.xpm");
// 	load_texture(game, &game->e_wall, "textures/SKULWAL3.xpm");
// 	load_texture(game, &game->w_wall, "textures/STONGARG.xpm");
// 	game->ceiling_color = 0x780010;
// 	game->floor_color = 0x002000;
// 	return (0);
// }

int main(int ac, char **av)
{
	t_game	game;

	//* parsing
	parse_map(ac, av, &game);

	//* basic parsing
	// game.map = input(av);
	// if (!game.map)
	// 	return (1);

	// game.mlx = mlx_init();
	// if (!game.mlx)
	// 	return (1);
	// //* init textures ( instructions )
	// if (init(&game))
	// 	return (1);

	// //* set player position
	// get_map_info(&game);

	// //* create window + image
	// game.window = mlx_new_window(game.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D");
	// if (!game.window)
	// 	return (1);
	// game.img = mlx_new_image(game.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	// if (!game.img)
	// 	return (1);
	// game.address = mlx_get_data_addr(game.img, &game.bpp, &game.size_line, &game.endian);
	// if (!game.address)
	// 	return (1);

	// //* rendering of the game
	// render_game(&game);

	// mlx_hook(game.window, 2, 0, key_press, &game);
	// mlx_hook(game.window, 17, 0, ft_exit, &game);
	// mlx_loop(game.mlx);
	return (0);
}

//todo; understand why we convert from rgb to int
//todo: push your updates !
//todo: copy the video from pc to your phone
//todo: stor the RGB in char not int ( befor you convert it to one int => just for memory opetimization )
