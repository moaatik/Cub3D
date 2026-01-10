/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils_5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenmoha <hbenmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 11:23:11 by hbenmoha          #+#    #+#             */
/*   Updated: 2025/11/18 14:22:22 by hbenmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

//* free 2D array
void	free_matrix(char **arr)
{
	int	y;

	y = 0;
	while (arr[y])
		ft_safe_malloc(0, FREE_ONE, 1, arr[y++]);
	ft_safe_malloc(0, FREE_ONE, 1, arr);
}

//* count how many node in t_list
int	ft_lstsize(t_list *list)
{
	int	i;

	i = 0;
	while (list)
	{
		i++;
		list = list->next;
	}
	return (i);
}

//* convert the linked list to matrix
char	**convert_linked_list_to_matrix(t_list *list, t_game *game)
{
	char	**map_matrix;
	int		y;
	int		height;

	y = 0;
	height = ft_lstsize(list);
	game->map.height = height;
	game->map.width = list->length;
	map_matrix = ft_safe_malloc(height * sizeof(char *) + 1, ALLOCATE, 1, NULL);
	while (y < height)
	{
		if (list->length > game->map.width)
			game->map.width = list->length;
		check_valid_map_line(list->line);
		map_matrix[y++] = list->line;
		list = list->next;
	}
	map_matrix[y] = NULL;
	return (map_matrix);
}

//* take a str and return it without '\n' at the end
char	*ft_get_line_without_new_line(char *str)
{
	int	i;

	i = ft_strlen(str);
	i--;
	while (is_space(str[i]) && i > 0)
		i--;
	return (ft_substr(str, 0, i + 1));
}

//* read the map from fd and store it in a linked list
t_list	*convert_map_from_file_to_linked_list(int fd, char *first_line)
{
	char	*line;
	t_list	*map_list;
	bool	empty_line;

	map_list = NULL;
	empty_line = false;
	ft_add_back(&map_list, first_line);
	line = get_next_line(fd);
	while (line)
	{
		if (is_only_white_spaces(line))
			empty_line = true;
		else
			ft_add_back(&map_list, line);
		ft_safe_malloc(0, FREE_ONE, 1, line);
		line = get_next_line(fd);
	}
	if (empty_line)
		error_exit("Error\nMap is not the last element in file\n");
	return (map_list);
}
