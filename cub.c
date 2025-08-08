#include "cub.h"

void *create_colored_tile(t_game *game, int r, int g, int b, int size)
{
	void    *img;
	char    *data;
	int     bpp;
	int     size_line;
	int     endian;

	img = mlx_new_image(game->mlx, size, size);
	data = mlx_get_data_addr(img, &bpp, &size_line, &endian);
	for (int y = 0; y < size; y++)
	{
		for (int x = 0; x < size; x++)
		{
			int i = y * size_line + x * (bpp / 8);
			data[i + 0] = b;
			data[i + 1] = g;
			data[i + 2] = r;
		}
	}
	return img;
}

void draw_ray(t_game *game)
{
	float ray_x = game->player_x;
	float ray_y = game->player_y;

	float step = 1.0;
	int max_steps = 900000;
	for (int i = 0; i < max_steps; i++)
	{
		int map_x = (int)(ray_x / BLOCK_SIZE);
		int map_y = (int)(ray_y / BLOCK_SIZE);
		if (map_y < 0 || map_x < 0 || map_y >= game->max_y || map_x >= game->max_x)
			break;
		if (game->map[map_y][map_x] == '1')
			break;
		mlx_pixel_put(game->mlx, game->window, (int)ray_x, (int)ray_y, 0xFF0000);
		ray_x += game->dir_x * step;
		ray_y += game->dir_y * step;
	}
}


void	render_map(t_game *game)
{
	int	i, j;
	void *floor_img = create_colored_tile(game, 0, 0, 0, BLOCK_SIZE - 1);
	void *wall_img = create_colored_tile(game, 0, 208, 0, BLOCK_SIZE - 1);
	void *player_img = create_colored_tile(game, 255, 0, 0, 8);

	mlx_clear_window(game->mlx, game->window);
	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			char tile = game->map[i][j];
			if (tile == '0')
				mlx_put_image_to_window(game->mlx, game->window, floor_img, j * BLOCK_SIZE, i * BLOCK_SIZE);
			else if (tile == '1')
				mlx_put_image_to_window(game->mlx, game->window, wall_img, j * BLOCK_SIZE, i * BLOCK_SIZE);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(game->mlx, game->window, player_img, (int)game->player_x - 4, (int)game->player_y - 4);
	mlx_destroy_image(game->mlx, floor_img);
	mlx_destroy_image(game->mlx, wall_img);
	mlx_destroy_image(game->mlx, player_img);

	draw_ray(game);
}

int	key_press(int keycode, t_game *game)
{
	if (keycode == 53)
	{
		mlx_destroy_window(game->mlx, game->window);
		free_strs(game->map);
		exit(0);
	}
	else if (keycode == 13 || keycode == 126)
		move_forward(game);
	else if (keycode == 1 || keycode == 125)
		move_backward(game);
	else if (keycode == 0 || keycode == 123)
		rotate_left(game);
	else if (keycode == 2 || keycode == 124)
		rotate_right(game);
	render_map(game);
	return (0);
}

int	handle_cross(t_game *game)
{
	mlx_destroy_window(game->mlx, game->window);
	free_strs(game->map);
	exit(0);
	return (0);
}

//int	mouse_move(int x, int y, t_game *game)
//{
//	static int last_x = -1;
//	(void)y;
//	if (last_x == -1)
//		last_x = x;

//	int delta_x = x - last_x;
//	last_x = x;

//	float angle = delta_x * 0.003f;

//	float old_dir_x = game->dir_x;
//	game->dir_x = game->dir_x * cos(angle) - game->dir_y * sin(angle);
//	game->dir_y = old_dir_x * sin(angle) + game->dir_y * cos(angle);

//	render_map(game);
//	return (0);
//}

int main(int ac, char **av)
{
	t_game	game;

	(void)ac;
	game.mlx = mlx_init();
	if (!game.mlx)
		return (1);
	game.map = input(av);
	if (!game.map)
		return (1);
	get_map_info(&game);
	game.window = mlx_new_window(game.mlx, game.max_x * BLOCK_SIZE, game.max_y * BLOCK_SIZE, "Cub3D");
	if (!game.window)
		return (1);
	render_map(&game);
	mlx_hook(game.window, 2, 0, key_press, &game);
	mlx_hook(game.window, 17, 0, handle_cross, &game);
	//mlx_hook(game.window, 6, 0, mouse_move, &game);
	mlx_loop(game.mlx);
	return (0);
}
