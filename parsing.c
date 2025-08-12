/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaatik <moaatik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 09:51:19 by moaatik           #+#    #+#             */
/*   Updated: 2025/08/12 16:21:30 by moaatik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	check_file(char *file)
{
	int	len;
	int	fd;

	if (!file)
		return (1);
	len = ft_strlen(file);
	if (ft_strcmp(file + len - 4, ".cub"))
		return (-1);
	fd = open(file, O_RDONLY);
	return (fd);
}

char	*get_map(int fd)
{
	char	*line;
	char	*temp;
	char	*map;

	line = get_next_line(fd);
	map = NULL;
	while (line)
	{
		temp = map;
		map = ft_strjoin(temp, line);
		if (!map || *line == '\n')
			return (free(temp), free(line), NULL);
		free(line);
		free(temp);
		line = get_next_line(fd);
	}
	return (map);
}
char	**input(char **av)
{
	int		fd;
	char	*map;
	char	**splitted_map;

	if (!av || !av[1])
		return (write(2, "Error\nNo config file found\n", 27), NULL);
	fd = check_file(av[1]);
	if (fd < 0)
		return (write(2, "Error\nwhile opening the file\n", 29), NULL);
	map = get_map(fd);
	if (!map)
		return (write(2, "Error\nwhile reading the file\n", 29), \
		close(fd), NULL);
	splitted_map = ft_split(map, '\n');
	if (!splitted_map)
		return (write(2, "Error\nFailed while splitting map\n", 33), free(map), \
		close(fd), NULL);
	free(map);
	close(fd);
	return (splitted_map);
}

void	get_map_info(t_game *game)
{
	int	y;
	int	x;
	int	max_width;

	y = 0;
	max_width = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == 'N' || game->map[y][x] == 'S' 
			|| game->map[y][x] == 'W' || game->map[y][x] == 'E')
			{
				game->player_y = y * BLOCK_SIZE + BLOCK_SIZE / 2;
				game->player_x = x * BLOCK_SIZE + BLOCK_SIZE / 2;

				if (game->map[y][x] == 'N')
				{
					game->dir_x = 0;
					game->dir_y = -1;
				}
				else if (game->map[y][x] == 'S')
				{
					game->dir_x = 0;
					game->dir_y = 1;
				}
				else if (game->map[y][x] == 'W')
				{
					game->dir_x = -1;
					game->dir_y = 0;
				}
				else if (game->map[y][x] == 'E')
				{
					game->dir_x = 1;
					game->dir_y = 0;
				}
				game->map[y][x] = '0';
			}
			x++;
		}
		if (x > max_width)
			max_width = x;
		y++;
	}
	game->max_y = y;
	game->max_x = max_width;
	game->ceiling_color = 0x00FFFF;
	game->floor_color = 0xFF8C00;
}
