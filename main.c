/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaatik <moaatik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 15:35:02 by moaatik           #+#    #+#             */
/*   Updated: 2025/09/25 15:32:22 by moaatik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*ptr;

	i = 0;
	ptr = (char *)s;
	while (i < n)
	{
		ptr[i] = 0;
		i++;
	}
}

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

void load_texture(t_game *game, t_texture *texture, char *path)
{
    texture->img = mlx_xpm_file_to_image(game->mlx, path, &texture->width, &texture->height);
    texture->address = mlx_get_data_addr(texture->img, &texture->bpp, &texture->size_line, &texture->endian);
}

int	init(t_game *game)
{
	load_texture(game, &game->n_wall, "textures/SP_DUDE1.xpm");
	load_texture(game, &game->s_wall, "textures/MARBFAC3.xpm");
	load_texture(game, &game->e_wall, "textures/SKULWAL3.xpm");
	load_texture(game, &game->w_wall, "textures/STONGARG.xpm");
	game->ceiling_color = 0x780010;
	game->floor_color = 0x002000;
	game->sprint = 1;
	return (0);
}

int main(int ac, char **av)
{
	t_game	game;

	(void)ac;

	ft_bzero(&game, sizeof(t_game));

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

	game.address = mlx_get_data_addr(game.img, &game.bpp, &game.size_line, &game.endian);
	if (!game.address)
		return (1);

	render_game(&game);

	mlx_hook(game.window, 2, 0, key_press, &game);
	mlx_hook(game.window, 3, 0, key_release, &game);
	mlx_loop_hook(game.mlx, update, &game);
	mlx_hook(game.window, 17, 0, ft_exit, &game);
	mlx_loop(game.mlx);
	return (0);
}
