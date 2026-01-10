/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenmoha <hbenmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 09:41:39 by hbenmoha          #+#    #+#             */
/*   Updated: 2025/11/09 09:23:15 by hbenmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	handle_new_line(int *j, char *new_line, char *line, char *buf)
{
	*j = new_line - line + 1;
	ft_strcopy(buf, new_line + 1);
}

void	handle_end_of_file(int *j, char *line, char *buf)
{
	*j = ft_strlen(line);
	buf[0] = '\0';
}

void	get_new_line(char **new_line, int fd, char *buf, char **line)
{
	int	i;

	i = 1;
	while (!(*new_line) && i > 0)
	{
		i = read(fd, buf, BUFFER_SIZE);
		if (i <= 0)
			break ;
		buf[i] = '\0';
		*line = ft_strjoin(*line, buf);
		*new_line = ft_strchr(*line, '\n');
	}
}

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1];
	char		*line;
	char		*new_line;
	int			j;

	line = ft_strdup(buf);
	new_line = ft_strchr(line, '\n');
	get_new_line(&new_line, fd, buf, &line);
	if (ft_strlen(line) == 0)
		return (buf[0] = '\0', ft_safe_malloc(0, FREE_ONE, 1, line), NULL);
	if (new_line)
		handle_new_line(&j, new_line, line, buf);
	else
		handle_end_of_file(&j, line, buf);
	line[j] = '\0';
	return (line);
}
