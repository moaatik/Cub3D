/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaatik <moaatik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 17:28:54 by moaatik           #+#    #+#             */
/*   Updated: 2025/08/12 18:54:44 by moaatik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <mlx.h>
# include <math.h>

# ifndef BLOCK_SIZE
#  define BLOCK_SIZE 300
# endif

# ifndef SPEED
#  define SPEED 50
# endif

# ifndef ROT_SPEED
#  define ROT_SPEED 0.1
# endif

# ifndef SCREEN_WIDTH
#  define SCREEN_WIDTH 800
# endif

# ifndef SCREEN_HEIGHT
#  define SCREEN_HEIGHT 600
# endif

typedef struct s_ray
{
    float	angle;
    float	dir_x;
    float	dir_y;
    float	x;
    float	y;
}	t_ray;

typedef struct s_game
{
	void	*mlx;
	void	*window;
	char	**map;
	float	player_y;
	float	player_x;
	float	dir_y;
	float	dir_x;
	float	rot_speed;
	int		max_x;
	int		max_y;

	void    *img;
    char    *img_data;
    int     bpp;
    int     size_line;
    int     endian;

	int		ceiling_color;
	int		floor_color;
}			t_game;

//parser
char	**input(char **av);
void	get_map_info(t_game *game);

//rander
void	render_map(t_game *game);
void	render_game(t_game *game);
void	my_mlx_pixel_put(t_game *game, int x, int y, int color);
void	*create_colored_tile(t_game *game, int r, int g, int b, int size);
void	draw_vertical_line(t_game *game, int x, int start_y, int end_y, int color);

// moves :
void	move_left(t_game *game);
void	move_right(t_game *game);
void	move_forward(t_game *game);
void	move_backward(t_game *game);

void	rotate_left(t_game *game);
void	rotate_right(t_game *game);

// utils :
void	free_strs(char **strs);
char	*get_next_line(int fd);
int		ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
char	*ft_strchr(const char *s, int c);
char	**ft_split(char const *s, char c);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);

#endif