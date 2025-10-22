/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenmoha <hbenmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 17:28:54 by moaatik           #+#    #+#             */
/*   Updated: 2025/10/22 15:33:14 by hbenmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdbool.h>
// # include <mlx.h>
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

//* macro for get_next_line
#define BUFFER_SIZE 42

//* Macros for ft_safe_malloc keys:
# define ALLOCATE 1
# define FREE_ALL 0
# define FREE_ONE 2

//* ft_saf_malloc struct:
typedef struct s_mem_node
{
	void				*address;
	struct s_mem_node	*next;
}						t_mem_node;

//* a struct of linked_list of lines of map
typedef	struct s_list
{
	char	*line;
	int		length;
	struct s_list	*next;
}	t_list;

//* enum of instructions
typedef enum e_instructions_type
{
	NO,	//? North texture
	SO,	//? South texture
	WE,	//? West texture
	EA,	//? East texture
	F,	//? Floor color
	C,	//? Ceiling color
}	t_instructions_type;

typedef struct s_map
{
	char	**map_matrix;
	int		height;
	int		width;
}		t_map;

typedef struct s_texture
{
	int		id;			//* identifier of the texture (NO/SO/WE/EA/F/C) /? does realy need it !?
	char	*path;		//* path of the texture
	void    *img;		//* return value of mlx_xpm_file_to_image
	char    *address;	//* return value of mlx_get_data_addr
	int     width;		//* inited by mlx_xpm_file_to_image()
	int     height;		//* inited by mlx_xpm_file_to_image()
	int     bpp;		//* inited by mlx_get_data_addr()
	int     size_line;	//* inited by mlx_get_data_addr()
	int     endian;		//* needed by mlx_get_data_addr() but not used!
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
	
	t_map		map;
	// char		**map; //* it was used by "ktami" to stor the map matrix (it's useless now)
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

//* parsing
// char	**input(char **av);
// void	get_map_info(t_game *game);
void	parse_map_block(int fd, char *cursor, t_game *game);
void	error_exit(char *str);
bool	is_instruction(char *str);
char	*skip_white_spaces(char *str);
void    parse_map(int ac, char *av[], t_game *game);
void	check_map_extension(char *map_name);
void	check_path_exist(char *path);
int		check_map_exists(char *map_file);
char	*get_next_line(int fd);
int		ft_strlen(const char *s);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_putstr_fd(char *s, int fd);
char	*ft_strchr (char *s, int c);
void	ft_strcopy(char *d, char* s);
char	*ft_strdup(char *s);
char	*ft_strjoin(char *s1, char *s2);
void	*ft_safe_malloc(size_t size, int key, int exit_status, void *to_delete);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*trim_spaces(char *line);
char	**ft_split(const char *str, char c, int *words_nb);
int		get_color_from_map(char *line);
void	ft_bzero(void *s, size_t n);
void	init_game_data(t_game *game);
int		ft_count_char(char *str, char c, int reps);
void	check_all_instructions_are_before_map(t_game *game);
void	parse_instructions(t_game *game, char *cursor);
void	parse_north_texture(char *cursor, t_game *game);
void	parse_south_texture(char *cursor, t_game *game);
void	parse_west_texture(char *cursor, t_game *game);
void	parse_east_texture(char *cursor, t_game *game);
void	parse_floor_color(char *cursor, t_game *game);
void	parse_ceiling_color(char *cursor, t_game *game);
bool	str_is_space(char *str);
bool	is_not_space(char *str);
bool	it_is_map(char *str);
bool	is_only_white_spaces(char *str);
void	ft_add_back(t_list **head, char *line);
char	*ft_get_line_without_new_line(char *str);
t_list	*convert_map_from_file_to_linked_list(int	fd, char *first_line);
int		ft_lstsize(t_list *list);
char	**convert_linked_list_to_matrix(t_list *list, t_game *game);
bool	is_space(char c);

//* randering
// void	render_game(t_game *game);

//* moves :
// void	move_left(t_game *game);
// void	move_right(t_game *game);
// void	move_forward(t_game *game);
// void	move_backward(t_game *game);
// void	rotate(t_game *game, int dir);


//* utils :
// void	free_strs(char **strs);


// char	**ft_split(char const *s, char c);

#endif
