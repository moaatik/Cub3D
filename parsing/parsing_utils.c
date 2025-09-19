/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenmoha <hbenmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 14:20:08 by hbenmoha          #+#    #+#             */
/*   Updated: 2025/09/18 18:02:06 by hbenmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

//* print a string in a fd
void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	if (fd < 0)
		return ;
    write(fd, s, ft_strlen(s));
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
void	check_map_exists(char *map_file, t_game *game)
{
	int	fd;

	fd = open(map_file, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Error\nMap file not found or inaccessible.\n", 2);
		exit(1);
	}
	calculate_size(game, fd);//todo:
	close(fd);
	fd = open(map_file, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Error\nMap file not found or inaccessible.\n", 2);
		exit(1);
	}
	make_area(fd, game);
	close(fd);
}

//* copy the map from file (.cub) to 2D array
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
