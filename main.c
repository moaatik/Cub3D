/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaatik <moaatik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 15:35:02 by moaatik           #+#    #+#             */
/*   Updated: 2025/09/02 14:29:05 by moaatik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	ft_exit(t_game *game)
{
	mlx_destroy_window(game->mlx, game->window);
	mlx_destroy_image(game->mlx, game->img);
	mlx_destroy_image(game->mlx, game->n_wall.img);
	mlx_destroy_image(game->mlx, game->s_wall.img);
	mlx_destroy_image(game->mlx, game->e_wall.img);
	mlx_destroy_image(game->mlx, game->w_wall.img);
	free_strs(game->map);
	exit(0);
	return (0);
}

int	key_press(int keycode, t_game *game)
{
	if (keycode == 53)
		ft_exit(game);
	else if (keycode == 13)
		move_forward(game);
	else if (keycode == 1)
		move_backward(game);
	else if (keycode == 123)
		rotate(game, 0);
	else if (keycode == 124)
		rotate(game, 1);
	else if (keycode == 0)
		move_right(game);
	else if (keycode == 2)
		move_left(game);
	else
		return (0);
	render_game(game);
	return (0);
}

void load_texture(t_game *game, t_texture *texture, char *path)
{
    texture->img = mlx_xpm_file_to_image(game->mlx, path, &texture->width, &texture->height);
    texture->addr = mlx_get_data_addr(texture->img, &texture->bpp, &texture->size_line, &texture->endian);
}

int	init(t_game *game)
{
	load_texture(game, &game->n_wall, "textures/red_brick.xpm");
	load_texture(game, &game->s_wall, "textures/mossy.xpm");
	load_texture(game, &game->e_wall, "textures/eagle.xpm");
	load_texture(game, &game->w_wall, "textures/grey_stone.xpm");
	game->ceiling_color = 0x00FFFF;
	game->floor_color = 0xFFFFFF;
	return (0);
}

int main(int ac, char **av)
{
	t_game	game;

	(void)ac;

	game.map = input(av);
	if (!game.map)
		return (1);

	game.mlx = mlx_init();
	if (!game.mlx)
		return (1);

	if (init(&game))
		return (1);

	get_map_info(&game);

	game.window = mlx_new_window(game.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D");
	if (!game.window)
		return (1);
	
	game.img = mlx_new_image(game.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!game.img)
		return (1);

	game.img_data = mlx_get_data_addr(game.img, &game.bpp, &game.size_line, &game.endian);
	if (!game.img_data)
		return (1);

	render_game(&game);

	mlx_hook(game.window, 2, 0, key_press, &game);
	mlx_hook(game.window, 17, 0, ft_exit, &game);
	mlx_loop(game.mlx);
	return (0);
}
