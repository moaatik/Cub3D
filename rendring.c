/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendring.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaatik <moaatik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 15:29:07 by moaatik           #+#    #+#             */
/*   Updated: 2025/09/21 13:30:46 by moaatik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

unsigned int	get_texture_color(t_texture *texture, int x, int y)
{
	void	*pixel;

	if (x < 0 || y < 0 || x >= texture->width || y >= texture->height)
		return (0);
	pixel = texture->address + (y * texture->size_line + x
			* (texture->bpp / 8));
	return (*(unsigned int *)pixel);
}

void	put_pixel_to_image(t_game *game, int x, int y, unsigned int color)
{
	void	*pixel;

	pixel = game->address + (y * game->size_line + x * (game->bpp / 8));
	*(unsigned int *)pixel = color;
}

t_texture	*get_wall_texture(t_game *game)
{
	if (game->side == 0)
	{
		if (game->ray.dir_x > 0)
			return (&game->w_wall);
		else
			return (&game->e_wall);
	}
	else
	{
		if (game->ray.dir_y > 0)
			return (&game->n_wall);
		else
			return (&game->s_wall);
	}
}

void	calculate_wall_dimensions(float dist, t_game *game)
{
	if (dist <= 0)
		dist = 1;
	game->wall.height = (int)(BLOCK_SIZE * SCREEN_HEIGHT / dist);
	game->wall.start = (SCREEN_HEIGHT - game->wall.height) / 2;
	game->wall.end = game->wall.start + game->wall.height;
}

int	calculate_texture_x(t_game *game, t_texture *tex)
{
	float	wall_x;
	int		tex_x;

	if (game->side == 0)
		wall_x = fmod(game->ray.y, (float)BLOCK_SIZE) / (float)BLOCK_SIZE;
	else
		wall_x = fmod(game->ray.x, (float)BLOCK_SIZE) / (float)BLOCK_SIZE;
	tex_x = (int)(wall_x * tex->width);
	if (tex_x < 0)
		tex_x = 0;
	else if (tex_x >= tex->width)
		tex_x = tex->width - 1;
	return (tex_x);
}

int	calculate_texture_y(int screen_y, t_game *game, t_texture *texture)
{
	float	tex_pos;
	int		tex_y;

	tex_pos = (float)(screen_y - game->wall.start) / (float)game->wall.height;
	tex_y = (int)(tex_pos * texture->height);
	if (tex_y < 0)
		tex_y = 0;
	else if (tex_y >= texture->height)
		tex_y = texture->height - 1;
	return (tex_y);
}

unsigned int	get_pixel_color(t_game *game, int screen_y, t_texture *texture,
	int tex_x)
{
	int	tex_y;

	if (screen_y >= game->wall.start && screen_y <= game->wall.end)
	{
		tex_y = calculate_texture_y(screen_y, game, texture);
		return (get_texture_color(texture, tex_x, tex_y));
	}
	else if (screen_y < game->wall.start)
		return (game->ceiling_color);
	else
		return (game->floor_color);
}

void	draw_wall_slice(t_game *game, int ray_index, float dist_world)
{
	t_texture		*texture;
	int				tex_x;
	int				y;
	unsigned int	color;

	calculate_wall_dimensions(dist_world, game);
	texture = get_wall_texture(game);
	tex_x = calculate_texture_x(game, texture);
	y = 0;
	while (y < SCREEN_HEIGHT)
	{
		color = get_pixel_color(game, y, texture, tex_x);
		put_pixel_to_image(game, ray_index, y, color);
		y++;
	}
}
