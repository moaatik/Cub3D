/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenmoha <hbenmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 14:20:08 by hbenmoha          #+#    #+#             */
/*   Updated: 2025/09/21 11:09:54 by hbenmoha         ###   ########.fr       */
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
char	*ft_strjoin(char const *s1, char const *s2)
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
	if (!str)
		return (NULL);
	while (s1[i])
		str[j++] = s1[i++];
	i = 0;
	while (s2[i])
		str[j++] = s2[i++];
	str[j] = 0;
	free(s1);
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
		exit(1);
	}
}

//* check if the map file exist & open the fd & calculate width + height & copy mape frome fd to 2D array
void	check_map_exists(char *map_file)
{
	int	fd;

	fd = open(map_file, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Error\nMap file not found or inaccessible.\n", 2);
		exit(1);
	}
	// calculate_size(game, fd);//todo:
	// close(fd);
	// fd = open(map_file, O_RDONLY);
	// if (fd == -1)
	// {
	// 	ft_putstr_fd("Error\nMap file not found or inaccessible.\n", 2);
	// 	exit(1);
	// }
	// make_area(fd, game);
	close(fd);
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
