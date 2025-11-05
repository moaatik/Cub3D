/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenmoha <hbenmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 15:35:02 by moaatik           #+#    #+#             */
/*   Updated: 2025/11/05 10:40:08 by hbenmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int main(int ac, char **av)
{
	t_game	game;

	//* parsing
	parse_map(ac, av, &game);
	data_init(); //todo



	//* debuging: 
	printf("everything is correct !\n");
	printf("DATA:\n");
	printf("NO => [%s]\n", game.n_wall.path);
	printf("SO => [%s]\n", game.s_wall.path);
	printf("WE => [%s]\n", game.w_wall.path);
	printf("EA => [%s]\n", game.e_wall.path);
	printf("F  => [%d]\n", game.floor_color);
	printf("F  => [%d]\n", game.ceiling_color);
	printf("map heigh => [%d]\n", game.map.height);
	printf("map width = [%d]\n", game.map.width);
	printf("\n==== map block ====\n\n");
	while (*game.map.map_matrix)
	{
		printf("[%s]\n", *game.map.map_matrix++);
	}

	return (0);
}
