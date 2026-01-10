/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenmoha <hbenmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 15:45:14 by hbenmoha          #+#    #+#             */
/*   Updated: 2025/11/08 11:48:02 by hbenmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

//? Count how many words are in the string using the delimiter.
size_t	count_word(const char *str, char c)
{
	size_t	words;
	short	key;

	words = 0;
	key = 1;
	while (*str)
	{
		if (*str != c && key == 1)
		{
			words++;
			key = 0;
		}
		else if (*str == c)
			key = 1;
		str++;
	}
	return (words);
}

//? Create a substring from the input string.
static char	*ft_substr_split(char const *s, size_t len)
{
	size_t	i;
	char	*str;

	if (!s)
		return (NULL);
	str = ft_safe_malloc((len + 1) * sizeof(char), ALLOCATE, 1, NULL);
	i = 0;
	while (i < len)
	{
		str[i] = s[i];
		i++;
	}
	return (str);
}

//? Fill the 2D array with substrings extracted from the input string.
static char	**fill_string(char **words, const char *str, char c, size_t w_nb)
{
	size_t	len;
	size_t	i;

	i = 0;
	while (*str)
	{
		len = 0;
		while (*str == c && *str)
			str++;
		while (*str != c && *str)
		{
			len++;
			str++;
		}
		if ((len) && (i < w_nb))
			words[i++] = ft_substr_split(str - len, len);
	}
	return (words);
}

//? Split the input string into a 2D array using the delimiter.
char	**ft_split(const char *str, char c, int *words_nb)
{
	size_t	words_number;
	char	**words;

	if (!str)
		return (NULL);
	words_number = count_word(str, c);
	*words_nb = words_number;
	words = ft_safe_malloc(\
		sizeof(char *) * (words_number + 1), ALLOCATE, 1, NULL);
	words[words_number] = NULL;
	return (fill_string(words, str, c, words_number));
}
