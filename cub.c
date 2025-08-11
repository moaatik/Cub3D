#include "cub.h"

void *create_colored_tile(t_game *game, int r, int g, int b, int size)
{
	void    *img;
	char    *data;
	int     bpp;
	int     size_line;
	int     endian;
	int		y;
	int		x;

	img = mlx_new_image(game->mlx, size, size);
	data = mlx_get_data_addr(img, &bpp, &size_line, &endian);
	y = 0;
	while (y < size)
	{
		x = 0;
		while (x < size)
		{
			int i = y * size_line + x * (bpp / 8);
			data[i + 0] = b;
			data[i + 1] = g;
			data[i + 2] = r;
			x++;
		}
		y++;
	}
	return (img);
}

void draw_ray(t_game *game, float scale)
{
	float ray_x = game->player_x;
	float ray_y = game->player_y;


	int	i = 0;
	while (i < 50)
	{
		int map_x = (int)(ray_x / BLOCK_SIZE);
		int map_y = (int)(ray_y / BLOCK_SIZE);
		if (map_y < 0 || map_x < 0 || map_y >= game->max_y || map_x >= game->max_x)
			break;
		if (game->map[map_y][map_x] == '1')
			break;
		mlx_pixel_put(game->mlx, game->window, (int)(ray_x * scale), (int)(ray_y * scale), 0xFF0000);
		ray_x += game->dir_x;
		ray_y += game->dir_y;
		i++;
	}
}

void	render_map(t_game *game)
{
	int		i;
	int		j;
	void	*floor_img;
	void	*wall_img;
	void	*player_img;
	float	scale;

	scale = 8.0 / BLOCK_SIZE;

	floor_img = create_colored_tile(game, 0, 0, 0, 8);
	wall_img = create_colored_tile(game, 0, 208, 0, 8);
	player_img = create_colored_tile(game, 255, 0, 0, 3);
	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			char tile = game->map[i][j];
			if (tile == '0')
				mlx_put_image_to_window(game->mlx, game->window, floor_img, j * 8, i * 8);
			if (tile == '1')
				mlx_put_image_to_window(game->mlx, game->window, wall_img, j * 8, i * 8);
			j++;
		}
		i++;
	}

	int player_minimap_x = (int)(game->player_x * scale) - 1;
	int player_minimap_y = (int)(game->player_y * scale);

	mlx_put_image_to_window(game->mlx, game->window, player_img, player_minimap_x, player_minimap_y);
	mlx_destroy_image(game->mlx, floor_img);
	mlx_destroy_image(game->mlx, wall_img);
	mlx_destroy_image(game->mlx, player_img);
	draw_ray(game, scale);
}

void clear_img_data(t_game *game, int color)
{
    int total_pixels;
    int bytes_per_pixel;
	int	i;

	total_pixels = SCREEN_WIDTH * SCREEN_HEIGHT;
    bytes_per_pixel = game->bpp / 8;
	i = 0;
    while (i < total_pixels * bytes_per_pixel)
    {
        game->img_data[i + 0] = color & 0xFF;
        game->img_data[i + 1] = (color >> 8) & 0xFF;
        game->img_data[i + 2] = (color >> 16) & 0xFF;
		i += bytes_per_pixel;
    }
}

void my_mlx_pixel_put(t_game *game, int x, int y, int color)
{
    if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
        return;
    char *dst = game->img_data + (y * game->size_line + x * (game->bpp / 8));
    dst[0] = color & 0xFF;
    dst[1] = (color >> 8) & 0xFF;
    dst[2] = (color >> 16) & 0xFF;
}

void draw_vertical_line(t_game *game, int x, int start_y, int end_y, int color)
{
    for (int y = start_y; y <= end_y; y++)
        my_mlx_pixel_put(game, x, y, color);
}

void render_3d(t_game *game)
{
    int num_rays = SCREEN_WIDTH;
	int	r;

    float fov = 60.0 / 180 * M_PI;
    float start_angle = atan2(game->dir_y, game->dir_x) - fov / 2;
    float angle_step = fov / num_rays;

	clear_img_data(game, 0x000000);
	r = 0;
    while (r < num_rays)
    {
        float ray_angle = start_angle + r * angle_step;

        float ray_dir_x = cos(ray_angle);
        float ray_dir_y = sin(ray_angle);

        float ray_x = game->player_x;
        float ray_y = game->player_y;

        float dist = 0;
        int hit = 0;

		int	i = 0;
        while (1)
        {
            int map_x = (int)(ray_x / BLOCK_SIZE);
            int map_y = (int)(ray_y / BLOCK_SIZE);

            if (map_x < 0 || map_y < 0 || map_x >= game->max_x || map_y >= game->max_y)
                break;

            if (game->map[map_y][map_x] == '1')
            {
                hit = 1;
                break;
            }
            ray_x += ray_dir_x;
            ray_y += ray_dir_y;
        }

        if (hit)
        {
            dist = sqrt((ray_x - game->player_x) * (ray_x - game->player_x) +
                        (ray_y - game->player_y) * (ray_y - game->player_y));

            int wall_height = (int)(BLOCK_SIZE * SCREEN_HEIGHT / dist);

            int wall_start = (SCREEN_HEIGHT - wall_height) / 2;
            int wall_end = wall_start + wall_height;
            draw_vertical_line(game, r, wall_start, wall_end, 0x00FF00);
			i++;
        }
		r++;
    }
	mlx_put_image_to_window(game->mlx, game->window, game->img, 0, 0);
	render_map(game);
}

int	key_press(int keycode, t_game *game)
{
	if (keycode == 53)
	{
		mlx_destroy_window(game->mlx, game->window);
		free_strs(game->map);
		exit(0);
	}
	else if (keycode == 13)
		move_forward(game);
	else if (keycode == 1)
		move_backward(game);
	else if (keycode == 123)
		rotate_left(game);
	else if (keycode == 124)
		rotate_right(game);
	else if (keycode == 0 )
		move_right(game);
	else if (keycode == 2)
		move_left(game);
	render_3d(game);
	return (0);
}

int	handle_cross(t_game *game)
{
	mlx_destroy_window(game->mlx, game->window);
	free_strs(game->map);
	exit(0);
	return (0);
}

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

	game.window = mlx_new_window(game.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D");
	if (!game.window)
		return (1);
	
	game.img = mlx_new_image(game.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	game.img_data = mlx_get_data_addr(game.img, &game.bpp, &game.size_line, &game.endian);

	render_3d(&game);

	mlx_hook(game.window, 2, 0, key_press, &game);
	mlx_hook(game.window, 17, 0, handle_cross, &game);
	mlx_loop(game.mlx);
	return (0);
}
