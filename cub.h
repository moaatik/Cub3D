/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaatik <moaatik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 17:28:54 by moaatik           #+#    #+#             */
/*   Updated: 2025/08/09 14:03:18 by moaatik          ###   ########.fr       */
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
#  define BLOCK_SIZE 30
# endif

# ifndef SPEED
#  define SPEED 6
# endif

# ifndef ROT_SPEED
#  define ROT_SPEED 0.1
# endif

# ifndef MAX_DEPTH
#  define MAX_DEPTH 1000
# endif

# ifndef SCREEN_WIDTH
#  define SCREEN_WIDTH 800
# endif

# ifndef SCREEN_HEIGHT
#  define SCREEN_HEIGHT 600
# endif

typedef struct s_game
{
	void	*mlx;
	void	*window;
	void	*map_window;
	char	**map;
	float	player_y;
	float	player_x;
	float	dir_y;
	float	dir_x;
	float	rot_speed;
	int		max_x;
	int		max_y;

	void    *img;          // mlx image pointer (framebuffer)
    char    *img_data;     // raw pixel data pointer
    int     bpp;           // bits per pixel
    int     size_line;     // bytes per line
    int     endian;  
}			t_game;

// moves :
void	move_forward(t_game *game);
void	move_backward(t_game *game);
void	move_right(t_game *game);
void	move_left(t_game *game);
void	rotate_left(t_game *game);
void	rotate_right(t_game *game);
char	**input(char **av);
char	*get_next_line(int fd);
void	get_map_info(t_game *game);

// utils :
char	*ft_strdup(const char *s1);
void	free_strs(char **strs);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strlen(const char *s);
char	**ft_split(char const *s, char c);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strchr(const char *s, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);

#endif