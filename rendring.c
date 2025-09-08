/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendring.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaatik <moaatik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 16:57:56 by moaatik           #+#    #+#             */
/*   Updated: 2025/09/08 11:49:17 by moaatik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void init_ray(t_game *game, int ray_index, float start_angle, float angle_step, t_ray *ray)
{
	ray->angle = start_angle + ray_index * angle_step;
	ray->dir_x = cos(ray->angle);
	ray->dir_y = sin(ray->angle);
	ray->x = game->player.x;
	ray->y = game->player.y;
}

void init_dda(t_game *game, t_ray *ray, t_cast *cast)
{
	cast->map_x = (int)(game->player.x / BLOCK_SIZE);
	cast->map_y = (int)(game->player.y / BLOCK_SIZE);

	if (ray->dir_x < 0)
		cast->step_x = -1;
	else
		cast->step_x = 1;

	if (ray->dir_y < 0)
		cast->step_y = -1;
	else
		cast->step_y = 1;

	if (ray->dir_x == 0)
		cast->delta_dist_x = 1e30f;
	else
		cast->delta_dist_x = fabs(1.0f / ray->dir_x);

	if (ray->dir_y == 0)
		cast->delta_dist_y = 1e30f;
	else
		cast->delta_dist_y = fabs(1.0f / ray->dir_y);

	if (ray->dir_x < 0)
		cast->side_dist_x = (game->player.x / BLOCK_SIZE - cast->map_x) * (cast->delta_dist_x);
	else
		cast->side_dist_x = (cast->map_x + 1.0f - game->player.x / BLOCK_SIZE) * (cast->delta_dist_x);

	if (ray->dir_y < 0)
		cast->side_dist_y = (game->player.y / BLOCK_SIZE - cast->map_y) * (cast->delta_dist_y);
	else
		cast->side_dist_y = (cast->map_y + 1.0f - game->player.y / BLOCK_SIZE) * (cast->delta_dist_y);
}

int perform_dda(t_game *game, t_cast *cast, int *side)
{
	int	hit = 0;

	*side = 0;
	while (!hit)
	{
		if (cast->side_dist_x < cast->side_dist_y)
		{
			cast->side_dist_x += cast->delta_dist_x;
			cast->map_x += cast->step_x;
			*side = 0;
		}
		else
		{
			cast->side_dist_y += cast->delta_dist_y;
			cast->map_y += cast->step_y;
			*side = 1;
		}

		if (cast->map_x < 0 || cast->map_y < 0 || cast->map_x >= game->max_x || cast->map_y >= game->max_y)
			return (0);

		if (game->map[cast->map_y][cast->map_x] == '1')
			hit = 1;
	}
	return (1);
}

float distance(t_game *game, t_ray *ray, t_cast *cast, int side)
{
	float	dist;
	float	player_cell_x;
	float	player_cell_y;
	float	dist_world;

	if (side == 0)
	{
		player_cell_x = game->player.x / BLOCK_SIZE;
		dist = (cast->map_x - player_cell_x + (1 - cast->step_x) / 2) / ray->dir_x;
	}
	else
	{
		player_cell_y = game->player.y / BLOCK_SIZE;
		dist = (cast->map_y - player_cell_y + (1 - cast->step_y) / 2) / ray->dir_y;
	}

	dist_world = dist * BLOCK_SIZE;

	ray->x = game->player.x + ray->dir_x * dist_world;
	ray->y = game->player.y + ray->dir_y * dist_world;

	dist_world *= game->player.dir_x * ray->dir_x + game->player.dir_y * ray->dir_y;
	return (dist_world);
}

float cast_ray(t_game *game, t_ray *ray, int *side)
{
	t_cast	cast;

	init_dda(game, ray, &cast);

	if (!perform_dda(game, &cast, side))
		return (-1);
	return (distance(game, ray, &cast, *side));
}

unsigned int get_texture_color(t_texture *texture, int x, int y)
{
	void *pixel;

	if (x < 0 || y < 0 || x >= texture->width || y >= texture->height)
		return (0);

	pixel = texture->address + (y * texture->size_line + x * (texture->bpp / 8));
	return (*(unsigned int *)pixel);
}

void put_pixel_to_image(t_game *game, int x, int y, unsigned int color)
{
	void *pixel;

	pixel = game->address + (y * game->size_line + x * (game->bpp / 8));
	*(unsigned int *)pixel = color;
}

t_texture *get_wall_texture(t_game *game, int side, t_ray *ray)
{
	if (side == 0) // vertical (x)
	{
		if (ray->dir_x > 0)
			return (&game->w_wall);
		else
			return (&game->e_wall);
	}
	else // horizontal (y)
	{
		if (ray->dir_y > 0)
			return (&game->n_wall);
		else
			return (&game->s_wall);
	}
}

void calculate_wall_dimensions(float dist, t_wall *wall)
{
	if (dist <= 0)
		dist = 1;
	wall->height = (int)(BLOCK_SIZE * SCREEN_HEIGHT / dist);
	wall->start = (SCREEN_HEIGHT - wall->height) / 2;
	wall->end = wall->start + wall->height;
}

int calculate_texture_x(t_ray *ray, t_texture *tex, int side)
{
	float	wall_x;
	int		tex_x;

	if (side == 0)
		wall_x = fmod(ray->y, (float)BLOCK_SIZE) / (float)BLOCK_SIZE;
	else
		wall_x = fmod(ray->x, (float)BLOCK_SIZE) / (float)BLOCK_SIZE;

	tex_x = (int)(wall_x * tex->width);
	if (tex_x < 0)
		tex_x = 0;
	else if (tex_x >= tex->width)
		tex_x = tex->width - 1;
	return (tex_x);
}

int calculate_texture_y(int screen_y, t_wall wall, t_texture *texture)
{
	float tex_pos;
	int tex_y;

	tex_pos = (float)(screen_y - wall.start) / (float)wall.height;
	tex_y = (int)(tex_pos * texture->height);

	if (tex_y < 0)
		tex_y = 0;
	else if (tex_y >= texture->height)
		tex_y = texture->height - 1;
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

void draw_wall_slice(t_game *game, t_ray *ray, int ray_index, float dist_world, int side)
{
	t_wall      wall;
	t_texture  *texture;
	int         tex_x;
	int         y;
	unsigned int color;

	calculate_wall_dimensions(dist_world, &wall);

	texture = get_wall_texture(game, side, ray);

	tex_x = calculate_texture_x(ray, texture, side);

	y = 0;
	while (y < SCREEN_HEIGHT)
	{
		color = get_pixel_color(game, y, wall, texture, tex_x);
		put_pixel_to_image(game, ray_index, y, color);
		y++;
	}
}

void render_game(t_game *game)
{
	t_ray ray;
	float fov;
	float start_angle;
	float angle_step;
	int ray_index;
	int side;
	float dist;

	fov = 60.0f * (M_PI / 180.0f);
	start_angle = atan2f(game->player.dir_y, game->player.dir_x) - fov / 2.0f;
	angle_step = fov / (float)SCREEN_WIDTH;

	ray_index = 0;
	while (ray_index < SCREEN_WIDTH)
	{
		init_ray(game, ray_index, start_angle, angle_step, &ray);
		dist = cast_ray(game, &ray, &side);
		if (dist > 0)
			draw_wall_slice(game, &ray, ray_index, dist, side);
		ray_index++;
	}
	mlx_put_image_to_window(game->mlx, game->window, game->img, 0, 0);
}
