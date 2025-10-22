/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenmoha <hbenmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 14:20:08 by hbenmoha          #+#    #+#             */
/*   Updated: 2025/10/22 10:59:03 by hbenmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

//* skip white spaces at the start of str
char	*skip_white_spaces(char *str)
{
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	return (str);
}

//* returns true if starts with NO, SO, WE, EA, F, or C.
bool	is_instruction(char *str)
{
	return (
		!ft_strncmp(str, "NO", 2)
		|| !ft_strncmp(str, "SO", 2)
		|| !ft_strncmp(str, "WE", 2)
		|| !ft_strncmp(str, "EA", 2)
		|| !ft_strncmp(str, "F", 1)
		|| !ft_strncmp(str, "C", 1)
	);
}

//* print a str in STDERR, free everything and exit.
void	error_exit(char *str)
{
	ft_putstr_fd(str, 2);
	ft_safe_malloc(0, FREE_ALL, 1, NULL);
}

//* calculate a str lenght
int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

//* check if a str contain a whit_spaces
bool	is_space(char *str)
{
	while (*str)
	{
		if ((*str >= 9 && *str <= 13) || *str == 32)
			return (true);
		str++;
	}
	return (false);
}

//* check if a str doesn't contain a white_sapces
bool	is_not_space(char *str)
{
	return ((*str < 9 || *str > 13) && *str != 32);
}

//* check if a str is only white spaces
bool	is_only_white_spaces(char *str)
{
	while (*str)
	{
		if((*str < 9 || *str > 13) && *str != 32)
			return (false);
		str++;
	}
	return (true);
}

//* check if *str == 0 or 1 (which means it's a map)
bool	it_is_map(char *str)
{
	return(*str == '0' || *str == '1');
}

//* converte ascii to integer + check if nb > 255
int	ft_atoi(char *str)
{
	long	nb;

	nb = 0;
	if (!str)
		return (-1);
	while (*str >= '0' && *str <= '9')
	{
		nb = (nb * 10) + (*str++ - 48);
		if (nb > 255)
			return (-1);
	}
	return ((int)nb);
}

//* print a string in a fd
void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	if (fd < 0)
		return ;
    write(fd, s, ft_strlen(s));
}

//* search for a char in a str
char	*ft_strchr (char *s, int c)
{
	while (s && *s)
	{
		if (*s == c)
			return(s);
		s++;
	}
	return (NULL);
}

//* copy a str to a dest
void	ft_strcopy(char *d, char* s)
{
	if (!d || !s)
		return ;
	while (*s)
		*d++ = *s++;
	*d = '\0';
}

//* duplicate a str
char	*ft_strdup(char *s)
{
	char	*str;

	if (!s)
		return (NULL);
	str = ft_safe_malloc(ft_strlen(s) + 1, ALLOCATE, 1, NULL);
	ft_strcopy(str, s);
	return(str);
}

//* join 2 strings and free the first one
char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		j;
	int		i;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return ((char *)(s2));
	if (!s2)
		return ((char *)(s1));
	j = 0;
	i = 0;
	str = ft_safe_malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char), ALLOCATE, 1, NULL);
	while (s1[i])
		str[j++] = s1[i++];
	i = 0;
	while (s2[i])
		str[j++] = s2[i++];
	str[j] = 0;
	ft_safe_malloc(0, FREE_ONE, 1, s1);
	return (str);
}

//* Checks if the map file has a `.cub` extension.
void	check_map_extension(char *map_name)
{
	size_t	len;

	len = ft_strlen(map_name);
	if (len < 4 || ft_strcmp(map_name + len - 4, ".cub") != 0)
	{
		ft_putstr_fd("Error\nMap file must have a .cub extension\n", 2);
		ft_safe_malloc(0, FREE_ALL, 1, NULL);
	}
}

//* compare 2 strs with a specific lenght 
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (n--)
	{
		if (*s1 != *s2 || !*s1 || !*s2)
			return ((unsigned char)*s1 - (unsigned char)*s2);
		s1++;
		s2++;
	}
	return (0);
}

//* compare 2 strings
int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

//* make a str from a str using start and lenght
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;

	if (!s)
		return (NULL);
	if (start > (unsigned int)ft_strlen(s) || len == 0)
		return (ft_strdup(""));
	if (len > (unsigned int)ft_strlen(s + start))
		len = ft_strlen(s + start);
	str = ft_safe_malloc(len + 1 * sizeof(char), ALLOCATE, 1, NULL);
	i = 0;
	while (i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	return (str);
}

//* take a str and trip spaces at the start + end
char	*trim_spaces(char *line)
{
	char	*str;
	int		i;

	i = 0;
	while ((*line >= 9 && *line <= 13) || *line == 32)
		line++;
	while (line[i])
		i++;
	i--;
	while ((line[i] >= 9 && line[i] <= 13) || line[i] == 32)
		i--;
	
	str = ft_substr(line, 0, i + 1);
	
	return (str);
}

//* convert rgb from 2D array to one int
int	convert_rgb_from_str_to_int(char **rgb_strs)
{
	int	i;
	int	rgb[3];

	i = 0;
	while (rgb_strs[i])
	{
		rgb_strs[i] = trim_spaces(rgb_strs[i]);
		if (is_space(rgb_strs[i]))
		{
				ft_putstr_fd("Error\nRGB is not correct!\n", 2);
				ft_safe_malloc(0, FREE_ALL, 1, NULL);
		}
		rgb[i] = ft_atoi(rgb_strs[i]);
		if (rgb[i] == -1)
		{
			ft_putstr_fd("Error\nRGB is not correct!\n", 2);
			ft_safe_malloc(0, FREE_ALL, 1, NULL);
		}
		i++;
	}
	return((rgb[0] << 16) | (rgb[1] << 8) | rgb[2]);
}

//* get the color from map + convert it to (int)
int	get_color_from_map(char *line)
{
	char	*color_str;
	char	**rgb_strs;
	int		words_nb;
	int		i;

	i = 0;
	color_str = trim_spaces(line);
	while (color_str[i])
	{
		if ((color_str[i] < '0' || color_str[i] > '9') && color_str[i] != ',' && (color_str[i] < 9 || color_str[i] > 13) && color_str[i] != 32)
		{
			ft_putstr_fd("Error\nRGB is not correct!\n", 2);
			ft_safe_malloc(0, FREE_ALL, 1, NULL);
		}
		i++;
	}
	rgb_strs = ft_split(color_str, ',', &words_nb);//* split RGB with ','
	if (words_nb != 3 || ft_count_char(color_str, ',', 2)) //* check if there is just 3 RGB strs
	{
		ft_putstr_fd("Error\nRGB is not correct!\n", 2);
		ft_safe_malloc(0, FREE_ALL, 1, NULL);
	}
	return (convert_rgb_from_str_to_int(rgb_strs)); //* it return a int ( converted from rgb str )
}

//* count how many times a char repeated
int	ft_count_char(char *str, char c, int reps)
{
	int	count;

	count = 0;
	if (!str)
		return (1);
	while (*str)
	{
		if (*str == c)
			count++;
		str++;
	}
	if (count != reps)
		return (1);
	return (0);
}

//* check if the map file exist & open the fd & calculate width + height & copy mape frome fd to 2D array
int	check_map_exists(char *map_file)
{
	int	fd;

	fd = open(map_file, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Error\nMap file not found or inaccessible.\n", 2);
		ft_safe_malloc(0, FREE_ALL, 1, NULL);
	}
	return (fd);
}

//* check if the path exist + accessible
void	check_path_exist(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Error\ntexture file not found or inaccessible.\n", 2);
		ft_safe_malloc(0, FREE_ALL, 1, NULL);
	}
	close(fd);
}

//* init game struct
void	init_game_data(t_game *game)
{
	ft_bzero(game, sizeof(*game));
	game->ceiling_color = -1;
	game->floor_color = -1;
}

//* parse north texture
void	parse_north_texture(char *cursor, t_game *game)
{
	if (game->n_wall.path != NULL)
		error_exit("Error\nDouble instructions\n");
	cursor += 2;
	if (is_not_space(cursor))
		error_exit("Error\nInvalid texture identifier format\n");
	game->n_wall.path = trim_spaces(cursor);
	check_path_exist(game->n_wall.path);
}

//* parse south texture
void	parse_south_texture(char *cursor, t_game *game)
{
	if (game->s_wall.path != NULL)
		error_exit("Error\nDouble instructions\n");
	cursor += 2;
	if (is_not_space(cursor))
		error_exit("Error\nInvalid texture identifier format\n");
	game->s_wall.path = trim_spaces(cursor);
	check_path_exist(game->s_wall.path);
}

//* parse west texture
void	parse_west_texture(char *cursor, t_game *game)
{
	if (game->w_wall.path != NULL)
		error_exit("Error\nDouble instructions\n");
	cursor += 2;
	if (is_not_space(cursor))
		error_exit("Error\nInvalid texture identifier format\n");
	game->w_wall.path = trim_spaces(cursor);
	check_path_exist(game->w_wall.path);
}

//* parse east texture
void	parse_east_texture(char *cursor, t_game *game)
{
	if (game->e_wall.path != NULL)
		error_exit("Error\nDouble instructions\n");
	cursor += 2;
	if (is_not_space(cursor))
		error_exit("Error\nInvalid texture identifier format\n");
	game->e_wall.path = trim_spaces(cursor);
	check_path_exist(game->e_wall.path);
}

//* parse floor color
void	parse_floor_color(char *cursor, t_game *game)
{
	if (game->floor_color != -1)
		error_exit("Error\nDouble instructions\n");
	cursor++;
	if (is_not_space(cursor))
		error_exit("Error\nInvalid texture identifier format\n");
	game->floor_color = get_color_from_map(cursor);
}

//* parse ceiling color
void	parse_ceiling_color(char *cursor, t_game *game)
{
	if (game->ceiling_color != -1)
		error_exit("Error\nDouble instructions\n");
	cursor++;
	if (is_not_space(cursor))
		error_exit("Error\nInvalid texture identifier format\n");
	game->ceiling_color = get_color_from_map(cursor);
}

//* parse instructions depends on its identifier
void	parse_instructions(t_game *game, char *cursor)
{
	if (!ft_strncmp(cursor, "NO", 2))
		parse_north_texture(cursor, game);
	else if (!ft_strncmp(cursor, "SO", 2))
		parse_south_texture(cursor, game);
	else if (!ft_strncmp(cursor, "WE", 2))
		parse_west_texture(cursor, game);
	else if (!ft_strncmp(cursor, "EA", 2))
		parse_east_texture(cursor, game);
	else if (!ft_strncmp(cursor, "F", 1))
		parse_floor_color(cursor, game);
	else if (!ft_strncmp(cursor, "C", 1))
		parse_ceiling_color(cursor, game);
}

//* check that all instructions are set before the map
void	check_all_instructions_are_before_map(t_game *game)
{
	if (!game->n_wall.path
		|| !game->s_wall.path
		|| !game->w_wall.path
		|| !game->e_wall.path
		|| game->floor_color == -1
		|| game->ceiling_color == -1)
		error_exit("Error\nInstructions not found\n");
}

//* parse map block
void	parse_map_block(int fd, char *line, t_game *game)
{
	(void)game;
	t_list	*map_list;

	map_list = convert_map_from_file_to_linked_list(fd, line);
	//todo: 3️⃣ Convert linked list to 2D array
}

//* read the map from fd and store it in a linked list
t_list	*convert_map_from_file_to_linked_list(int	fd, char *first_line)
{
	char	*line;
	t_list	*map_list;
	bool	empty_line;

	map_list = NULL;
	empty_line = false;
	ft_add_back(&map_list, first_line);
	line = get_next_line(fd);
	while (line)
	{
		if (is_only_white_spaces(line))
			empty_line = true;
		else
			ft_add_back(&map_list, line);
		ft_safe_malloc(0, FREE_ONE, 1, line);
		line = get_next_line(fd);
	}
	if (empty_line)
		error_exit("Error\nMap is not the last element in file\n");
	return (map_list);
}

//* create and add a new node to t_list linked list
void	ft_add_back(t_list **head, char *line)
{
	t_list	*new_node;
	t_list	*tmp_head;

	tmp_head = *head;
	new_node = ft_safe_malloc(sizeof(t_list), ALLOCATE, 1, NULL);
	new_node->line = ft_get_line_without_new_line(line);
	new_node->length = ft_strlen(new_node->line);
	if (!*head)
		*head = new_node;
	else
	{
		while (tmp_head->next)
			tmp_head = tmp_head->next;
		tmp_head->next = new_node;
	}
}

//* take a str and return it without '\n' at the end
char	*ft_get_line_without_new_line(char *str)
{
	if (str[ft_strlen(str) - 1] == '\n')
		return (ft_substr(str, 0, ft_strlen(str) - 1));
	return (ft_strdup(str));
}

/*
//? Calculate map dimensions (width/height) from file
static void	calculate_size(t_game *size, int fd)
{
	int		i;
	char	*tmp;
	
	i = 1;
	tmp = get_next_line(fd);
	if (!tmp)
	{
		ft_putstr_fd("Error\nEmpty map file.\n", 2);
		close(fd);
		exit(1);
	}
	size->width = ft_strlen_map_check(tmp);
	free(tmp);
	tmp = get_next_line(fd);
	while (tmp)
	{
		i++;
		free(tmp);
		tmp = get_next_line(fd);
	}
	size->height = i;
	check_map_fits_screen(size, fd);
}

// * Calculate map dimensions (width/height) from .cub file
void	calculate_map_size(t_game *game, int fd)
{
	int		i;
	char	*tmp;
	
	i = 1;
}

// * copy the map from file (.cub) to 2D array
void	make_area(int fd, t_game *game)
{
	char	**map;
	char	*line;
	int		i;
	
	i = 0;
	map = ft_safe_malloc(sizeof(char *) * (game->height + 1), ALLOCATE, 1, NULL);
	line = get_next_line(fd);
	while (line)
	{
		map[i] = ft_safe_malloc(sizeof(char) * (ft_strlen_map_check(line) + 1), ALLOCATE, 1, NULL);
		ft_strcpy(map[i], line);
		free(line);
		i++;
		line = get_next_line(fd);
	}
	map[i] = NULL;
	game->map = map;
}

*/
