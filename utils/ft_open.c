/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenmoha <hbenmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 08:17:18 by hbenmoha          #+#    #+#             */
/*   Updated: 2025/11/18 14:29:14 by hbenmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

//* Add a new node to the fds list.
static void	add_fd_to_list(t_fds **fds_header, int new_fd)
{
	t_fds	*new_node;
	t_fds	*last;

	if (!fds_header)
		return ;
	new_node = ft_safe_malloc(sizeof(t_fds), ALLOCATE, 1, NULL);
	new_node->fd = new_fd;
	new_node->next = NULL;
	if (!*fds_header)
	{
		*fds_header = new_node;
		return ;
	}
	last = *fds_header;
	while (last->next)
		last = last->next;
	last->next = new_node;
}

//* close all fds in the list
static void	close_and_free_fds_list(t_fds **fds_header)
{
	t_fds	*tmp;

	if (!fds_header || !*fds_header)
		return ;
	while (*fds_header)
	{
		tmp = (*fds_header)->next;
		close((*fds_header)->fd);
		ft_safe_malloc(0, FREE_ONE, 1, *fds_header);
		*fds_header = tmp;
	}
}

//* open an fd, track it, and handle failures safely.
int	ft_open(const char *file, int oflag, int key)
{
	static t_fds	*fds;
	int				fd;

	fd = -1;
	if (key == CREATE_FD)
	{
		if (!file)
			error_exit("open failed\n");
		fd = open(file, oflag);
		if (fd == -1)
			error_exit("open failed\n");
		add_fd_to_list(&fds, fd);
	}
	else if (key == CLOSE_FDS)
		close_and_free_fds_list(&fds);
	return (fd);
}

//* check if the current line of map contain a valid chars 
void	check_valid_map_line(char *str)
{
	if (!str)
		return ;
	while (*str)
	{
		if (*str != 32 && *str != '1' && *str != '0' && !is_player(*str))
			error_exit("Error\nForbidden character in map\n");
		str++;
	}
}
