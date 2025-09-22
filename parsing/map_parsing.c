/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenmoha <hbenmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 16:15:40 by hbenmoha          #+#    #+#             */
/*   Updated: 2025/09/22 17:57:36 by hbenmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

//todo: check ac == 2    (done)
//todo: check .cub extension (done)
//todo: check if the map file exist + accessible (done)
//todo: read a line by line then check if this line is (instraction | map)


void	parse_map(int ac, char *av[], t_game *game)
{
	(void) game;
	char	*line;
	int		fd;

	if (ac != 2)
	{
	ft_putstr_fd("Error\nNo config file found\n", 2);
		exit(1);
	}
	check_map_extension(av[1]);
	fd = check_map_exists(av[1]);
	
	line = get_next_line(fd);
	while (line)
	{
		if (*line == '\n')
		{
			line = get_next_line(fd);
			continue ;
		}
		//* skip white spaces at the start
		while ((*line >= 9 && *line <= 13) || *line == 32)
			line++;
		
		//todo: check if it's an instractions (NO/SO/WE/EA) (F/C)
		if (ft_strncmp(line, "NO", 2) == 0)
		{
			line += 2;
			while ((*line >= 9 && *line <= 13) || *line == 32)
				line++;
			game->n_wall.path = get_path_from_map(line);
			printf("path of NO => [%s]\n", game->n_wall.path);
		}
		else if (ft_strncmp(line, "SO", 2) == 0)
		{
			line += 2;
			while ((*line >= 9 && *line <= 13) || *line == 32)
				line++;
			game->s_wall.path = get_path_from_map(line);
			printf("path of SO => [%s]\n", game->s_wall.path);
		}
		else if (ft_strncmp(line, "WE", 2) == 0)
		{
			line += 2;
			while ((*line >= 9 && *line <= 13) || *line == 32)
				line++;
			game->w_wall.path = get_path_from_map(line);
			printf("path of WE => [%s]\n", game->w_wall.path);
		}
		else if (ft_strncmp(line, "EA", 2) == 0)
		{
			line += 2;
			while ((*line >= 9 && *line <= 13) || *line == 32)
				line++;
			game->e_wall.path = get_path_from_map(line);
			printf("path of EA => [%s]\n", game->e_wall.path);
		}
		else if (ft_strncmp(line, "F", 1) == 0)
		{
			line++;
			while ((*line >= 9 && *line <= 13) || *line == 32)
				line++;
			// game->floor_color = get_color_from_map(); //todo: make a fun that give you to color from map after it's convert from RGB to int
		}
		else if (ft_strncmp(line, "C", 1) == 0)
		{
			line++;
			while ((*line >= 9 && *line <= 13) || *line == 32)
				line++;
			// game->ceiling_color = get_color_from_map(); //todo: make a fun that give you to color from map after it's convert from RGB to int
		}
		else
		{
			ft_putstr_fd("Error\nInstructions not found\n", 2); //todo: here you should know if you get all the instruction or not ! so you have to make the game.s_wall.path = NULL, and once you get them from map init it, and at the end (here) check if any instruction = NULL, that mean it's not inited yet! => error. check it once you have *line == 0|1
			printf("line => [%s]", line);
			exit(1); //todo: should I call ft_safe_malloc here !? todo: call ft_safe malloc just because it's have exit inside it !
		}
		line = get_next_line(fd);
	}
	close(fd);
}
