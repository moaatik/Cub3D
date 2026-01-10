/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenmoha <hbenmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 11:00:41 by hbenmoha          #+#    #+#             */
/*   Updated: 2025/11/08 11:02:51 by hbenmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

//* join 2 strings and free the first one
char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		j;
	int		i;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return ((char *)(s2));
	if (!s2)
		return ((char *)(s1));
	j = 0;
	i = 0;
	str = ft_safe_malloc(\
		(ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char), ALLOCATE, 1, NULL);
	while (s1[i])
		str[j++] = s1[i++];
	i = 0;
	while (s2[i])
		str[j++] = s2[i++];
	str[j] = 0;
	ft_safe_malloc(0, FREE_ONE, 1, s1);
	return (str);
}

//* compare 2 strs with a specific lenght 
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (n--)
	{
		if (*s1 != *s2 || !*s1 || !*s2)
			return ((unsigned char)*s1 - (unsigned char)*s2);
		s1++;
		s2++;
	}
	return (0);
}

//* compare 2 strings
int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

//* make a str from a str using start and lenght
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;

	if (!s)
		return (NULL);
	if (start > (unsigned int)ft_strlen(s) || len == 0)
		return (ft_strdup(""));
	if (len > (unsigned int)ft_strlen(s + start))
		len = ft_strlen(s + start);
	str = ft_safe_malloc(len + 1 * sizeof(char), ALLOCATE, 1, NULL);
	i = 0;
	while (i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	return (str);
}

//* check if a char is white_spaces
bool	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}
