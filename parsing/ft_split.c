/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenmoha <hbenmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 15:45:14 by hbenmoha          #+#    #+#             */
/*   Updated: 2025/09/23 21:50:00 by hbenmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

//? Count how many words are in the string using the delimiter.
size_t	count_word(const char *str, char c)
{
	size_t	words;	// Counter for the number of words.
	short	key;	// Flag to track whether we are inside a word.

	words = 0;
	key = 1;
	while (*str)
	{
		// If the current character is not the delimiter and we are at the start of a word:
		if (*str != c && key == 1)
		{
			words++;	// Increment the word count.
			key = 0;	// Mark that we are inside a word.
		}
		// If the current character is the delimiter:
		else if (*str == c)
			key = 1;	// Mark that we are outside a word.
		str++;			// Move to the next character.
	}
	return (words);		// Return the total number of words.
}

//? Create a substring from the input string.
static char	*ft_substr_split(char const *s, size_t len)
{
	size_t	i;      // Index for traversing the input string.
	char	*str;   // Pointer to the new substring.

    // Check if the input string is NULL.
	if (!s)
		return (NULL);

    // Allocate memory for the substring.
	str = ft_safe_malloc((len + 1) * sizeof(char), ALLOCATE, 1, NULL);
    // Copy characters from the input string to the substring.
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
	size_t	len;    // Length of the current word.
	size_t	i;      // Index for the 2D array.

	i = 0;
	while (*str)
	{
		len = 0;
        //* Skip leading delimiters.
		while (*str == c && *str)
			str++;

        //* Calculate the length of the current word.
		while (*str != c && *str)
		{
			len++;
			str++;
		}
        //* If a word was found and there is space in the 2D array:
		if ((len) && (i < w_nb))
			words[i++] = ft_substr_split(str - len, len);     //* Extract and store the word.
	}
	return (words);     //* Return the filled 2D array.
}

//? Split the input string into a 2D array using the delimiter.
char	**ft_split(const char *str, char c, int *words_nb)
{
	size_t	words_number;   //* Number of words in the input string.
	char	**words;        //* 2D array to store the split words.

    //* Check if the input string is NULL.
	if (!str)
		return (NULL);

    //* Count the number of words in the input string.
	words_number = count_word(str, c);
	*words_nb = words_number;   //* Store the word count in the output variable.
	words = ft_safe_malloc(sizeof(char *) * (words_number + 1), ALLOCATE, 1, NULL);  //* Allocate memory for the 2D array.
	words[words_number] = NULL; //* Null-terminate the 2D array.
	return (fill_string(words, str, c, words_number));  // Fill the 2D array with substrings.
}
