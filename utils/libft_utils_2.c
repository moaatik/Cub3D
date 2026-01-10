/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenmoha <hbenmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 10:56:08 by hbenmoha          #+#    #+#             */
/*   Updated: 2025/11/08 11:00:35 by hbenmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

//* converte ascii to integer + check if nb > 255
int	ft_atoi(char *str)
{
	long	nb;

	nb = 0;
	if (!str)
		return (-1);
	while (*str >= '0' && *str <= '9')
	{
		nb = (nb * 10) + (*str++ - 48);
		if (nb > 255)
			return (-1);
	}
	return ((int)nb);
}

//* print a string in a fd
void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	if (fd < 0)
		return ;
	write(fd, s, ft_strlen(s));
}

//* search for a char in a str
char	*ft_strchr(char *s, int c)
{
	while (s && *s)
	{
		if (*s == c)
			return (s);
		s++;
	}
	return (NULL);
}

//* copy a str to a dest
void	ft_strcopy(char *d, char *s)
{
	if (!d || !s)
		return ;
	while (*s)
		*d++ = *s++;
	*d = '\0';
}

//* duplicate a str
char	*ft_strdup(char *s)
{
	char	*str;

	if (!s)
		return (NULL);
	str = ft_safe_malloc(ft_strlen(s) + 1, ALLOCATE, 1, NULL);
	ft_strcopy(str, s);
	return (str);
}
