/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaatik <moaatik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 20:21:55 by moaatik           #+#    #+#             */
/*   Updated: 2025/11/09 20:29:52 by moaatik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	init_ray(t_game *game, int ray_index, float start_angle,
	float angle_step)
{
	game->ray.angle = start_angle + ray_index * angle_step;
	game->ray.dir_x = cos(game->ray.angle);
	game->ray.dir_y = sin(game->ray.angle);
	game->ray.x = game->player.x;
	game->ray.y = game->player.y;
}

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
