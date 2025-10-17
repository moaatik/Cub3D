/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenmoha <hbenmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 16:15:40 by hbenmoha          #+#    #+#             */
/*   Updated: 2025/10/14 10:54:13 by hbenmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	parse_map(int ac, char *av[], t_game *game)
{
	char	*line;
	char	*cursor;
	int		fd;

	if (ac != 2)
		error_exit("Error\nNo config file found\n");

	check_map_extension(av[1]);
	fd = check_map_exists(av[1]);
	init_game_data(game);
	line = get_next_line(fd);
	while (line)
	{
		cursor = skip_white_spaces(line);

		//* skip empty lines
		if (!*cursor)
		{
			ft_safe_malloc(0, FREE_ONE, 1, line);
			line = get_next_line(fd);
			continue ;
		}
		else if (is_instruction(cursor))
			parse_instructions(game, cursor);
		else if (it_is_map(cursor))
		{
			check_all_instructions_are_before_map(game);
            parse_map_block(fd, line, game); //todo:
 			ft_safe_malloc(0, FREE_ONE, 1, line);
			break;
		}
		else
			error_exit("Error\nInstructions not correct\n");

		ft_safe_malloc(0, FREE_ONE, 1, line);
		line = get_next_line(fd);
	}

	close(fd);
}
