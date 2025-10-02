/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenmoha <hbenmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 16:15:40 by hbenmoha          #+#    #+#             */
/*   Updated: 2025/10/02 12:44:49 by hbenmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	parse_map(int ac, char *av[], t_game *game)
{
	(void) game;
	char	*line;
	char	*tmp;
	int		fd;

	if (ac != 2)
	{
		ft_putstr_fd("Error\nNo config file found\n", 2);
		ft_safe_malloc(0, FREE_ALL, 1, NULL);
	}
	check_map_extension(av[1]);
	fd = check_map_exists(av[1]);
	init_game_data(game);
	line = get_next_line(fd);
	tmp = line;
	while (line)
	{
		if (*line == '\n')
		{
			ft_safe_malloc(0, FREE_ONE, 1, tmp);
			line = get_next_line(fd);
			tmp = line;
			continue ;
		}
		//* skip white spaces at the start
		while ((*line >= 9 && *line <= 13) || *line == 32)
			line++;
		
		//* check if it's an instractions (NO/SO/WE/EA) (F/C)
		if (ft_strncmp(line, "NO", 2) == 0)
		{
			line += 2;
			if ((*line < 9 || *line > 13) && *line != 32)
			{
				ft_putstr_fd("Error\nInvalid texture identifier format\n", 2);
				ft_safe_malloc(0, FREE_ALL, 1, NULL);
			}
			game->n_wall.path = get_path_from_map(line);
			check_path_exist(game->n_wall.path);
		}
		else if (ft_strncmp(line, "SO", 2) == 0)
		{
			line += 2;
			if ((*line < 9 || *line > 13) && *line != 32)
			{
				ft_putstr_fd("Error\nInvalid texture identifier format\n", 2);
				ft_safe_malloc(0, FREE_ALL, 1, NULL);
			}
			game->s_wall.path = get_path_from_map(line);
			check_path_exist(game->s_wall.path);
		}
		else if (ft_strncmp(line, "WE", 2) == 0)
		{
			line += 2;
			if ((*line < 9 || *line > 13) && *line != 32)
			{
				ft_putstr_fd("Error\nInvalid texture identifier format\n", 2);
				ft_safe_malloc(0, FREE_ALL, 1, NULL);
			}
			game->w_wall.path = get_path_from_map(line);
			check_path_exist(game->w_wall.path);
		}
		else if (ft_strncmp(line, "EA", 2) == 0)
		{
			line += 2;
			if ((*line < 9 || *line > 13) && *line != 32)
			{
				ft_putstr_fd("Error\nInvalid texture identifier format\n", 2);
				ft_safe_malloc(0, FREE_ALL, 1, NULL);
			}
			game->e_wall.path = get_path_from_map(line);
			check_path_exist(game->e_wall.path);
		}
		else if (ft_strncmp(line, "F", 1) == 0)
		{
			line++;
			if ((*line < 9 || *line > 13) && *line != 32)
			{
				ft_putstr_fd("Error\nInvalid texture identifier format\n", 2);
				ft_safe_malloc(0, FREE_ALL, 1, NULL);
			}
			game->floor_color = get_color_from_map(line);
		}
		else if (ft_strncmp(line, "C", 1) == 0)
		{
			line++;
			if ((*line < 9 || *line > 13) && *line != 32)
			{
				ft_putstr_fd("Error\nInvalid texture identifier format\n", 2);
				ft_safe_malloc(0, FREE_ALL, 1, NULL);
			}
			game->ceiling_color = get_color_from_map(line);
		}
		else if (!game->n_wall.path || !game->s_wall.path || !game->w_wall.path || !game->e_wall.path || game->floor_color == -1 || game->ceiling_color == -1)
		{
			ft_putstr_fd("Error\nInstructions not found\n", 2);
			ft_safe_malloc(0, FREE_ALL, 1, NULL);
		}
		ft_safe_malloc(0, FREE_ONE, 1, tmp);
		line = get_next_line(fd);
		tmp = line;
	}
	//? debuging: 
	printf("everything is correct !\n");
	printf("DATA:\n");
	printf("NO => [%s]\n", game->n_wall.path);
	printf("SO => [%s]\n", game->s_wall.path);
	printf("WE => [%s]\n", game->w_wall.path);
	printf("EA => [%s]\n", game->e_wall.path);
	printf("F  => [%d]\n", game->floor_color);
	printf("F  => [%d]\n", game->ceiling_color);
	printf("line => [%s]\n", line);
	close(fd);
}


//to