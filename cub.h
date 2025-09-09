/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaatik <moaatik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 17:28:54 by moaatik           #+#    #+#             */
/*   Updated: 2025/09/09 12:21:06 by moaatik          ###   ########.fr       */
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
#  define BLOCK_SIZE 64
# endif

# ifndef SPEED
#  define SPEED 7
# endif

# ifndef ROT_SPEED
#  define ROT_SPEED 0.1
# endif

# ifndef SCREEN_WIDTH
#  define SCREEN_WIDTH 2000
# endif

# ifndef SCREEN_HEIGHT
#  define SCREEN_HEIGHT 1000
# endif

typedef struct s_texture
{
	void    *img;
	char    *address;
	int     width;
	int     height;
	int     bpp;
	int     size_line;
	int     endian;
}  			t_texture;

typedef struct s_cast
{
	int     map_x;
	int     map_y;
	int     step_x;
	int     step_y;
	float	dist_x;
	float	dist_y;
	float	side_dist_x;
	float	side_dist_y;
}  			t_cast;

typedef struct s_ray
{
	float	angle;
	float	dir_x;
	float	dir_y;
	float	x;
	float	y;
}			t_ray;

typedef struct s_wall
{
	int height;
	int start;
	int end;
}	    t_wall;

typedef struct s_player
{
	float   y;
	float   x;
	float   dir_y;
	float   dir_x;
	float   rot_speed;
}           t_player;

typedef struct	s_game
{
	void		*mlx;
	void		*window;
	t_texture   n_wall;
	t_texture	s_wall;
	t_texture	e_wall;
	t_texture	w_wall;

	t_player    player;
	t_ray		ray;
	t_wall		wall;
	t_cast		cast;
	
	char		**map;
	int			max_x;
	int			max_y;

	int			side;

	void    	*img;
	char    	*address;
	int     	bpp;
	int     	size_line;
	int     	endian;
	
	int			ceiling_color;
	int			floor_color;
}				t_game;

//parser
char	**input(char **av);
void	get_map_info(t_game *game);

//rander
void	render_game(t_game *game);

// moves :
void	move_left(t_game *game);
void	move_right(t_game *game);
void	move_forward(t_game *game);
void	move_backward(t_game *game);
void	rotate(t_game *game, int dir);


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
