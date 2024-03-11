/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmanip.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 14:35:36 by agaley            #+#    #+#             */
/*   Updated: 2024/03/09 14:57:03 by agaley           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * Compares two strings.
 *
 * @param s1 The first string to compare.
 * @param s2 The second string to compare.
 *
 * @returns An integer less than, equal to, or greater than zero if s1 is found,
 * respectively, to be less than, to match, or be greater than s2.
 */
int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	while (*str1 && (*str1 == *str2))
	{
		str1++;
		str2++;
	}
	return (*str1 - *str2);
}

/**
 * Searches for the first occurrence of a character in a string.
 *
 * @param s The string to search.
 * @param c The character to search for.
 *
 * @returns The first occurrence of the character (can be '\0') in the string.
 * NULL if the character was not found.
 */
char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	*s2;

	s2 = (char *)s;
	i = 0;
	while (s2[i])
	{
		if (s2[i] == (char)c)
			return (&s2[i]);
		i++;
	}
	if ((char)c == '\0')
		return ((char *)s + i);
	return ((void *)0);
}
