/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenmoha <hbenmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 09:41:39 by hbenmoha          #+#    #+#             */
/*   Updated: 2025/09/24 13:59:32 by hbenmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

char *get_next_line(int fd)
{
	static char buf[BUFFER_SIZE + 1]; //? A static buffer stores leftover content between calls.
	char *line; //? the line that will be returned
	char *new_line;
	int i;
	int j;

	line = ft_strdup(buf);

	//? read from the fd and append to the last str until we found a '\n' 
	while (!(new_line = ft_strchr(line, '\n')) && (i = read(fd, buf, BUFFER_SIZE))) 
	{
		buf[i] = '\0';
		line = ft_strjoin(line, buf);
	}

	//? if read return 0 ( i = 0 ) which mean we reach the EOF (for example in an empty line)
	if (ft_strlen(line) == 0)
		return(ft_safe_malloc(0, FREE_ONE, 1, line), NULL);

	if (new_line != NULL) //? save characters after '\n' in a the buf (if we foun the '\n')
	{
		j = new_line - line + 1; //* j = 11 - 0 + 1 = 12 ( new_line = ptr to '\n') ( line ptr to the first char of str) ( + 1 of the '\n' => j = indix after '\n' )
		ft_strcopy(buf, new_line + 1); //* copy chars that are after '\n' in the buf ( daba lbufer fih cheyata )
	}
	else //? when we found the last line in the fd whitout a '\n'.
	{  //? we calculate it's lenght and null terminate the buffer and we null terminate the last line . then we return it
		j = ft_strlen(line);
		buf[0] = '\0';
	}

	line[j] = '\0'; //* j = indix after '\n'
	return(line);
}
