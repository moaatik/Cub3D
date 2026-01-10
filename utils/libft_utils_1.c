/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenmoha <hbenmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 10:50:52 by hbenmoha          #+#    #+#             */
/*   Updated: 2025/11/18 13:49:04 by hbenmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

//* skip white spaces at the start of str
char	*skip_white_spaces(char *str)
{
	while ((*str >= 9 && *str <= 13) || *str == 32)
	{
		if ((*str >= 9 && *str <= 13) && *str != 10)
			error_exit("Error\nForbidden character in map\n");
		str++;
	}
	return (str);
}

//* calculate a str lenght
int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

//* check if a str contain a whit_spaces
bool	str_is_space(char *str)
{
	while (*str)
	{
		if ((*str >= 9 && *str <= 13) || *str == 32)
			return (true);
		str++;
	}
	return (false);
}

//* check if a str doesn't contain a white_sapces
bool	is_not_space(char *str)
{
	return (*str != 32);
}

//* check if a str is only white spaces
bool	is_only_white_spaces(char *str)
{
	while (*str)
	{
		if ((*str < 9 || *str > 13) && *str != 32)
			return (false);
		str++;
	}
	return (true);
}
