/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils_4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenmoha <hbenmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 11:34:24 by hbenmoha          #+#    #+#             */
/*   Updated: 2025/11/18 13:58:01 by hbenmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

//* print a str in STDERR, free everything and exit.
void	error_exit(char *str)
{
	ft_putstr_fd(str, 2);
	ft_safe_malloc(0, FREE_ALL, 1, NULL);
}

//* take a str and trip spaces at the start + end
char	*trim_spaces(char *line)
{
	char	*str;
	int		i;

	i = 0;
	while ((*line >= 9 && *line <= 13) || *line == 32)
	{
		if (*line >= 9 && *line <= 13)
			error_exit("Error\nInvalid texture identifier format\n");
		line++;
	}
	while (line[i])
		i++;
	i--;
	while ((line[i] >= 9 && line[i] <= 13) || line[i] == 32)
	{
		if ((line[i] >= 9 && line[i] <= 13) && line[i] != 10)
			error_exit("Error\nInvalid texture identifier format\n");
		i--;
	}
	str = ft_substr(line, 0, i + 1);
	return (str);
}

//* convert rgb from 2D array to one int=
int	convert_rgb_from_str_to_int(char **rgb_strs)
{
	int	i;
	int	rgb[3];

	i = 0;
	while (rgb_strs[i])
	{
		rgb_strs[i] = trim_spaces(rgb_strs[i]);
		if (str_is_space(rgb_strs[i]))
		{
			ft_putstr_fd("Error\nRGB is not correct!\n", 2);
			ft_safe_malloc(0, FREE_ALL, 1, NULL);
		}
		rgb[i] = ft_atoi(rgb_strs[i]);
		if (rgb[i] == -1)
		{
			ft_putstr_fd("Error\nRGB is not correct!\n", 2);
			ft_safe_malloc(0, FREE_ALL, 1, NULL);
		}
		i++;
	}
	return ((rgb[0] << 16) | (rgb[1] << 8) | rgb[2]);
}

//* count how many times a char repeated
int	ft_count_char(char *str, char c, int reps)
{
	int	count;

	count = 0;
	if (!str)
		return (1);
	while (*str)
	{
		if (*str == c)
			count++;
		str++;
	}
	if (count != reps)
		return (1);
	return (0);
}

//* create and add a new node to t_list linked list
void	ft_add_back(t_list **head, char *line)
{
	t_list	*new_node;
	t_list	*tmp_head;

	tmp_head = *head;
	new_node = ft_safe_malloc(sizeof(t_list), ALLOCATE, 1, NULL);
	new_node->line = ft_get_line_without_new_line(line);
	new_node->length = ft_strlen(new_node->line);
	if (!*head)
		*head = new_node;
	else
	{
		while (tmp_head->next)
			tmp_head = tmp_head->next;
		tmp_head->next = new_node;
	}
}
