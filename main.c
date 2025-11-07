/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaatik <moaatik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 15:35:02 by moaatik           #+#    #+#             */
/*   Updated: 2025/11/07 15:49:05 by moaatik          ###   ########.fr       */
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
	exit(0);
	return (0);
}

int	key_press(int keycode, t_game *game)
{
	if (keycode == 53)
		game->keys.escape = 1;
	else if (keycode == 13)
		game->keys.w = 1;
	else if (keycode == 1)
		game->keys.s = 1;
	else if (keycode == 123)
		game->keys.left = 1;
	else if (keycode == 124)
		game->keys.right = 1;
	else if (keycode == 0)
		game->keys.d = 1;
	else if (keycode == 2)
		game->keys.a = 1;
	else if (keycode == 257)
		game->sprint = 2;
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == 53)
		game->keys.escape = 0;
	else if (keycode == 13)
		game->keys.w = 0;
	else if (keycode == 1)
		game->keys.s = 0;
	else if (keycode == 123)
		game->keys.left = 0;
	else if (keycode == 124)
		game->keys.right = 0;
	else if (keycode == 0)
		game->keys.d = 0;
	else if (keycode == 2)
		game->keys.a = 0;
	else if (keycode == 257)
		game->sprint = 1;
	return (0);
}

int update(t_game *game)
{
    if (game->keys.escape)
        ft_exit(game);
    if (game->keys.w)
        move_forward(game);
    if (game->keys.s)
        move_backward(game);
    if (game->keys.left && !game->keys.right)
        rotate(game, 0);
    if (game->keys.right && !game->keys.left)
        rotate(game, 1);
    if (game->keys.d)
        move_right(game);
    if (game->keys.a)
        move_left(game);
    render_game(game);
    return (0);
}

int main(int ac, char **av)
{
	t_game	game;

	parse_map(ac, av, &game);
	game.player.rot_speed = 1;
	render_game(&game);

	mlx_hook(game.window, 2, 0, key_press, &game);
	mlx_hook(game.window, 3, 0, key_release, &game);
	mlx_loop_hook(game.mlx, update, &game);
	mlx_hook(game.window, 17, 0, ft_exit, &game);
	mlx_loop(game.mlx);
	return (0);
}
