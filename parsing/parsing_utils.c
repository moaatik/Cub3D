/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenmoha <hbenmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 14:20:08 by hbenmoha          #+#    #+#             */
/*   Updated: 2025/10/02 23:19:10 by hbenmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

//* calculate a str lenght
int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

//* check if a str contain a whitspace
int	is_space(char *str)
{
	while (*str)
	{
		if ((*str >= 9 && *str <= 13) || *str == 32)
			return (1);
		str++;
	}
	return (0);
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

//* compare 2 strings
int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
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

//* get the path from map + remove spaces
char	*get_path_from_map(char *line)
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

int	convert_rgb_from_str_to_int(char **rgb_strs)
{
	int	i;
	int	rgb[3];

	i = 0;
	while (rgb_strs[i])
	{
		rgb_strs[i] = get_path_from_map(rgb_strs[i]);
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
	color_str = get_path_from_map(line);
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
	// calculate_size(game, fd);
	// close(fd);
	// fd = open(map_file, O_RDONLY);
	// if (fd == -1)
	// {
	// 	ft_putstr_fd("Error\nMap file not found or inaccessible.\n", 2);
	// 	exit(1);
	// }
	// make_area(fd, game);
	// close(fd);
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

void	init_game_data(t_game *game)
{
	ft_bzero(game, sizeof(*game));
	game->ceiling_color = -1;
	game->floor_color = -1;
}

//* copy the map from file (.cub) to 2D array
// void	make_area(int fd, t_game *game)
// {
// 	char	**map;
// 	char	*line;
// 	int		i;

// 	i = 0;
// 	map = ft_safe_malloc(sizeof(char *) * (game->height + 1), ALLOCATE, 1, NULL);
// 	line = get_next_line(fd);
// 	while (line)
// 	{
// 		map[i] = ft_safe_malloc(sizeof(char) * (ft_strlen_map_check(line) + 1), ALLOCATE, 1, NULL);
// 		ft_strcpy(map[i], line);
// 		free(line);
// 		i++;
// 		line = get_next_line(fd);
// 	}
// 	map[i] = NULL;
// 	game->map = map;
// }
