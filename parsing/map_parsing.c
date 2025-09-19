/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenmoha <hbenmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 16:15:40 by hbenmoha          #+#    #+#             */
/*   Updated: 2025/09/18 16:33:26 by hbenmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

//todo: check ac == 2    (done)
//todo: check .cub extension (done)
//todo: check if the map file exist + accessible + copy mape frome fd to 2D array


void    parse_map(int ac, char *av[], t_game *game)
{
    if (ac != 2)
    {
        ft_putstr_fd("Error\nNo config file found\n", 2);
        exit(1);
    }
    check_map_extension(av[1]);
    check_map_exist(av[1], game);
}

