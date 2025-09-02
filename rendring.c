/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendring.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaatik <moaatik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 16:57:56 by moaatik           #+#    #+#             */
/*   Updated: 2025/09/02 15:18:18 by moaatik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	init_ray(t_game *game, int ray_index, float start_angle, float angle_step, t_ray *ray)
{
	ray->angle = start_angle + ray_index * angle_step;
	ray->dir_x = cos(ray->angle);
	ray->dir_y = sin(ray->angle);
	ray->x = game->player.x;
	ray->y = game->player.y;
}

int	cast_ray(t_game *game, t_ray *ray, int ray_index)
{
	int	map_x;
	int	map_y;

	(void)ray_index;
	while (1)
	{
		map_x = (int)(ray->x / BLOCK_SIZE);
		map_y = (int)(ray->y / BLOCK_SIZE);
		if (map_x < 0 || map_y < 0 || map_x >= game->max_x || map_y >= game->max_y)
			return (0);
		if (game->map[map_y][map_x] == '1')
			return (1);
		ray->x += ray->dir_x;
		ray->y += ray->dir_y;
	}
}

unsigned int get_texture_color(t_texture *texture, int x, int y)
{
	void	*pixel;
	
	if (x < 0 || y < 0 || x >= texture->width || y >= texture->height)
		return (0);
	
	pixel = texture->addr + (y * texture->size_line + x * (texture->bpp / 8));
	return (*(unsigned int*)pixel);
}

void put_pixel_to_image(t_game *game, int x, int y, unsigned int color)
{
	void	*pixel;

	pixel = game->img_data + (y * game->size_line + x * (game->bpp / 8));
	*(unsigned int*)pixel = color;
}

t_texture *get_wall_texture(t_game *game, t_ray *ray)
{
	int		map_x;
	int		map_y;
	float	dx;
	float	dy;
	
	map_x = (int)(ray->x / BLOCK_SIZE);
	map_y = (int)(ray->y / BLOCK_SIZE);
	
	dx = ray->x - (map_x * BLOCK_SIZE + BLOCK_SIZE / 2);
	dy = ray->y - (map_y * BLOCK_SIZE + BLOCK_SIZE / 2);
	
	if (fabs(dx) > fabs(dy))
	{
		if (dx > 0)
			return (&game->e_wall);
		else
			return (&game->w_wall);
	}
	else
	{
		if (dy > 0)
			return (&game->s_wall);
		else
			return (&game->n_wall);
	}
}

float calculate_wall_distance(t_game *game, t_ray *ray)
{
	float dist;

	dist = sqrt((ray->x - game->player.x) * (ray->x - game->player.x)
			+ (ray->y - game->player.y) * (ray->y - game->player.y));


	dist *= game->player.dir_x * ray->dir_x + game->player.dir_y * ray->dir_y;
	return (dist);
}

void	calculate_wall_dimensions(float dist, t_wall *wall)
{
	wall->height = (int)(BLOCK_SIZE * SCREEN_HEIGHT / dist);
	wall->start = (SCREEN_HEIGHT - wall->height) / 2;
	wall->end = wall->start + wall->height;
}

int calculate_texture_x(t_ray *ray, t_texture *texture)
{
	int     map_x;
	int     map_y;
	float   dx;
	float   dy;
	float   wall_hit_point;
	int     tex_x;
	
	map_x = (int)(ray->x / BLOCK_SIZE);
	map_y = (int)(ray->y / BLOCK_SIZE);
	
	dx = ray->x - (map_x * BLOCK_SIZE + BLOCK_SIZE / 2);
	dy = ray->y - (map_y * BLOCK_SIZE + BLOCK_SIZE / 2);
	
	if (fabs(dx) > fabs(dy)) // east || west
		wall_hit_point = fmod(ray->y, BLOCK_SIZE); // bansaba l wall fin drab ray (axman index f dak l wall)
	else // north || south
		wall_hit_point = fmod(ray->x, BLOCK_SIZE);
	
	// Convert wall hit point to texture coordinate
	tex_x = (int)((wall_hit_point / BLOCK_SIZE) * texture->width);

	return (tex_x);
}

int calculate_texture_y(int screen_y, t_wall wall, t_texture *texture)
{
	float   tex_pos;
	int     tex_y;
	
	// position in wall between (0.0 to 1.0) like percentage
	tex_pos = (float)(screen_y - wall.start) / wall.height;

	// Convert to texture Y coordinate like if the high is 20 and we are in half way (0.5 tex_pos) 20 * 0.5 = 10
	tex_y = (int)(tex_pos * texture->height);
	
	return (tex_y);
}

unsigned int get_pixel_color(t_game *game, int screen_y, t_wall wall, t_texture *texture, int tex_x)
{
	int tex_y;

	if (screen_y >= wall.start && screen_y <= wall.end)
	{
		tex_y = calculate_texture_y(screen_y, wall, texture);
		return (get_texture_color(texture, tex_x, tex_y));
	}
	else if (screen_y < wall.start)
		return (game->ceiling_color);
	else
		return (game->floor_color);
}

void draw_wall_slice(t_game *game, t_ray *ray, int ray_index)
{
	float           dist;
	t_wall 			wall;
	t_texture       *texture;
	int             tex_x;
	int             y;
	unsigned int    color;

	dist = calculate_wall_distance(game, ray);

	calculate_wall_dimensions(dist, &wall);

	texture = get_wall_texture(game, ray);

	tex_x = calculate_texture_x(ray, texture);
	y = 0;
	while (y < SCREEN_HEIGHT)
	{
		color = get_pixel_color(game, y, wall, texture, tex_x);
		put_pixel_to_image(game, ray_index, y, color);
		y++;
	}
}

void	render_game(t_game *game)
{
	t_ray	ray;
	float	fov;
	float	start_angle;
	float	angle_step;
	int		ray_index;

	fov = 60.0 * (M_PI / 180);
	start_angle = atan2(game->player.dir_y, game->player.dir_x) - fov / 2;
	angle_step = fov / SCREEN_WIDTH;
	ray_index = 0;
	while (ray_index < SCREEN_WIDTH)
	{
		init_ray(game, ray_index, start_angle, angle_step, &ray);
		if (cast_ray(game, &ray, ray_index))
			draw_wall_slice(game, &ray, ray_index);
		ray_index++;
	}
	mlx_put_image_to_window(game->mlx, game->window, game->img, 0, 0);
}
