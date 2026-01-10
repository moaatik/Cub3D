/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenmoha <hbenmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 17:28:54 by moaatik           #+#    #+#             */
/*   Updated: 2025/12/26 15:51:45 by hbenmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <mlx.h>
# include <math.h>
# include <stdbool.h>

# define BLOCK_SIZE 64
# define SPEED 3
# define ROT_SPEED 0.05
# define SCREEN_WIDTH 2000
# define SCREEN_HEIGHT 1000

//* macro for get_next_line
# define BUFFER_SIZE 42

//* Macros for ft_open keys:
# define CREATE_FD 1
# define CLOSE_FDS 0

//* Macros for ft_safe_malloc keys:
# define ALLOCATE 1
# define FREE_ALL 0
# define FREE_ONE 2

//* ft_saf_malloc struct:
typedef struct s_mem_node
{
	void				*address;
	struct s_mem_node	*next;
}	t_mem_node;

//* ft_open struct:
typedef struct s_fds
{
	int				fd;
	struct s_fds	*next;
}	t_fds;

//* a struct of linked_list of lines of map
typedef struct s_list
{
	char			*line;
	int				length;
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
}	t_map;

typedef struct s_texture
{
	char	*path;
	void	*img;
	char	*address;
	int		width;
	int		height;
	int		bpp;
	int		size_line;
	int		endian;
}	t_texture;

typedef struct s_cast
{
	float	first_x;
	float	first_y;

	float	step_x;
	float	step_y;

	int		map_x;
	int		map_y;

	float	side_dist_y;
	float	side_dist_x;

	int		map_x_step;
	int		map_y_step;
}	t_cast;

typedef struct s_ray
{
	float	angle;
	float	dir_x;
	float	dir_y;
	float	x;
	float	y;
}	t_ray;

typedef struct s_wall
{
	int	height;
	int	start;
	int	end;
}	t_wall;

typedef struct s_player
{
	float	y;
	float	x;
	float	dir_y;
	float	dir_x;
	float	rot_speed;
}	t_player;

typedef struct s_keys
{
	int	w;
	int	a;
	int	s;
	int	d;
	int	left;
	int	right;
	int	escape;
}	t_keys;

typedef struct s_game
{
	void		*mlx;
	void		*window;
	t_texture	n_wall;
	t_texture	s_wall;
	t_texture	e_wall;
	t_texture	w_wall;

	t_player	player;
	t_cast		cast;
	t_keys		keys;
	t_ray		ray;
	t_wall		wall;

	t_map		map;

	int			side;

	int			sprint;

	void		*img;
	char		*address;
	int			bpp;
	int			size_line;
	int			endian;

	int			ceiling_color;
	int			floor_color;
}	t_game;

//* rander
void			render_game(t_game *game);
void			draw_wall_slice(t_game *game, int ray_index, float dist_world);
int				calculate_texture_y(int screen_y, t_game *game,
					t_texture *texture);
void			init_ray(t_game *game, int ray_index, float start_angle,
					float angle_step);
unsigned int	get_texture_color(t_texture *texture, int x, int y);
void			put_pixel_to_image(t_game *game, int x, int y,
					unsigned int color);
unsigned int	get_pixel_color(t_game *game, int screen_y, t_texture *texture,
					int tex_x);

//* moves :
void			move_left(t_game *game);
void			move_right(t_game *game);
void			move_forward(t_game *game);
void			move_backward(t_game *game);
void			rotate(t_game *game, int dir);

//* parsing functions
void			parse_map_block(int fd, char *cursor, t_game *game);
void			error_exit(char *str);
bool			is_instruction(char *str);
char			*skip_white_spaces(char *str);
void			parse_map(int ac, char *av[], t_game *game);
void			check_map_extension(char *map_name);
void			check_path_exist(char *path);
int				check_map_exists(char *map_file);
char			*get_next_line(int fd);
int				ft_strlen(const char *s);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
void			ft_putstr_fd(char *s, int fd);
char			*ft_strchr(char *s, int c);
void			ft_strcopy(char *d, char *s);
char			*ft_strdup(char *s);
char			*ft_strjoin(char *s1, char *s2);
void			*ft_safe_malloc(size_t size, int key, int exit_status,
					void *to_delete);
int				ft_open(const char *file, int oflag, int key);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*trim_spaces(char *line);
char			**ft_split(const char *str, char c, int *words_nb);
int				get_color_from_map(char *line);
void			ft_bzero(void *s, size_t n);
void			init_game_struct(t_game *game);
int				ft_count_char(char *str, char c, int reps);
void			check_all_instructions_are_before_map(t_game *game);
void			parse_instructions(t_game *game, char *cursor);
void			parse_north_texture(char *cursor, t_game *game);
void			parse_south_texture(char *cursor, t_game *game);
void			parse_west_texture(char *cursor, t_game *game);
void			parse_east_texture(char *cursor, t_game *game);
void			parse_floor_color(char *cursor, t_game *game);
void			parse_ceiling_color(char *cursor, t_game *game);
bool			str_is_space(char *str);
bool			is_not_space(char *str);
bool			it_is_map(char *str);
bool			is_only_white_spaces(char *str);
void			ft_add_back(t_list **head, char *line);
char			*ft_get_line_without_new_line(char *str);
t_list			*convert_map_from_file_to_linked_list(int fd, char *first_line);
int				ft_lstsize(t_list *list);
char			**convert_linked_list_to_matrix(t_list *list, t_game *game);
bool			is_space(char c);
void			check_map_border(t_game *game);
void			validate_map(t_game *game);
void			check_one_player(t_game *game);
bool			is_player(char c);
void			set_direction_vector(t_game *game, char player_position);
void			check_all_4_neighbors(int y, int x, t_game *game);
void			check_neigboors(t_game *game);
void			check_all_instructions_and_map_are_set(t_game *game);
void			convert_map_to_rectangular(t_game *game);
void			free_matrix(char **arr);
void			mlx_data_init(t_game *game);
int				ft_atoi(char *str);
int				convert_rgb_from_str_to_int(char **rgb_strs);
void			set_player_position(t_game *game, int *player_counter, int y,
					int x);
void			check_current_neighboor(char current_char);
void			check_valid_map_line(char *str);
int				update(t_game *game);
int				key_release(int keycode, t_game *game);
int				key_press(int keycode, t_game *game);
int				ft_exit(t_game *game);

#endif
