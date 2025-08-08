/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaatik <moaatik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 09:51:19 by moaatik           #+#    #+#             */
/*   Updated: 2025/08/08 10:05:13 by moaatik          ###   ########.fr       */
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
	if (fd == -1)
		return (-1);
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
		return (NULL);
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
