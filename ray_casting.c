/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaatik <moaatik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 16:57:56 by moaatik           #+#    #+#             */
/*   Updated: 2025/11/07 15:55:48 by moaatik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"





static void	debug_texture(const char *name, t_texture *t)
{
	printf("===== Texture: %s =====\n", name);
	printf("  path      : %s\n", t->path ? t->path : "(null)");
	printf("  img       : %p\n", (void *)t->img);
	printf("  address   : %p\n", (void *)t->address);
	printf("  width     : %d\n", t->width);
	printf("  height    : %d\n", t->height);
	printf("  bpp       : %d\n", t->bpp);
	printf("  size_line : %d\n", t->size_line);
	printf("  endian    : %d\n", t->endian);
}

static void	debug_player(t_player *p)
{
	printf("===== Player =====\n");
	printf("  pos (x,y): %.2f, %.2f\n", p->x, p->y);
	printf("  dir (x,y): %.2f, %.2f\n", p->dir_x, p->dir_y);
	printf("  rot_speed: %.2f\n", p->rot_speed);
}

static void	debug_keys(t_keys *k)
{
	printf("===== Keys =====\n");
	printf("  W:%d A:%d S:%d D:%d Left:%d Right:%d Esc:%d\n",
		k->w, k->a, k->s, k->d, k->left, k->right, k->escape);
}

static void	debug_map(t_map *m)
{
	printf("===== Map =====\n");
	printf("  width: %d, height: %d\n", m->width, m->height);
	if (m->map_matrix)
	{
		printf("  matrix:\n");
		for (int i = 0; i < m->height; i++)
			printf("    %s\n", m->map_matrix[i]);
	}
	else
		printf("  matrix: (null)\n");
}

void	debug_game_state(t_game *g)
{
	printf("\n========= DEBUG GAME STATE =========\n");
	printf("mlx ptr     : %p\n", (void *)g->mlx);
	printf("window ptr  : %p\n", (void *)g->window);
	printf("main img ptr: %p\n", (void *)g->img);
	printf("address     : %p\n", (void *)g->address);
	printf("bpp:%d size_line:%d endian:%d\n",
		g->bpp, g->size_line, g->endian);

	debug_texture("North", &g->n_wall);
	debug_texture("South", &g->s_wall);
	debug_texture("East",  &g->e_wall);
	debug_texture("West",  &g->w_wall);

	debug_player(&g->player);
	debug_keys(&g->keys);
	debug_map(&g->map);

	printf("max_x:%d max_y:%d side:%d sprint:%d\n",
		g->max_x, g->max_y, g->side, g->sprint);
	printf("ceiling_color:%d floor_color:%d\n",
		g->ceiling_color, g->floor_color);
	printf("====================================\n\n");
}








void	init_ray(t_game *game, int ray_index, float start_angle,
	float angle_step)
{
	game->ray.angle = start_angle + ray_index * angle_step;
	game->ray.dir_x = cos(game->ray.angle);
	game->ray.dir_y = sin(game->ray.angle);
	game->ray.x = game->player.x;
	game->ray.y = game->player.y;
}

void init_dda(t_game *game)
{
    game->cast.map_x = (int)(game->player.x / BLOCK_SIZE);
    game->cast.map_y = (int)(game->player.y / BLOCK_SIZE);

    if (game->ray.dir_x < 0)
        game->cast.map_x_step = -1;
    else
        game->cast.map_x_step = 1;

    if (game->ray.dir_y < 0)
        game->cast.map_y_step = -1;
    else
        game->cast.map_y_step = 1;

    game->cast.step_x = fabs(1.0f / game->ray.dir_x);
    game->cast.step_y = fabs(1.0f / game->ray.dir_y);

    float player_grid_x = game->player.x / BLOCK_SIZE;
    float player_grid_y = game->player.y / BLOCK_SIZE;

    if (game->ray.dir_x < 0)
    {
        float distance_to_left_edge = player_grid_x - game->cast.map_x;
        game->cast.side_dist_x = distance_to_left_edge * game->cast.step_x;
    }
    else
    {
        float distance_to_right_edge = (game->cast.map_x + 1.0f) - player_grid_x;
        game->cast.side_dist_x = distance_to_right_edge * game->cast.step_x;
    }
    if (game->ray.dir_y < 0)
    {
        float distance_to_top_edge = player_grid_y - game->cast.map_y;
        game->cast.side_dist_y = distance_to_top_edge * game->cast.step_y;
    }
    else
    {
        float distance_to_bottom_edge = (game->cast.map_y + 1.0f) - player_grid_y;
        game->cast.side_dist_y = distance_to_bottom_edge * game->cast.step_y;
    }
}

int run_dda(t_game *game)
{
    while (1)
    {
        if (game->cast.side_dist_x < game->cast.side_dist_y)
        {
            game->cast.side_dist_x += game->cast.step_x;
            game->cast.map_x += game->cast.map_x_step;
            game->side = 0;
        }
        else
        {
            game->cast.side_dist_y += game->cast.step_y;
            game->cast.map_y += game->cast.map_y_step;
            game->side = 1;
        }

        if (game->cast.map_x < 0 || game->cast.map_x >= game->map.width ||
            game->cast.map_y < 0 || game->cast.map_y >= game->map.height)
            return 0;

        if (game->map.map_matrix[game->cast.map_y][game->cast.map_x] == '1')
            return 1;
    }
}

float distance(t_game *game)
{
    float wall_dist;

    if (game->side == 0)
        wall_dist = (game->cast.side_dist_x - game->cast.step_x);
    else
        wall_dist = (game->cast.side_dist_y - game->cast.step_y);

    wall_dist *= BLOCK_SIZE;

    game->ray.x = game->player.x + game->ray.dir_x * wall_dist;
    game->ray.y = game->player.y + game->ray.dir_y * wall_dist;

    wall_dist *= game->player.dir_x * game->ray.dir_x + game->player.dir_y * game->ray.dir_y;

    return (wall_dist);
}

float	cast_ray(t_game *game)
{
	init_dda(game);
	if (!run_dda(game))
		return (-1);
	return (distance(game));
}

void	render_game(t_game *game)
{
	float	fov;
	float	start_angle;
	float	angle_step;
	int		ray_index;
	float	dist;

	debug_game_state(game);
	fov = 60.0f * (M_PI / 180.0f);
	start_angle = atan2f(game->player.dir_y, game->player.dir_x) - fov / 2.0f;
	angle_step = fov / (float)SCREEN_WIDTH;
	ray_index = 0;
	while (ray_index < SCREEN_WIDTH)
	{
		init_ray(game, ray_index, start_angle, angle_step);
		dist = cast_ray(game);
		if (dist > 0)
			draw_wall_slice(game, ray_index, dist);
		ray_index++;
	}
	mlx_put_image_to_window(game->mlx, game->window, game->img, 0, 0);
}
